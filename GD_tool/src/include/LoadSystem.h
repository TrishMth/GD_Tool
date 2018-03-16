#pragma once
#pragma region Internal Includes
#include "ProjectManager.h"
#include "GlobalStructs.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <vector>
#include <fstream>
#pragma endregion


namespace GD_Tool
{
	namespace Mainframework
	{
		class LoadSystem
		{
		public:
			/**
			* Loads an existing project
			*
			* @param The filepath of the project to load 
			*/
			static void LoadProject(const std::string& filePath);
			/**
			* Loads the config file of this app
			*/
			static AppConfigDesc LoadConfig();
		private: 
			/**
			* Default Constructor of the Load system
			*
			* @param filePath The path of the project you wanna load 
			*/
			LoadSystem() {};
			/**
			* Creates the default config file. And sets all default settings.
			*/
			static AppConfigDesc CreateDefaultConfigFile(std::fstream& stream, AppConfigDesc& desc);
			/**
			* Static function to load the obj datas from an obj 
			* 
			* @param objName The name of the Object you want to read out the data. 
			* @return True if you could read out the datas of the object, otherwise false. 
			*/
			bool static LoadObjData(const std::string& objName); 
			/**
			* Static function to load the datas of a formula 
			* 
			* @param formName The Name of the Formula you want to read out the data. 
			* @return True if you could read out the datas of the formula, otherwise false. 
			*/
			bool static LoadFormData(const std::string& formName);

		};
	}
}