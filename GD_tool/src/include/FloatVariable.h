#pragma once
#pragma region Internal Includes
#include "BaseVariable.h"
#include "BaseNode.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#pragma endregion 

namespace GD_Tool
{
	namespace Mainframework
	{
		class FloatVariable : public BaseVariable, public BaseNode
		{
		public: 
			/**
			*Default Constructor of the FloatVariable class which inherits from BaseVariable
			*
			* @param type The type of the current Variable
			* @param value The value of the current Variable
			*/
			FloatVariable(const float& value, const std::string& name);

			float static AddInt(const float& value1, const int32_t& value2) { return value1 + value2; }
			float static AddFloat(const float& value1, const float& value2) { return value1 + value2; }
			float static SubstractInt(const float& value1, const int32_t& value2) { return value1 - value2; }
			float static SubstractFloat(const float& value1, const float& value2) { return value1 - value2; }
			float static MultiplicateInt(const float& value1, const int32_t& value2) { return value1 * value2; }
			float static MultiplicateFloat(const float& value1, const float& value2) { return value1 * value2; }
			float static DivideInt(const float& value1, const int32_t& value2) {return value1 / value2;}
			float static DivideFloat(const float& value1, const float& value2) { return value1 / value2; } 
			bool static Equal(const float& value1, const float& value2); 
			bool static NotEqual(const float& value1, const float& value2); 

			/**
			* Operator override for the add operator (int32_t)
			*
			* @param value The integer value you want to add to the integer variable
			* @return The result of the calculation
			*/
			float operator+(const int32_t& value) const;
			/**
			* Operator override for the add operator (float)
			*
			* @param value The float value you want to add to the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation
			*/
			float operator+(const float& value) const;
			/**
			* Operator override for the substract operator (int32_t)
			*
			* @param value The integer value you want to substract from the integer variable
			* @return The result of the calculation
			*/
			float operator-(const int32_t& value) const;
			/**
			* Operator override for the substract operator (float)
			*
			* @param value The float value you want to substract from the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation
			*/
			float operator-(const float& value) const;
			/**
			* Operator override for the multiplication operator (int32_t)
			*
			* @param value The integer value you want to multiplicate with the integer variable
			* @return The result of the calculation
			*/
			float operator*(const int32_t& value) const;
			/**
			* Operator override for the multiplication operator (float)
			*
			* @param value The float value you want to multiplicate with the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation
			*/
			float operator*(const float& value) const;
			/**
			* Operator override for the multiplication operator (int32_t)
			*
			* @param value The integer value you want to multiplicate with the integer variable
			* @return The result of the calculation
			*/
			float operator/(const int32_t& value) const;
			/**
			* Operator override for the multiplication operator (float)
			*
			* @param value The float value you want to divide through the integer variable.
			* @return The rounded result of the calculation
			*/
			float operator/(const float& value) const;
			/**
			* The Default Destructor of the FloatVariable class
			*/
			~FloatVariable() {};
		private:
			float m_value;
			std::string m_name; 
		};
	}
}