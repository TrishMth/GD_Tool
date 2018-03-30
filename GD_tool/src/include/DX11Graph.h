#pragma once
#pragma region Internal Includes
#include "DX11.h"
#include "GlobalStructs.h"
#pragma endregion 
#pragma region External Includes
#include <DirectXMath.h>
#pragma endregion 

namespace GD_Tool
{
	namespace Mainframework
	{
	
	
		class DX11Graph : public DX11
		{
			
		public: 
			/**
			* Default Constructor of the DX11 Graph
			*/
			DX11Graph(HINSTANCE hInstance);
			/**
			* Default Destructor of the DX11 Graph
			*/
			virtual ~DX11Graph();
			/**
			* Initializes the DX11 graph
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
			* Function which updates the current graphscene
			*/
			virtual void UpdateScene(); 
			/**
			* Draws the current Graph to the screen
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
			void ReleaseGraph(); 
			/**
			* Sets new points to the height of the graph, to update the vertex buffer of the Graph
			* 
			* @param val The new y-value of the graph on a specific x-axis value
			* @param index The x-value where to set the new y-value of the graph
			*/
			void SetNewGraphHeight(const float& val, const uint32_t& index);
			/**
			* Sets the new constant buffer and updates the values of it
			*
			* @param constBuf The new constant Buffer of the graph 
			*/
			void SetNewConstBuffer(GRAPH_VS_CONSTANT_BUFFER* constBuf);
			/**
			* Getter function of the current constant buffer
			*
			* @return The constant buffer of the graph 
			*/
			GRAPH_VS_CONSTANT_BUFFER* GetConstBuffer() const;
		private: 
			/**
			* Updates the current constant buffer
			* 
			* @return True if the update was successful otherwise false
			*/
			bool UpdateConstBuf();
			/**
			* Updates the current vertex buffer
			* 
			* @return True if the update was successful otherwise false
			*/
			bool UpdateVertBuf();
			/**
			* Reads out the Vertex and Pixel Shader and build them
			*/
			void BuildShader(); 
			/**
			* Build the vertex and constant buffer
			*/
			void BuildBuffers(); 
			/**
			* Creates a grid with the incoming size
			*
			* @param width The width of the grid.
			* @param depth The depth of the grid. 
			* @param vCntX The vertex count on the x axis
			* @param vCntZ The vertex count on the z axis. 
			*/
			void CreateGrid(const float& width, const float& height, const uint32_t& vCntX, const uint32_t& vCntY);
		private: 
			ID3D11Buffer* m_pGraphVertexBuffer;
			ID3D11Buffer* m_pGraphConstBuffer;
			ID3D11VertexShader* m_pVShader; 
			ID3D11PixelShader* m_pPShader;
			GRAPHVERTEX m_pVertBuf[200];
			GRAPH_VS_CONSTANT_BUFFER* m_pConstBuf = (GRAPH_VS_CONSTANT_BUFFER*)_aligned_malloc(sizeof(GRAPH_VS_CONSTANT_BUFFER), 16);
			
			ID3D11InputLayout* m_pInputLayout;

			POINT m_lastMousePos{};
		};
	}
}