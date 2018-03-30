#pragma once
#pragma region Internal Includes
#include "DX11.h"
#include "GlobalStructs.h"
#include "DXDefines.h"
#include "GlobalEnums.h"
#pragma endregion 
#pragma region External Includes
#include <DirectXMath.h>
#pragma endregion 

namespace GD_Tool
{
	namespace Mainframework
	{
		class DX11Map : public DX11
		{
		public:
			DX11Map(HINSTANCE hInstance, const GlobalEnums::EMapSizes& mapSize);
			virtual ~DX11Map();
			virtual bool Init(const uint32_t& resolutionX, const uint32_t& resolutionY) final;
			virtual int32_t Run() final;
			virtual void OnResize() final;
			virtual void UpdateScene();
			virtual void DrawScene() final;
			virtual LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) final;

			void ReleaseMap();

		private: 
			void BuildShader();
			void BuildBuffers();


			ID3D11Buffer * m_pMapVertexBuffer;
			ID3D11Buffer* m_pMapConstBuffer;
			ID3D11VertexShader* m_pVShader;
			ID3D11PixelShader* m_pPShader;
			MAPVERTEX* m_pVertBuf;
			MAP_VS_CONSTANT_BUFFER* m_pConstBuf = (MAP_VS_CONSTANT_BUFFER*)_aligned_malloc(sizeof(MAP_VS_CONSTANT_BUFFER), 16);

			ID3D11InputLayout* m_pInputLayout;
		};
	}
}