#include "include\DX11Graph.h"

GD_Tool::Mainframework::DX11Graph::DX11Graph(HINSTANCE hInstance)
	:DX11(hInstance)
	, m_pGraphVertexBuffer(nullptr)
	, m_pInputLayout(nullptr)
	, m_pGraphConstBuffer(nullptr)
	,m_pVShader(nullptr)
	,m_pPShader(nullptr)
{
}

GD_Tool::Mainframework::DX11Graph::~DX11Graph()
{
	ReleaseGraph();
}

bool GD_Tool::Mainframework::DX11Graph::Init(const uint32_t& resolutionX, const uint32_t& resolutionY)
{
	if (!DX11::Init(resolutionX, resolutionY))
		return false; 

	BuildShader();
	BuildBuffers();
	return true; 
}

int32_t GD_Tool::Mainframework::DX11Graph::Run()
{
	MSG msg = { 0 };



	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (!m_appPaused)
			{
			}
			else
			{
				Sleep(100);
			}
		}
	}
	return (int32_t)msg.wParam;
}

void GD_Tool::Mainframework::DX11Graph::OnResize()
{
	DX11::OnResize();
	DrawScene();
}

void GD_Tool::Mainframework::DX11Graph::UpdateScene()
{
	UpdateConstBuf();
}

void GD_Tool::Mainframework::DX11Graph::DrawScene()
{
	HRESULT hr; 
	assert(m_pDevCon); 
	assert(m_pSwapChain);
	float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_pDevCon->ClearRenderTargetView(m_pBackBuffer, black);
	m_pDevCon->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	uint32_t stride = sizeof(GRAPHVERTEX);
	uint32_t offset = 0; 
	m_pDevCon->IASetVertexBuffers(0, 1, &m_pGraphVertexBuffer, &stride, &offset);
	m_pDevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	m_pDevCon->Draw(200, 0);

	hr = m_pSwapChain->Present(0, 0);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to present");
		return;
	}
}

void GD_Tool::Mainframework::DX11Graph::ReleaseGraph()
{
	DX11::Release(); 
	SafeRelease(m_pGraphVertexBuffer);
	SafeRelease(m_pVShader); 
	SafeRelease(m_pPShader);
	SafeRelease(m_pGraphConstBuffer);
	SafeRelease(m_pInputLayout);
	_aligned_free(m_pConstBuf);

}

LRESULT GD_Tool::Mainframework::DX11Graph::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result;
	result = DX11::MsgProc(hwnd, msg, wParam, lParam); 
	switch (msg)
	{
	case WM_SIZE:
		if (wParam == 2)
		{
			OnResize();
			m_maximized = true;
			m_minimized = false; 
		}
		else if (m_maximized && wParam == 0)
		{
			OnResize();
			m_maximized = false;
			m_minimized = true;
		}
		break;
	}
	return result; 
}

void GD_Tool::Mainframework::DX11Graph::SetNewGraphHeight(const float& val, const uint32_t& index)
{
	m_pVertBuf[index].y = val;
	if (UpdateVertBuf())
		DrawScene();
}

void GD_Tool::Mainframework::DX11Graph::SetNewConstBuffer(GRAPH_VS_CONSTANT_BUFFER * constBuf)
{
	m_pConstBuf = constBuf; 
	if (UpdateConstBuf())
		DrawScene();
}


GD_Tool::Mainframework::GRAPH_VS_CONSTANT_BUFFER* GD_Tool::Mainframework::DX11Graph::GetConstBuffer() const
{
	return m_pConstBuf;
}

void GD_Tool::Mainframework::DX11Graph::BuildShader()
{
	DWORD shaderFlags = 0; 
#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3DCOMPILE_DEBUG;
	shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif 
	ID3D10Blob* compiledVShader = nullptr;
	ID3D10Blob* compiledPShader = nullptr;
	ID3D10Blob* compilationMsgs = nullptr; 
	HRESULT hr; 
	hr = D3DCompileFromFile(L"VS/GraphV.Shader", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VSMain", "vs_5_0", shaderFlags, NULL, &compiledVShader, &compilationMsgs);
	if (compilationMsgs != nullptr)
	{
		MessageBoxA(0, (char*)compilationMsgs->GetBufferPointer(), 0, 0);
		SafeRelease(compilationMsgs);
		return;
	}
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to compile Vertex Shader of the graph");
		SafeRelease(compiledVShader); 
		return;
	}
	hr = m_pDevice->CreateVertexShader(compiledVShader->GetBufferPointer(), compiledVShader->GetBufferSize(), nullptr, &m_pVShader);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to create vertex shader of the graph"); 
		SafeRelease(compiledVShader);
		return;
	}
	m_pDevCon->VSSetShader(m_pVShader, nullptr, NULL); 

	hr = D3DCompileFromFile(L"PS/GraphP.Shader", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PSMain", "ps_5_0", shaderFlags, NULL, &compiledPShader, &compilationMsgs);
	if (compilationMsgs != nullptr)
	{
		MessageBoxA(0, (char*)compilationMsgs->GetBufferPointer(), 0, 0);
		SafeRelease(compilationMsgs);
		return;
	}
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to compile Pixel Shader of the graph");
		SafeRelease(compiledPShader);
	}
	hr = m_pDevice->CreatePixelShader(compiledPShader->GetBufferPointer(), compiledPShader->GetBufferSize(), nullptr, &m_pPShader);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to create pixel shader of the graph");
		SafeRelease(compiledPShader);
		return;
	}
	m_pDevCon->PSSetShader(m_pPShader, nullptr, NULL);
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	
	hr = m_pDevice->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), compiledVShader->GetBufferPointer(),compiledVShader->GetBufferSize(), &m_pInputLayout);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to create input layout");
		return;
	}
	m_pDevCon->IASetInputLayout(m_pInputLayout);
	
	SafeRelease(compiledVShader);
	SafeRelease(compiledPShader);
	SafeRelease(compilationMsgs);

}

