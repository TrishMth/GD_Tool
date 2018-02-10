#pragma once
#pragma region Internal Includes
#include "IBaseVariable.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#pragma endregion 

namespace GD_Tool
{
	namespace Mainframework
	{
		class IntegerVariable : IBaseVariable
		{
		public:
			/**
			*Default Constructor of the IntegerVariable class which inherits from IBaseVariable
			*
			* @param type The type of the current Variable
			* @param value The value of the current Variable
			*/
			IntegerVariable(const EVariableTypes& type, const int32_t value) :m_value(value), IBaseVariable(type) {};
			/**
			* Getter function, to get the value of the integer variable
			* 
			* @return The value of the integer variable
			*/
			int32_t GetValue() const; 




			/**
			* Operator override for the add operator (int32_t)
			* 
			* @param value The integer value you want to add to the integer variable
			* @return The result of the calculation 
			*/
			int32_t operator+(const int32_t& value) const; 
			/**
			* Operator override for the add operator (IntegerVariable)
			*
			* @param intVar The integer variable you want to add to the current integer variable 
			* @return The result of the calculation
			*/
			int32_t operator+(IntegerVariable* intVar) const; 
			/**
			* Operator override for the add operator (float)
			*
			* @param value The float value you want to add to the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation 
			*/
			int32_t operator+(const float& value) const; 
			/**
			* Operator override for the add operator (FloatVariable)
			* 
			* @param floatVar The float Variable you want to add to the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation 
			*/
			/*int32_t operator+(FloatVariable* floatVar) const; */
			/**
			* Operator override for the substract operator (int32_t)
			*
			* @param value The integer value you want to substract from the integer variable
			* @return The result of the calculation
			*/
			int32_t operator-(const int32_t& value) const;
			/**
			* Operator override for the substract operator (IntegerVariable)
			*
			* @param intVar The integer variable you want to substrac from the current integer variable
			* @return The result of the calculation
			*/
			int32_t operator-(IntegerVariable* intVar) const;
			/**
			* Operator override for the substract operator (float)
			*
			* @param value The float value you want to substract from the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation
			*/
			int32_t operator-(const float& value) const;
			/**
			* Operator override for the substract operator (FloatVariable)
			*
			* @param floatVar The float Variable you want to substract from the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation
			*/
			/*int32_t operator-(FloatVariable* floatVar) const; */
			/**
			* Operator override for the multiplication operator (int32_t)
			*
			* @param value The integer value you want to multiplicate with the integer variable
			* @return The result of the calculation
			*/
			int32_t operator*(const int32_t& value) const;
			/**
			* Operator override for the multiplication operator (IntegerVariable)
			*
			* @param intVar The integer variable you want to multiplicate with the current integer variable
			* @return The result of the calculation
			*/
			int32_t operator*(IntegerVariable* intVar) const;
			/**
			* Operator override for the multiplication operator (float)
			*
			* @param value The float value you want to multiplicate with the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation
			*/
			int32_t operator*(const float& value) const;
			/**
			* Operator override for the multiplication operator (FloatVariable)
			*
			* @param floatVar The float Variable you want to multiplicate with the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation
			*/
			/*int32_t operator*(FloatVariable* floatVar) const; */
			/**
			* Operator override for the multiplication operator (int32_t)
			*
			* @param value The integer value you want to multiplicate with the integer variable
			* @return The result of the calculation
			*/
			int32_t operator/(const int32_t& value) const;
			/**
			* Operator override for the Division operator (IntegerVariable)
			*
			* @param intVar The integer variable you want to divide through the current integer variable
			* @return The result of the calculation
			*/
			int32_t operator/(IntegerVariable* intVar) const;
			/**
			* Operator override for the multiplication operator (float)
			*
			* @param value The float value you want to divide through the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation
			*/
			int32_t operator/(const float& value) const;
			/**
			* Operator override for the multiplication operator (FloatVariable)
			*
			* @param floatVar The float Variable you want to divide through the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation
			*/
			/*int32_t operator/(FloatVariable* floatVar) const; */

			/**
			* The Default Destructor of the IntegerVariable class
			*/
			~IntegerVariable() {};
		private: 
			int32_t m_value; 
		};
	}
}