#pragma once
#pragma region Internal Includes
#include "IntegerVariable.h"
#include "BaseVariable.h"
#include "Object.h"
#include "Formula.h"
#include "GlobalStructs.h"
#pragma endregion 
#pragma region External Includes
#include "Windows.h"
#include <string>
#include <map>
#include <fstream>
#include <iostream>
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
			* Function to get the current name of the project
			*
			* @return std::string The name of the current Project
			*/
			std::string GetName() const { return m_name; }
			/**
			* Getter function to get the filepath of the current project
			*
			* @param std::string The filepath of the current project
			*/
			std::string GetFilePath() const { return m_filePath; }
			/**
			* Function to remove an object from the project
			*
			* @index Index of the object you want to remove from the project
			*/
			void RemoveObject(const uint32_t& index);
			/**
			* Function to get the vector of the objects of the current project
			*
			* return The vector of the current objects
			*/
			std::map<uint32_t, Object*> GetObjects();
			/**
			* Getter function to get the map of the current formulas
			*
			* @return std::map<uint32_t, Formula*> The map of the formulas the project has
			*/
			std::map<uint32_t, Formula*> GetFormulas();
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
			void CreateFormula(const std::string& name); 
			/**
			* Function to remove a formula from the current project. 
			* 
			* @param index The index of the formula you want to remove from the current project
			*/
			void RemoveFormula(const uint32_t& index);
			/**
			* Function to save the current Project with its dependencies. 
			* 
			*/
			void Save();
			/**
			* Deletes the project file
			*
			*/
			void Delete();
			/** 
			* Default Destructor of the ProjectManager
			*/
			~ProjectManager();
		private: 
			std::string m_name; 
			std::string m_filePath;
			std::string m_fileName;
			uint32_t m_objIndex; 
			uint32_t m_formulaIndex; 
			std::map<uint32_t, Object*> m_baseObjects;
			std::map<uint32_t, Formula*> m_formulas; 
			bool m_isDirty; 
		};
	}
}