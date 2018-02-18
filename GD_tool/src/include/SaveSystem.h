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
			/**
			* Private function to get all informations out of the package and compress them in a single string to write in a .txt file
			*/
			void BreakDownStruct();
			/**
			* Private function to spread out the objects 
			*
			* @param obj The Object you want to spread out 
			* @return The objects spread out as string 
			*/
			std::string SpreadOutObject(Object* obj);
			/**
			* Private function to save all informations into a text file 
			*/
			void SaveProject(std::string informationsToSave); 
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