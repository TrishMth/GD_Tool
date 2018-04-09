#pragma once
#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
#include <D3D11.h>
#include <D3Dcompiler.h>
#include <cstdint>
#include <cassert>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <sstream>
#include <windowsx.h>
#include <strsafe.h>
#pragma endregion 



namespace GD_Tool
{
	namespace Mainframework
	{
		class DX11
		{
		private: // Functions

		protected: 
			//Saferelease Template to Release the Pointer in DX11 safely
			template<typename T> void SafeRelease(T*& aPointer)
			{
				if (aPointer != nullptr)
				{
					aPointer->Release();
					aPointer = nullptr;
				}
			}
			/**
			*Function to release DX11
			*/
			void Release();
			bool InitMainWindow(); 
			bool InitDirect3D(); 
			bool Failed(HRESULT aResult);
			HRESULT CreateDeviceD3D(HWND hwnd);
			virtual void InvalidateDeviceObjects();
			void CleanupRenderTarget();
			void CreateRenderTarget();
			void CleanupDeviceD3D();

		public:
			/**
			*Default Constructor for DX11.
			*/
			DX11(const HINSTANCE& hInstance);
			HINSTANCE ApplicationInstance() const; 
			HWND MainWindow() const; 
			float AspectRatio() const; 

			virtual int32_t Run() = 0;

			/**
			*The base function to initialize DX11. 
			*/
			virtual bool Init(const uint32_t& resolutionX, const uint32_t& resolutionY);
			virtual void OnResize(); 
			virtual void DrawScene() = 0; 
			virtual LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); 

			virtual void OnMouseDown(const WPARAM& btnState,const int32_t& x, const int32_t& y) {}; 
			virtual void OnMouseUp(const WPARAM& btnState, const int32_t& x,const int32_t& y) {}; 
			virtual void OnMouseMove(const WPARAM& btnState, const int32_t&x, const int32_t& y) {};
			/** 
			*Default Destructor for the DX11 class
			*/
			virtual ~DX11();
		private: // Member variables
		protected:

			

			HINSTANCE m_hAppInstance{};
			HWND m_hMainWnd{};
			D3D11_VIEWPORT m_viewPort{};

			bool m_appPaused; 
			bool m_minimized; 
			bool m_maximized; 
			bool m_resizing; 
			UINT m_4xMsaaQuality;
			uint32_t m_resolutionX; 
			uint32_t m_resolutionY; 
			int64_t m_time;
			int64_t m_ticksPerSecond;

			IDXGISwapChain* m_pSwapChain;
			ID3D11Device* m_pDevice; 
			ID3D11DeviceContext* m_pDevCon;
			ID3D11RenderTargetView * m_pBackBuffer;
			ID3D11Texture2D* m_pDepthStencilBuffer; 
			ID3D11DepthStencilView* m_pDepthStencilView; 
			ID3D11Device * m_pBaseDevice;

			std::wstring m_MainWindowCaption;

			bool m_enable4xMsaa;

		};
	}
}