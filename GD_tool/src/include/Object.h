#pragma once
#pragma region Internal Includes
#include "BaseVariable.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <map>
#include <Windows.h>
#include <fstream>
#pragma endregion

namespace GD_Tool
{
	namespace Mainframework
	{
		class ProjectManager;

		class Object
		{
		public: 
			/**
			* Default Constructor of the Object Class
			*/
			Object(const uint32_t& objIndex, const std::string& name); 
			/**
			* Getter function to get the name of the object
			*
			* @return The name of the Object
			*/
			std::string GetName() const { return m_name; }
			/**
			* Method to add another Object to this Object 
			* @param obj The Object you wants to add to the current object
			*/
			void AddObject(Object* obj); 
			/**
			* Method to remove an object from the m_attachedObjs vector
			* @param index The index of the obj you want to remove
			*/
			void RemoveObject(const uint32_t& index); 
			/**
			* Getter function to get the current index of the object
			* 
			* @return The index of the object
			*/
			uint32_t GetIndex() const; 
			/**
			* Getter function to get the attached objs on this object
			*
			* @return The objects attached to this obj
			*/
			std::map<uint32_t, Object*> GetAttachedObjs() const { return m_attachedObjs; }
			/**
			* Getter function to get the index of the attached Objects
			*
			* @return The index of the attached Objects
			*/
			uint32_t GetAttachedIndex() const { return m_attachedIndex; }
			/**
			* Function to create a new variable, this will add the variable directly to the object.
			*
			* @param type The type of the variable you want to create
			* @param name The name of the variable you want to create
			* @param value The default value of the variable you want to create 
			*/
			void CreateVariable(const EVariableTypes& type, const std::string& name, const int32_t& value);
			void CreateVariable(const EVariableTypes& type, const std::string& name, const float& value); 
			void CreateVariable(const EVariableTypes& type, const std::string& name, const double& value); 
			void CreateVariable(const EVariableTypes& type, const std::string& name, const bool& value); 
			/**
			* Method to add some variables to the objcet
			* @param variable The current Variable you want to add to the Object
			*/
			void AddVariable(BaseVariable* variable);
			/**
			* Function to remove a variable from an object
			*
			* @param index The index of the variable you want to remove from the object
			*/
			void RemoveVariable(const uint32_t& index);
			/** 
			* Getter function to get the variables attached to the obj
			* 
			* @return All variables of this obj
			*/
			std::map<uint32_t, BaseVariable*> GetVariables() const {m_variables;}
			/**
			* Function to save the changes of this object
			*
			*/
			void Save();
			/**
			* Deletes the file of the object
			*/
			void Delete();
			/**
			* Default Destructor of the Object Class
			*/		
			~Object(); 
		private: 
			std::map<uint32_t, BaseVariable*> m_variables;
			std::map<uint32_t, Object*> m_attachedObjs; 
			uint32_t m_attachedIndex; 
			uint32_t m_objIndex; 
			uint32_t m_variableIndex; 
			std::string m_name;
			std::string m_fileName;
			bool m_isDirty; 
		};
	}
}