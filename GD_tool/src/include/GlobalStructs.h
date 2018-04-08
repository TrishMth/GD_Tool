#pragma once
#pragma region Internal includes
#include "Object.h"
#include "BaseVariable.h"
#include "Formula.h"
#include "GlobalEnums.h"
#include "imgui.h"
#include "AddNode.h"
#pragma endregion 
#pragma region External includes
#include <string>
#include <map>
#include <DirectXMath.h>
#pragma endregion 

namespace GD_Tool
{
	namespace Mainframework
	{
		struct VERTEX_CONSTANT_BUFFER
		{
			float        mvp[4][4];
		};

		struct MAPVERTEX
		{
			float x = 0, y = 0, z = 0;
			float Color[4]{ 0,0,0,0 };
		};
		struct MAP_VS_CONSTANT_BUFFER
		{
			float x = 0; 
		};
		struct GRAPH_VS_CONSTANT_BUFFER
		{
			float fTime = 0;
		};
		struct GRAPHVERTEX
		{
			float x = 0, y = 0, z = 0;
			float Color[4]{ 0,0,0,0 };
		};
		/**
		* Description struct for the project 
		*/
		struct ProjectDesc
		{
			std::string GetBuffer() const { std::string FullBuffer = Begin + Name; return FullBuffer; }
			std::string Name;
		private:
			std::string Begin = "_pDesc\n";
		};
		/**
		* Description struct for an object
		*/
		struct ObjectDesc
		{
			std::string GetObjDesc() const
			{
				std::string FullBuffer = Begin;
				for (uint32_t i = 0; i < Count; i++)
				{
					FullBuffer.append(Names[i]);
				}
				return FullBuffer;
			}
			uint32_t Count;
			std::vector<std::string> Names;
			std::string Begin = "_objDesc\n";
		};
		/**
		* Description struct for a formula
		*/
		struct FormulaDesc
		{
			std::string GetFormulaDesc() const
			{
				std::string FullBuffer = Begin;
				for (uint32_t i = 0; i < Count; i++)
				{
					FullBuffer.append(Names[i]);
				}
				return FullBuffer;
			}
			uint32_t Count;
			std::vector<std::string> Names;
			std::string Begin = "_FormDesc\n";
			std::string End = "_End\n";
		};
		struct AppConfigDesc
		{
			void SetAppConfigDesc(const std::string& str, const uint32_t& line)
			{
				switch (line)
				{
				case 0: 
					WindowWidth = atoi(str.c_str());
				case 1: 
					WindowHeight = atoi(str.c_str());
				}
			}
			uint32_t WindowWidth = 0; 
			uint32_t WindowHeight = 0;
			bool Maximized = false; 
		};
		
	}
}