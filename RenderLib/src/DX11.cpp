#include "include\DX11.h"

RenderLib::Mainframework::DX11::DX11()
{

}
//Saferelease Template to Release the Pointer in DX11 safely
template<typename T> void SafeRelease(T*& aPointer)
{
	if (aPointer != nullptr)
	{
		aPointer->Release();
		aPointer = nullptr;
	}
}
//function to check the HRESULT of some functions
bool Failed(HRESULT aResult)
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
bool RenderLib::Mainframework::DX11::Init(HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC scDesc{};
	scDesc.BufferCount = 1; 
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.OutputWindow = hwnd; 
	scDesc.SampleDesc.Count = 4; 
	scDesc.Windowed = TRUE; 

	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scDesc,
		&m_swapChain,
		&m_device,
		NULL,
		&m_devCon);

	return true; 
}

void RenderLib::Mainframework::DX11::Release()
{
	SafeRelease(m_swapChain); 
	SafeRelease(m_device); 
	SafeRelease(m_devCon); 
}

RenderLib::Mainframework::DX11::~DX11()
{
	Release();
}
