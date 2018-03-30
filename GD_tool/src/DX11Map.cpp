#include "include\DX11Map.h"

GD_Tool::Mainframework::DX11Map::DX11Map(HINSTANCE hInstance, const GD_Tool::Mainframework::GlobalEnums::EMapSizes& mapSize)
	:DX11(hInstance)
	, m_pMapVertexBuffer(nullptr)
	, m_pMapConstBuffer(nullptr)
	, m_pVShader(nullptr)
	, m_pPShader(nullptr)
	, m_pVertBuf(nullptr)
	, m_pInputLayout(nullptr)
{
	switch (mapSize)
	{
	case GlobalEnums::EMapSizes::Size128:
		m_pVertBuf = new MAPVERTEX[SIZE128X128];
		break;
	case GlobalEnums::EMapSizes::Size256:
		m_pVertBuf = new MAPVERTEX[SIZE256X256];
		break;
	case GlobalEnums::EMapSizes::Size512:
		m_pVertBuf = new MAPVERTEX[SIZE512X512];
		break; 
	case GlobalEnums::EMapSizes::Size1k:
		m_pVertBuf = new MAPVERTEX[SIZE1024X1024];
		break; 
	case GlobalEnums::EMapSizes::Size2k:
		m_pVertBuf = new MAPVERTEX[SIZE2048X2048];
		break; 
	case GlobalEnums::EMapSizes::Size4k:
		m_pVertBuf = new MAPVERTEX[SIZE4096X4096]; 
		break; 
	case GlobalEnums::EMapSizes::Size8k: 
		m_pVertBuf = new MAPVERTEX[SIZE8192X8192];
		break;
	}

}

GD_Tool::Mainframework::DX11Map::~DX11Map()
{
	ReleaseMap();
}

bool GD_Tool::Mainframework::DX11Map::Init(const uint32_t & resolutionX, const uint32_t & resolutionY)
{
	if (!DX11::Init(resolutionX, resolutionY))
		return false;

	BuildShader();
	BuildBuffers();
	return true;
}

int32_t GD_Tool::Mainframework::DX11Map::Run()
{
	MSG msg = { 0 };


	m_timer.Reset();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			m_timer.Tick();
			if (!m_appPaused)
			{
				CalculateFrameStats();
			}
			else
			{
				Sleep(100);
			}
		}
	}
	return (int32_t)msg.wParam;
}

void GD_Tool::Mainframework::DX11Map::OnResize()
{
	DX11::OnResize();
}

void GD_Tool::Mainframework::DX11Map::UpdateScene()
{

}

void GD_Tool::Mainframework::DX11Map::DrawScene()
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
	m_pDevCon->IASetVertexBuffers(0, 1, &m_pMapVertexBuffer, &stride, &offset);
	m_pDevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	m_pDevCon->Draw(200, 0);

	hr = m_pSwapChain->Present(0, 0);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to present");
		return;
	}
}

LRESULT GD_Tool::Mainframework::DX11Map::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

void GD_Tool::Mainframework::DX11Map::ReleaseMap()
{
	DX11::Release();
	SafeRelease(m_pMapVertexBuffer); 
	SafeRelease(m_pMapConstBuffer); 
	SafeRelease(m_pVShader); 
	SafeRelease(m_pPShader); 
	SafeRelease(m_pInputLayout);
	delete[] m_pVertBuf;
}

void GD_Tool::Mainframework::DX11Map::BuildShader()
{
}

void GD_Tool::Mainframework::DX11Map::BuildBuffers()
{
}
