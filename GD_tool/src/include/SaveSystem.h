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
			
		public: 
			/**
			* Default Constructor of the SaveSystem class 
			*
			* @param name The name of the current Project as SaveFile name to save the configs of the project.
			*/
			SaveSystem(std::string name);
			/**
			* Function to save the configs of the current project
			* 
			* @param name The name of the project. It's the name of the config file. 
			*/
			void SaveProject(std::string name);
			/**
			* Function to save a created object. Will executed every time, when an object is created 
			* and every time the user wants to save the object and the object is dirty.
			* 
			*/
			void SaveObject(Object* obj);
			/** Function to save a created node. Will executed every time a node will get created and the user wants to save 
			* the node while it's dirty
			*/
			void SaveNode(BaseNode* node);
			/**
			* Default Destructor of the Savesystem
			*/
			~SaveSystem(); 
	
		};
	}
}