void GD_Tool::Mainframework::DX11Graph::BuildBuffers()
{
	HRESULT hr;

	
	m_pConstBuf->fTime = .8f;
	D3D11_BUFFER_DESC constBufDesc{}; 
	constBufDesc.ByteWidth = sizeof(GRAPH_VS_CONSTANT_BUFFER)*4;
	constBufDesc.Usage = D3D11_USAGE_DYNAMIC; 
	constBufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; 
	constBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = &m_pConstBuf;

	hr = m_pDevice->CreateBuffer(&constBufDesc, &initData, &m_pGraphConstBuffer);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to create constant buffer");
		return;
	}

	m_pDevCon->VSSetConstantBuffers(0, 1, &m_pGraphConstBuffer);
	m_pDevCon->PSSetConstantBuffers(0, 1, &m_pGraphConstBuffer);

	D3D11_SUBRESOURCE_DATA subData{};
	subData.pSysMem = &m_pGraphVertexBuffer; 
	D3D11_MAPPED_SUBRESOURCE mapSubRes{};


	for (uint32_t i = 0; i < 100; i++)
	{
		if (i == 0)
			m_pVertBuf[i].x = -1;
		else
			m_pVertBuf[i].x = -1 + ((float)i / 100);
		m_pVertBuf[i].y = -.9f;		
		m_pVertBuf[i].z = 0.0f;
	}
	for (uint32_t i = 0; i < 100; i++)
	{
		m_pVertBuf[i+100].x = (float)i / 100;	
		if (i != 50)
			m_pVertBuf[i + 100].y = -.9f;
		else
			m_pVertBuf[i + 100].y = 1;
		m_pVertBuf[i+100].z = 0.0f;
	}			 

	D3D11_BUFFER_DESC vBufferDesc{}; 
	vBufferDesc.ByteWidth = sizeof(GRAPHVERTEX) * 200;
	vBufferDesc.Usage = D3D11_USAGE_DYNAMIC; 
	vBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; 
	vBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;


	hr = m_pDevice->CreateBuffer(&vBufferDesc, nullptr, &m_pGraphVertexBuffer);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to create vertex buffer"); 
		return;
	}
	hr = m_pDevCon->Map(m_pGraphVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mapSubRes);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to map the vertexbuffer");
		return;
	}
	memcpy(mapSubRes.pData, m_pVertBuf, sizeof(m_pVertBuf));
	m_pDevCon->Unmap(m_pGraphVertexBuffer, NULL); 
	
	if (UpdateConstBuf())
		DrawScene();

}

bool GD_Tool::Mainframework::DX11Graph::UpdateConstBuf()
{
	D3D11_MAPPED_SUBRESOURCE mappedSubRes{};

	HRESULT hr; 
	hr = m_pDevCon->Map(m_pGraphConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubRes);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to map const buffer"); 
		return false; 
	}

	GRAPH_VS_CONSTANT_BUFFER* dataPtr = (GRAPH_VS_CONSTANT_BUFFER*)mappedSubRes.pData;
	if (dataPtr == nullptr)
	{
		OutputDebugStringW(L"Failed to read out mapped subresource data"); 
		return false; 
	}
	memcpy(dataPtr, m_pConstBuf, sizeof(GRAPH_VS_CONSTANT_BUFFER));

	m_pDevCon->Unmap(m_pGraphConstBuffer, 0); 
	return true;
}

bool GD_Tool::Mainframework::DX11Graph::UpdateVertBuf()
{
	D3D11_MAPPED_SUBRESOURCE mappedSubRes{};

	HRESULT hr; 
	hr = m_pDevCon->Map(m_pGraphVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubRes);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to map vertex buffer");
		return false;
	}
	GRAPHVERTEX* dataPtr = (GRAPHVERTEX*)mappedSubRes.pData;
	if (dataPtr == nullptr)
	{
		OutputDebugStringW(L"Failed to read out mapped subresource data");
		return false;
	}
	memcpy(dataPtr, m_pVertBuf, sizeof(GRAPHVERTEX));
	m_pDevCon->Unmap(m_pGraphVertexBuffer, 0); 
	return true; 
}


void GD_Tool::Mainframework::DX11Graph::CreateGrid(const float & width, const float & height, const uint32_t & vCntX, const uint32_t & vCntY)
{

	uint32_t vCnt = vCntX * vCntY;
}
