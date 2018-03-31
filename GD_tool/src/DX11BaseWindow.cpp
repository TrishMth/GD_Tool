#include "include\DX11BaseWindow.h"

GD_Tool::Mainframework::DX11BaseWindow::DX11BaseWindow(HINSTANCE hInstance)
	:DX11(hInstance)
	, m_pBaseVertexBuffer(nullptr)
	, m_pBaseConstBuffer(nullptr)
	, m_pBaseIndexBuffer(nullptr)
	, m_pVShader(nullptr)
	, m_pPShader(nullptr)
	, m_pBlendState(nullptr)
	, m_pFontSampler(nullptr)
	, m_pInputLayout(nullptr)
	, m_pDepthStencilState(nullptr)
	, m_pRasterizerState(nullptr)
	, m_pFontTexView(nullptr)
{
}
// Backup DX state that will be modified to restore it afterwards (unfortunately this is very ugly looking and verbose. Close your eyes!)
struct BACKUP_DX11_STATE
{
	UINT                        ScissorRectsCount, ViewportsCount;
	D3D11_RECT                  ScissorRects[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
	D3D11_VIEWPORT              Viewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
	ID3D11RasterizerState*      RS= nullptr;
	ID3D11BlendState*           BlendState = nullptr ;
	FLOAT                       BlendFactor[4];
	UINT                        SampleMask;
	UINT                        StencilRef;
	ID3D11DepthStencilState*    DepthStencilState = nullptr ;
	ID3D11ShaderResourceView*   PSShaderResource = nullptr;
	ID3D11SamplerState*         PSSampler = nullptr;
	ID3D11PixelShader*          PS = nullptr;
	ID3D11VertexShader*         VS = nullptr;
	UINT                        PSInstancesCount, VSInstancesCount;
	ID3D11ClassInstance*        PSInstances[256], *VSInstances[256];   // 256 is max according to PSSetShader documentation
	D3D11_PRIMITIVE_TOPOLOGY    PrimitiveTopology;
	ID3D11Buffer*               IndexBuffer = nullptr, *VertexBuffer = nullptr , *VSConstantBuffer = nullptr;
	UINT                        IndexBufferOffset, VertexBufferStride, VertexBufferOffset;
	DXGI_FORMAT                 IndexBufferFormat;
	ID3D11InputLayout*          InputLayout = nullptr;
	BACKUP_DX11_STATE()
	{
		for (int i = 0; i < 256; i++)
		{
			PSInstances[i] = nullptr;
			VSInstances[i] = nullptr;
		}
	}
	~BACKUP_DX11_STATE()
	{
		if(RS != nullptr)
			RS->Release();
		if(BlendState != nullptr)
			BlendState->Release();
		if(DepthStencilState != nullptr)
			DepthStencilState->Release();
		if(PSShaderResource != nullptr)
			PSShaderResource->Release();
		if(PSSampler != nullptr)
			PSSampler->Release();
		if(PS != nullptr)
			PS->Release();
		if(VS != nullptr)
			VS->Release();
		for (int i = 0; i < 256; i++)
		{
			if(PSInstances[i] != nullptr)
				PSInstances[i]->Release();
			if(VSInstances[i] != nullptr)
				VSInstances[i]->Release();	
		}
		if(IndexBuffer != nullptr)
			IndexBuffer->Release();
		if(VertexBuffer != nullptr)
			VertexBuffer->Release();
		if(VSConstantBuffer != nullptr)
			VSConstantBuffer->Release();
		if(InputLayout != nullptr)
			InputLayout->Release();
	}

};
GD_Tool::Mainframework::DX11BaseWindow::~DX11BaseWindow()
{
	DX11::Release();
	ReleaseWindow();
}

bool GD_Tool::Mainframework::DX11BaseWindow::Init(const uint32_t & resolutionX, const uint32_t & resolutionY)
{
	if (!DX11::Init(resolutionX, resolutionY))
		return false; 
	ImGui::CreateContext();

	if (!QueryPerformanceFrequency((LARGE_INTEGER *)&m_ticksPerSecond))
		return false;
	if (!QueryPerformanceCounter((LARGE_INTEGER *)&m_time))
		return false;

	// Setup back-end capabilities flags
	ImGuiIO& io = ImGui::GetIO();
	m_pDevice = m_pBaseDevice;
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;   // We can honor GetMouseCursor() values (optional)
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;    // We can honor io.WantSetMousePos requests (optional, rarely used)

															// Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array that we will update during the application lifetime.
	io.KeyMap[ImGuiKey_Tab] = VK_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = VK_UP;
	io.KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
	io.KeyMap[ImGuiKey_PageDown] = VK_NEXT;
	io.KeyMap[ImGuiKey_Home] = VK_HOME;
	io.KeyMap[ImGuiKey_End] = VK_END;
	io.KeyMap[ImGuiKey_Insert] = VK_INSERT;
	io.KeyMap[ImGuiKey_Delete] = VK_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = VK_BACK;
	io.KeyMap[ImGuiKey_Space] = VK_SPACE;
	io.KeyMap[ImGuiKey_Enter] = VK_RETURN;
	io.KeyMap[ImGuiKey_Escape] = VK_ESCAPE;
	io.KeyMap[ImGuiKey_A] = 'A';
	io.KeyMap[ImGuiKey_C] = 'C';
	io.KeyMap[ImGuiKey_V] = 'V';
	io.KeyMap[ImGuiKey_X] = 'X';
	io.KeyMap[ImGuiKey_Y] = 'Y';
	io.KeyMap[ImGuiKey_Z] = 'Z';

	io.ImeWindowHandle = m_hMainWnd;


	return true; 
}

int32_t GD_Tool::Mainframework::DX11BaseWindow::Run()
{
	ImGui::StyleColorsDark();
	MSG msg = { 0 };
	ImGuiIO& GUI = ImGui::GetIO();

	RECT rect{ 0 };
	GetClientRect(m_hMainWnd, &rect);
	GUI.DisplaySize = ImVec2((float)(rect.right - rect.left), (float)(rect.bottom - rect.top));

	int width, height;
	unsigned char* pixels;
	GUI.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
	GUI.Fonts->AddFontDefault();
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	bool show_window_demo = true; 
	m_timer.Reset();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		
		NewFrame();
		if (!m_appPaused)
		{
				
			UpdateScene(m_timer.DeltaTime());
				
			// 1. Show a simple window.
			// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
			{
				static float f = 0.0f;
				static int counter = 0;
				ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				ImGui::Checkbox("Demo Window", &show_window_demo);      // Edit bools storing our windows open/close state

				if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
					counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
			ImGui::ShowDemoWindow(&show_window_demo);
			m_pDevCon->OMSetRenderTargets(1, &m_pBackBuffer, NULL);
			m_pDevCon->ClearRenderTargetView(m_pBackBuffer, (float*)&clear_color);
			//DrawScene();
			ImGui::Render();
			RenderDrawData(ImGui::GetDrawData());
			m_pSwapChain->Present(1, 0);

		}
		else
		{
			Sleep(100);
		}
		
	}
	return (int32_t)msg.wParam;
}

void GD_Tool::Mainframework::DX11BaseWindow::OnResize()
{
	DX11::OnResize();
	ImGuiIO& GUI = ImGui::GetIO();
	GUI.DisplaySize.x = m_resolutionX; 
	GUI.DisplaySize.y = m_resolutionY; 
}

void GD_Tool::Mainframework::DX11BaseWindow::UpdateScene(const float& dTime)
{

}

void GD_Tool::Mainframework::DX11BaseWindow::DrawScene()
{
	float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_pDevCon->OMSetRenderTargets(1, &m_pBackBuffer, NULL);
	m_pDevCon->ClearRenderTargetView(m_pBackBuffer, (float*)&black);
}

void GD_Tool::Mainframework::DX11BaseWindow::RenderDrawData(ImDrawData* draw_data)
{
	uint32_t vertBufSize = 5000, indBufSize = 10000;

	// Create and grow vertex/index buffers if needed
	if (!m_pBaseVertexBuffer || vertBufSize < draw_data->TotalVtxCount)
	{
		if (m_pBaseVertexBuffer) { m_pBaseVertexBuffer->Release(); m_pBaseVertexBuffer = nullptr; }
		vertBufSize = draw_data->TotalVtxCount + 5000;
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = vertBufSize * sizeof(ImDrawVert);
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		if (m_pDevice->CreateBuffer(&desc, nullptr, &m_pBaseVertexBuffer) < 0)
			return;
	}
	if (!m_pBaseIndexBuffer || indBufSize < draw_data->TotalIdxCount)
	{
		if (m_pBaseIndexBuffer) { m_pBaseIndexBuffer->Release(); m_pBaseIndexBuffer = nullptr; }
		indBufSize = draw_data->TotalIdxCount + 10000;
		D3D11_BUFFER_DESC desc;
		memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = indBufSize * sizeof(ImDrawIdx);
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		if (m_pDevice->CreateBuffer(&desc, nullptr, &m_pBaseIndexBuffer) < 0)
			return;
	}

	// Copy and convert all vertices into a single contiguous buffer
	D3D11_MAPPED_SUBRESOURCE vtx_resource, idx_resource;
	if (m_pDevCon->Map(m_pBaseVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vtx_resource) != S_OK)
		return;
	if (m_pDevCon->Map(m_pBaseIndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &idx_resource) != S_OK)
		return;
	ImDrawVert* vtx_dst = (ImDrawVert*)vtx_resource.pData;
	ImDrawIdx* idx_dst = (ImDrawIdx*)idx_resource.pData;
	for (int n = 0; n < draw_data->CmdListsCount; n++)
	{
		const ImDrawList* cmd_list = draw_data->CmdLists[n];
		memcpy(vtx_dst, cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size * sizeof(ImDrawVert));
		memcpy(idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
		vtx_dst += cmd_list->VtxBuffer.Size;
		idx_dst += cmd_list->IdxBuffer.Size;
	}
	m_pDevCon->Unmap(m_pBaseVertexBuffer, 0);
	m_pDevCon->Unmap(m_pBaseIndexBuffer, 0);

	// Setup orthographic projection matrix into our constant buffer
	{
		D3D11_MAPPED_SUBRESOURCE mapped_resource;
		if (m_pDevCon->Map(m_pBaseConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource) != S_OK)
			return;
		VERTEX_CONSTANT_BUFFER* constant_buffer = (VERTEX_CONSTANT_BUFFER*)mapped_resource.pData;
		
		float L = 0.0f;
		float R = ImGui::GetIO().DisplaySize.x;
		float B = ImGui::GetIO().DisplaySize.y;
		float T = 0.0f;
		float mvp[4][4] =
		{
			{ 2.0f / (R - L),   0.0f,           0.0f,       0.0f },
		{ 0.0f,         2.0f / (T - B),     0.0f,       0.0f },
		{ 0.0f,         0.0f,           0.5f,       0.0f },
		{ (R + L) / (L - R),  (T + B) / (B - T),    0.5f,       1.0f },
		};
		memcpy(&constant_buffer->mvp, mvp, sizeof(mvp));
		m_pDevCon->Unmap(m_pBaseConstBuffer, 0);
	}

	
	BACKUP_DX11_STATE old;
	old.ScissorRectsCount = old.ViewportsCount = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
	m_pDevCon->RSGetScissorRects(&old.ScissorRectsCount, old.ScissorRects);
	m_pDevCon->RSGetViewports(&old.ViewportsCount, old.Viewports);
	m_pDevCon->RSGetState(&old.RS);
	m_pDevCon->OMGetBlendState(&old.BlendState, old.BlendFactor, &old.SampleMask);
	m_pDevCon->OMGetDepthStencilState(&old.DepthStencilState, &old.StencilRef);
	m_pDevCon->PSGetShaderResources(0, 1, &old.PSShaderResource);
	m_pDevCon->PSGetSamplers(0, 1, &old.PSSampler);
	old.PSInstancesCount = old.VSInstancesCount = 256;
	m_pDevCon->PSGetShader(&old.PS, old.PSInstances, &old.PSInstancesCount);
	m_pDevCon->VSGetShader(&old.VS, old.VSInstances, &old.VSInstancesCount);
	m_pDevCon->VSGetConstantBuffers(0, 1, &old.VSConstantBuffer);
	m_pDevCon->IAGetPrimitiveTopology(&old.PrimitiveTopology);
	m_pDevCon->IAGetIndexBuffer(&old.IndexBuffer, &old.IndexBufferFormat, &old.IndexBufferOffset);
	m_pDevCon->IAGetVertexBuffers(0, 1, &old.VertexBuffer, &old.VertexBufferStride, &old.VertexBufferOffset);
	m_pDevCon->IAGetInputLayout(&old.InputLayout);

	// Setup viewport
	D3D11_VIEWPORT vp;
	memset(&vp, 0, sizeof(D3D11_VIEWPORT));
	vp.Width = ImGui::GetIO().DisplaySize.x;
	vp.Height = ImGui::GetIO().DisplaySize.y;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = vp.TopLeftY = 0.0f;
	m_pDevCon->RSSetViewports(1, &vp);

	// Bind shader and vertex buffers
	unsigned int stride = sizeof(ImDrawVert);
	unsigned int offset = 0;
	m_pDevCon->IASetInputLayout(m_pInputLayout);
	m_pDevCon->IASetVertexBuffers(0, 1, &m_pBaseVertexBuffer, &stride, &offset);
	m_pDevCon->IASetIndexBuffer(m_pBaseIndexBuffer, sizeof(ImDrawIdx) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, 0);
	m_pDevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pDevCon->VSSetShader(m_pVShader, NULL, 0);
	m_pDevCon->VSSetConstantBuffers(0, 1, &m_pBaseConstBuffer);
	m_pDevCon->PSSetShader(m_pPShader, NULL, 0);
	m_pDevCon->PSSetSamplers(0, 1, &m_pFontSampler);

	// Setup render state
	const float blend_factor[4] = { 0.f, 0.f, 0.f, 0.f };
	m_pDevCon->OMSetBlendState(m_pBlendState, blend_factor, 0xffffffff);
	m_pDevCon->OMSetDepthStencilState(m_pDepthStencilState, 0);
	m_pDevCon->RSSetState(m_pRasterizerState);

	// Render command lists
	int vtx_offset = 0;
	int idx_offset = 0;
	for (int n = 0; n < draw_data->CmdListsCount; n++)
	{
		const ImDrawList* cmd_list = draw_data->CmdLists[n];
		for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
		{
			const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
			if (pcmd->UserCallback)
			{
				pcmd->UserCallback(cmd_list, pcmd);
			}
			else
			{
				const D3D11_RECT r = { (LONG)pcmd->ClipRect.x, (LONG)pcmd->ClipRect.y, (LONG)pcmd->ClipRect.z, (LONG)pcmd->ClipRect.w };
				m_pDevCon->PSSetShaderResources(0, 1, (ID3D11ShaderResourceView**)&pcmd->TextureId);
				m_pDevCon->RSSetScissorRects(1, &r);
				m_pDevCon->DrawIndexed(pcmd->ElemCount, idx_offset, vtx_offset);
			}
			idx_offset += pcmd->ElemCount;
		}
		vtx_offset += cmd_list->VtxBuffer.Size;
	}

	// Restore modified DX state
	m_pDevCon->RSSetScissorRects(old.ScissorRectsCount, old.ScissorRects);
	m_pDevCon->RSSetViewports(old.ViewportsCount, old.Viewports);
	m_pDevCon->RSSetState(old.RS); if (old.RS) old.RS->Release();
	m_pDevCon->OMSetBlendState(old.BlendState, old.BlendFactor, old.SampleMask); if (old.BlendState) old.BlendState->Release();
	m_pDevCon->OMSetDepthStencilState(old.DepthStencilState, old.StencilRef); if (old.DepthStencilState) old.DepthStencilState->Release();
	m_pDevCon->PSSetShaderResources(0, 1, &old.PSShaderResource); if (old.PSShaderResource) old.PSShaderResource->Release();
	m_pDevCon->PSSetSamplers(0, 1, &old.PSSampler); if (old.PSSampler) old.PSSampler->Release();
	m_pDevCon->PSSetShader(old.PS, old.PSInstances, old.PSInstancesCount); if (old.PS) old.PS->Release();
	for (UINT i = 0; i < old.PSInstancesCount; i++) if (old.PSInstances[i]) old.PSInstances[i]->Release();
	m_pDevCon->VSSetShader(old.VS, old.VSInstances, old.VSInstancesCount); if (old.VS) old.VS->Release();
	m_pDevCon->VSSetConstantBuffers(0, 1, &old.VSConstantBuffer); if (old.VSConstantBuffer) old.VSConstantBuffer->Release();
	for (UINT i = 0; i < old.VSInstancesCount; i++) if (old.VSInstances[i]) old.VSInstances[i]->Release();
	m_pDevCon->IASetPrimitiveTopology(old.PrimitiveTopology);
	m_pDevCon->IASetIndexBuffer(old.IndexBuffer, old.IndexBufferFormat, old.IndexBufferOffset); if (old.IndexBuffer) old.IndexBuffer->Release();
	m_pDevCon->IASetVertexBuffers(0, 1, &old.VertexBuffer, &old.VertexBufferStride, &old.VertexBufferOffset); if (old.VertexBuffer) old.VertexBuffer->Release();
	m_pDevCon->IASetInputLayout(old.InputLayout); if (old.InputLayout) old.InputLayout->Release();
}

void GD_Tool::Mainframework::DX11BaseWindow::CreateFontsTexture()
{
	// Build texture atlas
	ImGuiIO& io = ImGui::GetIO();
	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

	// Upload texture to graphics system
	{
		D3D11_TEXTURE2D_DESC desc{};
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;

		ID3D11Texture2D *pTexture = NULL;
		D3D11_SUBRESOURCE_DATA subResource;
		subResource.pSysMem = pixels;
		subResource.SysMemPitch = desc.Width * 4;
		subResource.SysMemSlicePitch = 0;
		m_pDevice->CreateTexture2D(&desc, &subResource, &pTexture);

		// Create texture view
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		m_pDevice->CreateShaderResourceView(pTexture, &srvDesc, &m_pFontTexView);
		pTexture->Release();
	}

	// Store our identifier
	io.Fonts->TexID = (void *)m_pFontTexView;

	// Create texture sampler
	{
		D3D11_SAMPLER_DESC desc{};
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.MipLODBias = 0.f;
		desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		desc.MinLOD = 0.f;
		desc.MaxLOD = 0.f;
		m_pDevice->CreateSamplerState(&desc, &m_pFontSampler);
	}

}

void GD_Tool::Mainframework::DX11BaseWindow::NewFrame()
{
	if (!m_pFontSampler)
		BuildShader();
	ImGuiIO& GUI = ImGui::GetIO();

	RECT rect{ 0 };
	GetClientRect(m_hMainWnd, &rect); 

	GUI.DisplaySize = ImVec2((float)(rect.right - rect.left), (float)(rect.bottom - rect.top));
	int64_t currentTime;
	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);
	GUI.DeltaTime = (float)(currentTime - m_time) / m_ticksPerSecond;
	m_time = currentTime;
	// Read keyboard modifiers inputs
	GUI.KeyCtrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
	GUI.KeyShift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
	GUI.KeyAlt = (GetKeyState(VK_MENU) & 0x8000) != 0;
	GUI.KeySuper = false;
	// GUI.KeysDown : filled by WM_KEYDOWN/WM_KEYUP events
	// GUI.MousePos : filled by WM_MOUSEMOVE events
	// GUI.MouseDown : filled by WM_*BUTTON* events
	// GUI.MouseWheel : filled by WM_MOUSEWHEEL events

	// Set OS mouse position if requested (only used when ImGuiConfigFlags_NavEnableSetMousePos is enabled by user)
	if (GUI.WantSetMousePos)
	{
		POINT pos = { (int)GUI.MousePos.x, (int)GUI.MousePos.y };
		ClientToScreen(m_hMainWnd, &pos);
		SetCursorPos(pos.x, pos.y);
	}
	ImGuiMouseCursor lastMouseCursor = ImGuiMouseCursor_COUNT;
	// Update OS mouse cursor with the cursor requested by imgui
	ImGuiMouseCursor mouse_cursor = GUI.MouseDrawCursor ? ImGuiMouseCursor_None : ImGui::GetMouseCursor();
	if (lastMouseCursor != mouse_cursor)
	{
		lastMouseCursor = mouse_cursor;
		UpdateCursor();
	}

	// Start the frame. This call will update the io.WantCaptureMouse, io.WantCaptureKeyboard flag that you can use to dispatch inputs (or not) to your application.
	ImGui::NewFrame();
}

bool GD_Tool::Mainframework::DX11BaseWindow::UpdateCursor()
{
	ImGuiIO& GUI = ImGui::GetIO();
	if (GUI.ConfigFlags & ImGuiConfigFlags_NoSetMouseCursor)
		return false; 

	ImGuiMouseCursor imgui_cursor = GUI.MouseDrawCursor ? ImGuiMouseCursor_None : ImGui::GetMouseCursor();
	if (imgui_cursor == ImGuiMouseCursor_None)
	{
		// Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
		::SetCursor(NULL);
	}
	else
	{
		// Hardware cursor type
		LPTSTR win32_cursor = IDC_ARROW;
		switch (imgui_cursor)
		{
		case ImGuiMouseCursor_Arrow:        win32_cursor = IDC_ARROW; break;
		case ImGuiMouseCursor_TextInput:    win32_cursor = IDC_IBEAM; break;
		case ImGuiMouseCursor_ResizeAll:    win32_cursor = IDC_SIZEALL; break;
		case ImGuiMouseCursor_ResizeEW:     win32_cursor = IDC_SIZEWE; break;
		case ImGuiMouseCursor_ResizeNS:     win32_cursor = IDC_SIZENS; break;
		case ImGuiMouseCursor_ResizeNESW:   win32_cursor = IDC_SIZENESW; break;
		case ImGuiMouseCursor_ResizeNWSE:   win32_cursor = IDC_SIZENWSE; break;
		}
		::SetCursor(::LoadCursor(NULL, win32_cursor));
	}
	return true;
}

bool GD_Tool::Mainframework::DX11BaseWindow::WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui::GetCurrentContext() == NULL)
		return 0;
	ImGuiIO& io = ImGui::GetIO();
	switch (msg)
	{
	case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
	{
		int button = 0;
		if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK) button = 0;
		if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONDBLCLK) button = 1;
		if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONDBLCLK) button = 2;
		if (!ImGui::IsAnyMouseDown() && ::GetCapture() == NULL)
			::SetCapture(hwnd);
		io.MouseDown[button] = true;
		return 0;
	}
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	{
		int button = 0;
		if (msg == WM_LBUTTONUP) button = 0;
		if (msg == WM_RBUTTONUP) button = 1;
		if (msg == WM_MBUTTONUP) button = 2;
		io.MouseDown[button] = false;
		if (!ImGui::IsAnyMouseDown() && ::GetCapture() == hwnd)
			::ReleaseCapture();
		return 0;
	}
	case WM_MOUSEWHEEL:
		io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
		return 0;
	case WM_MOUSEHWHEEL:
		io.MouseWheelH += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
		return 0;
	case WM_MOUSEMOVE:
		io.MousePos.x = (signed short)(lParam);
		io.MousePos.y = (signed short)(lParam >> 16);
		return 0;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (wParam < 256)
			io.KeysDown[wParam] = 1;
		return 0;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		if (wParam < 256)
			io.KeysDown[wParam] = 0;
		return 0;
	case WM_CHAR:
		// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
		if (wParam > 0 && wParam < 0x10000)
			io.AddInputCharacter((unsigned short)wParam);
		return 0;
	case WM_SETCURSOR:
		if (LOWORD(lParam) == HTCLIENT && UpdateCursor())
			return 1;
	}
	return 0;
}

