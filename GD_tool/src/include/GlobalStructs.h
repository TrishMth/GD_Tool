#pragma once
#pragma region Internal includes
#include "Object.h"
#include "BaseVariable.h"
#include "Formula.h"
#include "GlobalEnums.h"
#include "imgui.h"
#pragma endregion 
#pragma region External includes
#include <string>
#include <map>
#include <list>
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
		struct GraphPoints
		{
			ImVec2 list[100]; 
			
			
			ImVec2 operator[](const uint32_t& index)
			{
				return list[index];
			}
			void SetHeight(const uint32_t& index, const uint32_t& height)
			{
				list[index].y = height;
			}
		};
		/**
		* Description struct for the project 
		*/
		struct ProjectDesc
		{
			std::string GetBuffer() const { std::string FullBuffer = Begin + Name; return FullBuffer; }
			std::string Name;
			std::string Begin = "_pDesc\n";
		};
		/**
		* Description struct for an object
		*/
		struct ObjectDesc
		{
			
			std::vector<std::string> Names;
			std::string Begin = "_objDesc\n";
		};
		/**
		* Description struct for a formula
		*/
		struct FormulaDesc
		{
		
			std::vector<std::string> Names;
			std::string Begin = "_FormDesc\n";
			std::string End = "_End\n";
		};
		struct AppConfigDesc
		{

			uint32_t WindowWidth = 1600; 
			uint32_t WindowHeight = 900;
			int32_t WindowPosX = 100; 
			int32_t WindowPosY = 100;
			bool Maximized = false; 
			uint32_t Styles = 0;
			bool VSync = 1;
			std::list<std::string> RecentlyOpenedPaths;
			void SetAppConfigDesc(const std::string& str, const uint32_t& line)
			{
				switch (line)
				{
				case 0:
					WindowWidth = atoi(str.c_str());
					break;
				case 1:
					WindowHeight = atoi(str.c_str());
					break;
				case 2:
					WindowPosX = atoi(str.c_str());
					break;
				case 3:
					WindowPosY = atoi(str.c_str());
					break;
				case 4:
					Maximized = atoi(str.c_str());
					break;
				case 5:
					Styles = atoi(str.c_str());
					break;
				case 6:
					VSync = atoi(str.c_str());
					break;	
				case 7: 
					if(!str.empty())
						RecentlyOpenedPaths.push_back(str);
					break; 
				case 8: 
					if(!str.empty())
						RecentlyOpenedPaths.push_back(str);
					break;
				case 9:
					if(!str.empty())
						RecentlyOpenedPaths.push_back(str); 
					break;
				}
			}
			void CheckRecentlyOpenedFiles(const std::string& filePath)
			{
				for (std::list<std::string>::iterator it = RecentlyOpenedPaths.begin(); it != RecentlyOpenedPaths.end(); ++it)
				{
					if (*it == filePath)
					{
						RecentlyOpenedPaths.erase(it);
						break;
					}
					
				}				
			}
		};
		
	}
}