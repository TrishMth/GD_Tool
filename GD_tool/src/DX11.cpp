#include "include\DX11.h"


//function to check the HRESULT of some functions
bool GD_Tool::Mainframework::DX11::Failed(HRESULT aResult)
{
	if (FAILED(aResult))
	{
		LPTSTR buffer;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, (DWORD)aResult, LANG_USER_DEFAULT, (LPTSTR)&buffer, 0, nullptr);

		MessageBox(0, buffer, TEXT("Fatal error"), MB_OK | MB_ICONERROR);
		LocalFree(buffer);
		return true;
	}
	return false;
}
HRESULT GD_Tool::Mainframework::DX11::CreateDeviceD3D(HWND hwnd)
{
	// Setup swap chain
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &m_pSwapChain, &m_pBaseDevice, &featureLevel, &m_pDevCon) != S_OK)
		return E_FAIL;

	CreateRenderTarget();

	return S_OK;
}
void GD_Tool::Mainframework::DX11::InvalidateDeviceObjects()
{
	SafeRelease(m_pBackBuffer);
	SafeRelease(m_pDepthStencilBuffer);
	SafeRelease(m_pDepthStencilView);
}
void GD_Tool::Mainframework::DX11::CleanupRenderTarget()
{
	SafeRelease(m_pBackBuffer);
}
void GD_Tool::Mainframework::DX11::CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	m_pBaseDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pBackBuffer);
	pBackBuffer->Release();
}
void GD_Tool::Mainframework::DX11::CleanupDeviceD3D()
{
	SafeRelease(m_pSwapChain); 
	SafeRelease(m_pDevice); 
	SafeRelease(m_pDevCon);
	SafeRelease(m_pBaseDevice);
}
namespace
{
	// This is just used to forward Windows messages from a global window
	// procedure to our member function window procedure because we cannot
	// assign a member function to WNDCLASS::lpfnWndProc.
	GD_Tool::Mainframework::DX11* g_pDX11App = nullptr;
}

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return g_pDX11App->MsgProc(hwnd, msg, wParam, lParam);
}
bool GD_Tool::Mainframework::DX11::InitMainWindow()
{
	///\internal Initialize the WNDCLASSEX and set the important things
	WNDCLASSEX wndClass{};
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = MainWndProc;
	wndClass.hInstance = m_hAppInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(m_hAppInstance, MAKEINTRESOURCE(230));
	wndClass.lpszClassName = "Window_Class";
	wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);

	///\internal create a Rectangle to use it for the Window creation. 
	RECT rect{};
	rect.left = 0;
	rect.right = m_resolutionX;
	rect.top = 0;
	rect.bottom = m_resolutionY;

	///\internal Adjusts the Window to the left upper corner
	/*if (!AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, NULL))
		return false;*/
	ATOM atom = 0;
	// registers the current window. 
	atom = RegisterClassEx(&wndClass);
	if (atom == 0)
		return false;
	///\internal Creates the window based on the handle, WNDCLASSEX and the rectangle. 
	m_hMainWnd = CreateWindowEx
	(
		NULL,
		wndClass.lpszClassName,
		"GD_Tool",
		WS_OVERLAPPEDWINDOW,
		200,
		200,
		rect.right,
		rect.bottom,
		NULL,
		NULL,
		m_hAppInstance,
		nullptr
	);
	if (m_hMainWnd == NULL)
		return false;


	
	return true; 
}

bool GD_Tool::Mainframework::DX11::InitDirect3D()
{
	HRESULT hr;
	UINT m4xMsaaQuality = 0;

	

	DXGI_SWAP_CHAIN_DESC scDesc{};

	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferDesc.Width = m_resolutionX;
	scDesc.BufferDesc.Height = m_resolutionY;
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;


	scDesc.BufferCount = 2;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	if (m_enable4xMsaa)
	{
		scDesc.SampleDesc.Count = 4;
		scDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		scDesc.SampleDesc.Count = 1;
		scDesc.SampleDesc.Quality = 0;
	}


	scDesc.OutputWindow = m_hMainWnd;
	scDesc.Windowed = TRUE;

	scDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT createDeviceFlags = 0;
	D3D_FEATURE_LEVEL featureLevel;
#if defined (DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, nullptr, NULL, D3D11_SDK_VERSION, &scDesc, &m_pSwapChain, &m_pDevice, &featureLevel, &m_pDevCon);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to Create Device and Swap Chain ");
		return false;
	}
	if (featureLevel != D3D_FEATURE_LEVEL_11_0 && featureLevel != D3D_FEATURE_LEVEL_11_1)
	{
		MessageBoxW(0, L"Direct3D Feature Level 11 unsupported. ", 0, 0);
		return false;
	}
	hr = m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Mutisamplecheck failed"); 
		return false; 
	}
	assert(m4xMsaaQuality > 0);


	CreateRenderTarget();



	/*D3D11_TEXTURE2D_DESC depthStencilDesc{};

	depthStencilDesc.Width = m_resolutionX;
	depthStencilDesc.Height = m_resolutionY;

	depthStencilDesc.MipLevels = 1;

	depthStencilDesc.ArraySize = 1;

	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	if (m_enable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT; 
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; 
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags = 0; 

	hr = m_pDevice->CreateTexture2D(&depthStencilDesc, 0, &m_pDepthStencilBuffer);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to create the depthstencilbuffer");
		return false;
	}
	hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, 0, &m_pDepthStencilView);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to create the depthstencilView");
		return false;
	}

	m_pDevCon->OMSetRenderTargets(1, &m_pBackBuffer, m_pDepthStencilView);


	
	m_viewPort.TopLeftX = 0;
	m_viewPort.TopLeftY = 0;
	m_viewPort.Width = m_resolutionX;
	m_viewPort.Height = m_resolutionY;
	m_viewPort.MinDepth = 0.0f;
	m_viewPort.MaxDepth = 1.0f;

	m_pDevCon->RSSetViewports(1, &m_viewPort);
*/
	return true;
}



