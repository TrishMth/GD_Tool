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
	String
};

namespace GD_Tool
{
	namespace Mainframework
	{
		class IBaseVariable
		{
		public:
			/** 
			* Default Constructor of the Variable class
			* @param type The type of the Variable you want to create 
			*/
			IBaseVariable(const EVariableTypes& type) : m_variableType(type) {};
			/**
			* Getter method to get the current type of the Variable
			* return EVariableTypes The type of the current variable
			*/
			EVariableTypes GetType() { return m_variableType; };
			/**
			* Getter pure virtual function to get the current value of the type 
			*/
			virtual void GetValue() = 0; 
			/** 
			* Default Destructor of the Variable class
			*/
			~IBaseVariable() {};
		private: 
			EVariableTypes m_variableType; 
		};
	}
}