#pragma once
#pragma region Internal Includes
#include "IntegerVariable.h"
#include "BaseVariable.h"
#include "Object.h"
#include "Formula.h"
#include "GlobalStructs.h"
#include "SaveSystem.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <vector>
#pragma endregion

namespace GD_Tool
{
	namespace Mainframework
	{
		class ProjectManager
		{
		public: 
			/**
			* Default Constructor of the ProjectManager
			* @param name The name of the new Project
			*/
			ProjectManager(const std::string name); 
			/**
			* Function to change the name of the project
			*
			* @param newName The new name of the current project
			*/
			void ChangeName(const std::string newName);
			/**
			* Method to create an object
			*
			* @param name The name of the object you want to create
			* @param index The index of the object 
			*/
			void CreateObject(const std::string& name);
			/**
			* Function to get the vector of the objects of the current project
			*
			* return The vector of the current objects
			*/
			std::vector<Object*> GetObjects();
			/**
			* Function to add an object to the current project
			*
			* @param obj The object you want to add to the current project
			*/
			void AddObject(Object* obj);
			/**
			* Function to create a new Variable in the current project
			*
			*/
			void CreateVariable();
			/**
			* Function to create a new Formula in the current project
			*
			*/
			void CreateFormula(); 
			/**
			* Function to package the project and save the current project
			*
			* @return ProjectPackage The struct of the packaged project.
			*/
			ProjectPackage PackageProject(); 
		private: 
			std::string m_name; 
			uint32_t m_objIndex; 
			uint32_t m_varIndex; 
			uint32_t m_formulaIndex; 
			std::vector<Object*> m_baseObjects;
			std::vector<BaseVariable> m_variables; 
			std::vector<Formula*> m_formulas; 
			SaveSystem* m_saveSystem; 
		};
	}
}