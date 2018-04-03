#pragma once
#pragma region Internal Includes
#include "DX11.h"
#include "GlobalStructs.h"
#include "imgui.h"
#include "BaseGUI.h"
#pragma endregion 
#define DIRECTINPUT_VERSION 0x0800
#pragma region External Includes
#include <dinput.h>
#include <DirectXMath.h>
#pragma endregion 



namespace GD_Tool
{
	namespace Mainframework
	{
		class DX11BaseWindow :public DX11
		{
		public:
			DX11BaseWindow(HINSTANCE hInstance);
			virtual ~DX11BaseWindow();
			/**
			* Initializes the DX11 base window
			*
			* @param resolutionX The resolution of the x-axis the window the graph should appear has.
			* @param resolutionY The resolution of the y-axis the window the graph should appear has.
			* @return returns true if the initialization was successful, otherwise false
			*/
			virtual bool Init(const uint32_t& resolutionX, const uint32_t& resolutionY) final;
			/**
			* Run function which draws the current graph and receives the messages from the window to update the graph.
			*
			* @return the value of the messages which are called from the window.
			*/
			virtual int32_t Run() final;
			/**
			* Function which is called, whenever the window is resizing
			*/
			virtual void OnResize() final;
			/**
			* Function which updates the current scene
			*/
			virtual void UpdateScene(const float& dTime);
			/**
			* Draws the current Window to the screen
			*/
			virtual void DrawScene() final;
			/**
			* The function which catch ups the messages from the window and returns the result.
			*
			* @param hwnd The Window handle of the current window
			* @param msg The messages of the current window
			* @param wParam Parameters of the message which are important to process the message
			* @param lParam Parameters of the message which are important to process the message
			* @return The result of the message
			*/
			virtual LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) final;
			/**
			* Safe releases the member of the graph
			*/
			void ReleaseWindow();
			
		private:
			void RenderDrawData(ImDrawData * draw_data);
			void CreateFontsTexture();
			void NewFrame();
			bool UpdateCursor();
			bool WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
			virtual void InvalidateDeviceObjects() final;
			/**
			* Reads out the Vertex and Pixel Shader and build them
			*/
			void BuildShader();
			/**
			* Build the vertex and constant buffer
			*/
			void BuildBuffers();
		private:
			ID3D11Buffer * m_pBaseVertexBuffer;
			ID3D11Buffer* m_pBaseIndexBuffer;
			ID3D11Buffer* m_pBaseConstBuffer;
			ID3D11VertexShader* m_pVShader;
			ID3D11PixelShader* m_pPShader;
			ID3D11BlendState* m_pBlendState;
			ID3D11SamplerState* m_pFontSampler;
			ID3D11InputLayout* m_pInputLayout;
			ID3D11DepthStencilState* m_pDepthStencilState;
			ID3D11RasterizerState* m_pRasterizerState;
			ID3D11ShaderResourceView* m_pFontTexView;

			

			POINT m_lastMousePos{};
		};
	}
}