LRESULT GD_Tool::Mainframework::DX11BaseWindow::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	if (WndProcHandler(hwnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (m_pDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			InvalidateDeviceObjects();
			CleanupRenderTarget();
			m_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			CreateRenderTarget();
			BuildShader();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void GD_Tool::Mainframework::DX11BaseWindow::ReleaseWindow()
{
	Release(); 
	SafeRelease(m_pBaseConstBuffer); 
	SafeRelease(m_pBaseVertexBuffer); 
	SafeRelease(m_pInputLayout); 
	SafeRelease(m_pVShader); 
	SafeRelease(m_pPShader);
	SafeRelease(m_pBlendState);
	SafeRelease(m_pFontSampler); 
	SafeRelease(m_pDepthStencilState);
	SafeRelease(m_pRasterizerState);
	SafeRelease(m_pFontTexView);
	ImGui::DestroyContext();
}

void GD_Tool::Mainframework::DX11BaseWindow::BuildShader()
{
	if (!m_pDevice)
		return; 
	if (m_pFontSampler)
		InvalidateDeviceObjects();
	{
		static const char* vertexShader =
			"cbuffer vertexBuffer : register(b0) \
            {\
            float4x4 ProjectionMatrix; \
            };\
            struct VS_INPUT\
            {\
            float2 pos : POSITION;\
            float4 col : COLOR0;\
            float2 uv  : TEXCOORD0;\
            };\
            \
            struct PS_INPUT\
            {\
            float4 pos : SV_POSITION;\
            float4 col : COLOR0;\
            float2 uv  : TEXCOORD0;\
            };\
            \
            PS_INPUT main(VS_INPUT input)\
            {\
            PS_INPUT output;\
            output.pos = mul( ProjectionMatrix, float4(input.pos.xy, 0.f, 1.f));\
            output.col = input.col;\
            output.uv  = input.uv;\
            return output;\
            }";
		ID3D10Blob* pVShaderBlob = nullptr; 
		D3DCompile(vertexShader, strlen(vertexShader), NULL, NULL, NULL, "main", "vs_4_0", 0, 0, &pVShaderBlob, NULL);
		if (pVShaderBlob == nullptr) // NB: Pass ID3D10Blob* pErrorBlob to D3DCompile() to get error showing in (const char*)pErrorBlob->GetBufferPointer(). Make sure to Release() the blob!
			return;
		if (m_pDevice->CreateVertexShader((DWORD*)pVShaderBlob->GetBufferPointer(), pVShaderBlob->GetBufferSize(), NULL, &m_pVShader) != S_OK)
			return;

		// Create the input layout
		D3D11_INPUT_ELEMENT_DESC local_layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,   0, (size_t)(&((ImDrawVert*)0)->pos), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,   0, (size_t)(&((ImDrawVert*)0)->uv),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, (size_t)(&((ImDrawVert*)0)->col), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		if (m_pDevice->CreateInputLayout(local_layout, 3, pVShaderBlob->GetBufferPointer(), pVShaderBlob->GetBufferSize(), &m_pInputLayout) != S_OK)
			return;

		// Create the constant buffer
		{
			D3D11_BUFFER_DESC desc;
			desc.ByteWidth = sizeof(VERTEX_CONSTANT_BUFFER);
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.MiscFlags = 0;
			m_pDevice->CreateBuffer(&desc, NULL, &m_pBaseConstBuffer);
		}
		SafeRelease(pVShaderBlob);
	}
	// Create the pixel shader
	{
		static const char* pixelShader =
			"struct PS_INPUT\
            {\
            float4 pos : SV_POSITION;\
            float4 col : COLOR0;\
            float2 uv  : TEXCOORD0;\
            };\
            sampler sampler0;\
            Texture2D texture0;\
            \
            float4 main(PS_INPUT input) : SV_Target\
            {\
            float4 out_col = input.col * texture0.Sample(sampler0, input.uv); \
            return out_col; \
            }";

		ID3D10Blob* pPShaderBlob = nullptr; 
		D3DCompile(pixelShader, strlen(pixelShader), NULL, NULL, NULL, "main", "ps_4_0", 0, 0, &pPShaderBlob, NULL);
		if (pPShaderBlob == nullptr)  // NB: Pass ID3D10Blob* pErrorBlob to D3DCompile() to get error showing in (const char*)pErrorBlob->GetBufferPointer(). Make sure to Release() the blob!
			return;
		if (m_pDevice->CreatePixelShader((DWORD*)pPShaderBlob->GetBufferPointer(), pPShaderBlob->GetBufferSize(), NULL, &m_pPShader) != S_OK)
			return;
		SafeRelease(pPShaderBlob);
	}

	// Create the blending setup
	{
		D3D11_BLEND_DESC desc{};
		desc.AlphaToCoverageEnable = false;
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		m_pDevice->CreateBlendState(&desc, &m_pBlendState);
	}

	// Create the rasterizer state
	{
		D3D11_RASTERIZER_DESC desc{};
		desc.FillMode = D3D11_FILL_SOLID;
		desc.CullMode = D3D11_CULL_NONE;
		desc.ScissorEnable = true;
		desc.DepthClipEnable = true;
		m_pDevice->CreateRasterizerState(&desc, &m_pRasterizerState);
	}

	// Create depth-stencil State
	{
		D3D11_DEPTH_STENCIL_DESC desc{};
		desc.DepthEnable = false;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
		desc.StencilEnable = false;
		desc.FrontFace.StencilFailOp = desc.FrontFace.StencilDepthFailOp = desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		desc.BackFace = desc.FrontFace;
		m_pDevice->CreateDepthStencilState(&desc, &m_pDepthStencilState);
	}

	CreateFontsTexture();

}

void GD_Tool::Mainframework::DX11BaseWindow::BuildBuffers()
{

}
