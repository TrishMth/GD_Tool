#pragma once
#pragma region Internal includes
#include "Object.h"
#include "BaseVariable.h"
#include "Formula.h"
#pragma endregion 
#pragma region External includes
#include <string>
#include <vector>
#pragma endregion 

namespace GD_Tool
{
	namespace Mainframework
	{
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
				for (int i = 0; i < Count; i++)
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
				for (int i = 0; i < Count; i++)
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
	}
}