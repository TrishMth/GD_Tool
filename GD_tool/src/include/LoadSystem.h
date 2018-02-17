#pragma once
#pragma region Internal Includes
#include "IntegerVariable.h"
#include "BaseVariable.h"
#include "Object.h"
#include "Formula.h"
#include "GlobalStructs.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <vector>
#pragma endregion


namespace GD_Tool
{
	namespace Mainframework
	{
		class LoadSystem
		{
		private: 
			ProjectPackage m_package; 
		public: 
			/**
			* Default Constructor of the LoadSystem 
			*
			*@param package The package of the current project
			*/
			LoadSystem(const ProjectPackage package); 
			/**
			* Default Destructor of the LoadSystem
			*/
			~LoadSystem() {};
		};
	}
}