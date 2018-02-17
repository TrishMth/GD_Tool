#pragma once
#pragma region Internal Includes
#include "BaseVariable.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <vector>
#pragma endregion

namespace GD_Tool
{
	namespace Mainframework
	{
		class Object
		{
		public: 
			/**
			* Default Constructor of the Object Class
			*/
			Object(const uint32_t& objIndex, const std::string& name); 
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
			* Setter function to re-set the index of the object
			* 
			* @param index The new index you want to set to the object
			*/
			void SetIndex(const uint32_t& index);
			/**
			* Method to add some variables to the objcet
			* @param variable The current Variable you want to add to the Object
			*/
			void AddVariable(const BaseVariable& variable);
			/** 
			* Getter function to get the variables attached to the obj
			* 
			* @return All variables of this obj
			*/
			std::vector<BaseVariable> GetVariables() const ; 
			/**
			* Default Destructor of the Object Class
			*/
			~Object(); 
		private: 
			std::vector<BaseVariable> m_variables;
			std::vector<Object*> m_attachedObjs; 
			uint32_t m_objIndex; 
			std::string m_name;
		};
	}
}