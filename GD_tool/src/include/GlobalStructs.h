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
		struct ProjectPackage
		{
			std::string Name;
			uint32_t ObjIndex; 
			uint32_t VariableIndex; 
			uint32_t FormulaIndex; 
			std::vector<Object*> Objects; 
			std::vector<BaseVariable> Variables; 
			std::vector<Formula*> Formulas; 
		};
	}
}