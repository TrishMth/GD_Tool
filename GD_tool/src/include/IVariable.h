#pragma once
#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
#include <string>
#include <cstdint>
#pragma endregion 

enum class EVariableTypes
{
	Integer, 
	Boolean, 
	Float, 
	Double, 
};

namespace GD_Tool
{
	namespace Mainframework
	{
		class IVariable
		{
		public:
			/** 
			* Default Constructor of the Variable class
			* @param type The type of the Variable you want to create 
			*/
			IVariable(const EVariableTypes& type, const std::string& name) : m_variableType(type), m_name(name) {};
			/**
			* Getter function to get the name of the variable
			* 
			* @return std::string The name of the variable
			*/
			std::string GetName() { return m_name; }
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
			~IVariable() {};
		private: 
			EVariableTypes m_variableType; 
			std::string m_name;
		};
	}
}