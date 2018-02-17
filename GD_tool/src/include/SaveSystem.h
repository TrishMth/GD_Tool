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
		class SaveSystem
		{
		private: 
			ProjectPackage m_currentProject; 
		public: 
			/**
			* Default Constructor of the SaveSystem
			* 
			* @param package The package of the current project to save it
			*/
			SaveSystem(const ProjectPackage package); 
			/**
			*Default Destructor of the SaveSystem 
			*/
			~SaveSystem() {};
		};
	}
}