GD_Tool::Mainframework::DX11::DX11(const HINSTANCE& hInstance)
	:m_hAppInstance(hInstance)
	, m_MainWindowCaption(L"Game Designer")
	, m_enable4xMsaa(false)
	, m_hMainWnd(NULL)
	, m_appPaused(false)
	, m_minimized(false)
	, m_maximized(false)
	, m_resizing(false)
	, m_4xMsaaQuality(0)
	, m_pDevice(nullptr)
	,m_pDevCon(nullptr)
	, m_pSwapChain(nullptr)
	, m_pDepthStencilBuffer(nullptr)
	, m_pBackBuffer(nullptr)
	, m_pDepthStencilView(nullptr)
	,m_pBaseDevice(nullptr)
{
	g_pDX11App = this;

}
HINSTANCE GD_Tool::Mainframework::DX11::ApplicationInstance() const
{
	return HINSTANCE();
}
HWND GD_Tool::Mainframework::DX11::MainWindow() const
{
	return HWND();
}
float GD_Tool::Mainframework::DX11::AspectRatio() const
{
	return static_cast<float>(m_resolutionX) / m_resolutionY;
}

bool GD_Tool::Mainframework::DX11::Init(const uint32_t& resolutionX, const uint32_t& resolutionY)
{
	m_resolutionX = resolutionX; 
	m_resolutionY = resolutionY;
	if (!InitMainWindow())
		return false; 
	if (CreateDeviceD3D(m_hMainWnd) < 0)
	{
		CleanupDeviceD3D();
		return false;
	}
	ShowWindow(m_hMainWnd, SW_SHOW);
	UpdateWindow(m_hMainWnd);

	/*if (!InitDirect3D())
		return false; */

	return true; 
}

void GD_Tool::Mainframework::DX11::OnResize()
{
	assert(m_pDevCon);
	assert(m_pDevice);
	assert(m_pSwapChain);

	SafeRelease(m_pBackBuffer);
	SafeRelease(m_pDepthStencilView);
	SafeRelease(m_pDepthStencilBuffer);


	HRESULT hr;

	hr = m_pSwapChain->ResizeBuffers(1, m_resolutionX, m_resolutionY, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to resize swapChainbuffer");
		return;
	}
	ID3D11Texture2D* backBuffer;
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to get buffer of the swapChain");
		SafeRelease(backBuffer);
		return;
	}
	hr = m_pDevice->CreateRenderTargetView(backBuffer, 0, &m_pBackBuffer);
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to create new RenderTargetView after resize");
		SafeRelease(backBuffer);
		return;
	}
	SafeRelease(backBuffer);

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = m_resolutionX;
	depthStencilDesc.Height = m_resolutionY;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	if (m_enable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	hr = m_pDevice->CreateTexture2D(&depthStencilDesc, 0, &m_pDepthStencilBuffer); 
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to create new depthStencil buffer");
		return;
	}
	hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, 0, &m_pDepthStencilView); 
	if (Failed(hr))
	{
		OutputDebugStringW(L"Failed to create new depthStencilView after resize");
		return;
	}

	m_pDevCon->OMSetRenderTargets(1, &m_pBackBuffer, m_pDepthStencilView); 

	m_viewPort.TopLeftX = 0; 
	m_viewPort.TopLeftY = 0; 
	m_viewPort.Width = static_cast<float>(m_resolutionX); 
	m_viewPort.Height = static_cast<float>(m_resolutionY); 
	m_viewPort.MinDepth = 0.0f; 
	m_viewPort.MaxDepth = 1.0f; 
}


LRESULT GD_Tool::Mainframework::DX11::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result;
	switch (msg)
	{
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			m_appPaused = true;
		}
		else
		{
			m_appPaused = false;
		}
		return 0;
	case WM_ENTERSIZEMOVE:
		m_appPaused = true;
		m_resizing = true;
		return 0;
	case WM_EXITSIZEMOVE:
		m_appPaused = false;
		m_resizing = false;
		OnResize();
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_MENUCHAR:
		return MAKELRESULT(0, MNC_CLOSE);
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
	}
	
	return result = DefWindowProc(hwnd, msg, wParam, lParam);
}

void GD_Tool::Mainframework::DX11::Release()
{
	InvalidateDeviceObjects();
	if (m_pDevCon)
		m_pDevCon->ClearState(); 
	if(m_pSwapChain != nullptr)
		m_pSwapChain->SetFullscreenState(FALSE, NULL);
	SafeRelease(m_pDevice);
	SafeRelease(m_pDevCon); 

	
}

GD_Tool::Mainframework::DX11::~DX11()
{
	Release();
}
