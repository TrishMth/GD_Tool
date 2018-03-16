#pragma once
#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#pragma endregion 

namespace RenderLib
{
	namespace Mainframework
	{
		class DX11
		{
		private: // Functions
		public:
			/**
			*Default Constructor for DX11.
			*/
			DX11();
			/**
			*The base function to initialize DX11. 
			*/
			bool Init(HWND hwnd);
			/**
			*Function to release DX11
			*/
			void Release();
			/** 
			*Default Destructor for the DX11 class
			*/
			~DX11();
		private: // Member variables
			IDXGISwapChain* m_swapChain;
			ID3D11Device* m_device; 
			ID3D11DeviceContext* m_devCon;


		};
	}
}