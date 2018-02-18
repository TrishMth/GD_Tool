#pragma once
#pragma region Internal Includes
#include "GlobalEnums.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <cstdint>
#pragma endregion 



namespace GD_Tool
{
	namespace Mainframework
	{
		class BaseVariable
		{
		private: 
			EVariableTypes m_variableType; 
			int32_t m_iValue; 
			float m_fValue; 
			bool m_bValue; 
			double m_dValue; 
			std::string m_name;
			bool m_isPublic; 
		public:
			/** 
			* Default Constructor of the Variable class (int)
			* @param type The type of the Variable you want to create 
			*/
			BaseVariable(const EVariableTypes& type, const std::string& name, const int32_t& value) : m_variableType(type), m_name(name), m_isPublic(true), m_iValue(value), m_fValue(0), m_dValue(0), m_bValue(0) {};
			/**
			* Default Constructor of the Variable class (float)
			* @param type The type of the Variable you want to create
			*/
			BaseVariable(const EVariableTypes& type, const std::string& name, const float& value) : m_variableType(type), m_name(name), m_isPublic(true), m_iValue(0), m_fValue(value), m_dValue(0), m_bValue(0) {};
			/**
			* Default Constructor of the Variable class (bool)
			* @param type The type of the Variable you want to create
			*/
			BaseVariable(const EVariableTypes& type, const std::string& name, const bool& value) : m_variableType(type), m_name(name), m_isPublic(true), m_iValue(0), m_fValue(0), m_dValue(0), m_bValue(value) {};
			/**
			* Default Constructor of the Variable class (double)
			* @param type The type of the Variable you want to create
			*/
			BaseVariable(const EVariableTypes& type, const std::string& name, const double& value) : m_variableType(type), m_name(name), m_isPublic(true), m_iValue(0), m_fValue(0), m_dValue(value), m_bValue(0) {};
			
			/**
			* Getter function to get the name of the variable
			* 
			* @return std::string The name of the variable
			*/
			std::string GetName() { return m_name; }
			/**
			* Changes the visibility of this variable to provide others to see every variable and to don't get overhead of variables in inspector
			*
			*/
			void ChangeVisibility() { m_isPublic = !m_isPublic; }
			/** 
			* Changes the name of the variable
			*
			* @param newName The new name of the variable
			*/
			void ChangeName(const std::string& newName) { m_name = newName; }
			/**
			* Getter method to get the current type of the Variable
			* @return EVariableTypes The type of the current variable
			*/
			EVariableTypes GetType() { return m_variableType; }		
			/** 
			* Default Destructor of the Variable class
			*/
			virtual ~BaseVariable() {};
		};
	}
}