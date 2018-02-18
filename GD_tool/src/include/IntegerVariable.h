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
		class IntegerVariable : public BaseVariable, public BaseNode
		{
		public:
			/**
			* Default Constructor of the IntegerVariable class which inherits from IVariable
			*
			* @param type The type of the current Variable
			* @param value The value of the current Variable
			*/
			IntegerVariable(const int32_t& value, const std::string& name);
			/**
			* Getter function to get the value of the Variable
			*
			* @return The value of the variable
			*/
			int32_t GetValue() const; 
			/**
			* Setter function to change the value of this Integer manually
			* 
			* @param value The new value of this integer
			*/
			void SetValue(const int32_t& value); 
			/**
			* Setter function to change the value of this Integer maually 
			* 
			* @param value The float value you want to set as value of this integer. (Warning: possible Data loss!)
			*/
			void SetValue(const float& value); 
			/**
			* Static function to add an int variable to another
			* 
			* @param value1 The integer value you want to add another to
			* @param value2 The integer value you want to add to the other value.
			* @return The calculated value
			*/
			int32_t static AddInt(const int32_t& value1, const int32_t& value2) { return value1 + value2;  }
			/**
			* Static function to add a float value to an integer value 
			* 
			* @param value1 The value you want to add another to 
			* @param value2 The value you want to add to an other value
			* @return The calculated value as float value
			*/
			float static AddFloat(const float& value1, const float& value2) { return value1 + value2; }
			
			/**
			* Static function to substract an integer value from another 
			* 
			* @param value1 The value where you want to substract the other from 
			* @param value2 The value you want to substract from the other
			* @return The calculated result as int value
			*/
			int32_t static SubstractInt(const int32_t& value1, const int32_t& value2) { return value1 - value2; }
			/**
			* Static function to substract a float value from an integer value 
			* 
			* @param value1 The value you want to substract the other from 
			* @param value2 The value you want to substract from the other
			* @return The calculated result as float value 
			*/
			float static SubstractFloat(const int32_t& value1, const float& value2) { return value1 - value2; }

			/**
			* Static function to multiplicate an integer with another 
			* 
			* @param value1 The value you want to multiplicate another to 
			* @param value2 The value you want to multiplicate to the other 
			* @return The calculated result as int value
			*/
			int32_t static MultiplicatInt(const int32_t& value1, const int32_t& value2) { return value1*value2; }
			/**
			* Static function to multiplicate an float to an integer value 
			* 
			* @param value1 The value you want to multiplicate another to 
			* @param value2 The value you want to multiplicate to the other 
			* @return The calculcated result as float value 
			*/
			float static MultiplicateFloat(const int32_t& value1, const float& value2) { return value1*value2;  }
			
			/**
			* Static function to divide an integer through another 
			*
			* @param value1 The value where you want to divide through 
			* @param value2 The value you want to divide through the other 
			* @return The calculated result as int value 
			*/
			int32_t static DivideInt(const int32_t& value1, const int32_t& value2) { return value1 / value2; }
			/** 
			* Static function to divide an float through an integer value 
			* 
			* @param value1 The value where you want to divide through 
			* @param value2 The value you want to divide through the other 
			* @return The calculated result as float value
			*/
			float static DivideFloat(const int32_t& value1, const float& value2) { return value1 / value2;  }

			bool static Equal(const int32_t& value1, const int32_t value2) { return value1 == value2 ? true : false; }

			bool static NotEqual(const int32_t& value1, const int32_t value2) { return value1 != value2 ? true : false; }



			/**
			* Operator override for the add operator (int32_t)
			* 
			* @param value The integer value you want to add to the integer variable
			* @return The result of the calculation 
			*/
			int32_t operator+(const int32_t& value) const;  
			/**
			* Operator override for the add operator (float)
			*
			* @param value The float value you want to add to the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation 
			*/
			int32_t operator+(const float& value) const; 
			/**
			* Operator override for the substract operator (int32_t)
			*
			* @param value The integer value you want to substract from the integer variable
			* @return The result of the calculation
			*/
			int32_t operator-(const int32_t& value) const;
			/**
			* Operator override for the substract operator (float)
			*
			* @param value The float value you want to substract from the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation
			*/
			int32_t operator-(const float& value) const;
			/**
			* Operator override for the multiplication operator (int32_t)
			*
			* @param value The integer value you want to multiplicate with the integer variable
			* @return The result of the calculation
			*/
			int32_t operator*(const int32_t& value) const;
			/**
			* Operator override for the multiplication operator (float)
			*
			* @param value The float value you want to multiplicate with the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation
			*/
			int32_t operator*(const float& value) const;
			/**
			* Operator override for the multiplication operator (int32_t)
			*
			* @param value The integer value you want to multiplicate with the integer variable
			* @return The result of the calculation
			*/
			int32_t operator/(const int32_t& value) const;
			/**
			* Operator override for the multiplication operator (float)
			*
			* @param value The float value you want to divide through the integer variable. Warning possible data loss cause of rounding!
			* @return The rounded result of the calculation
			*/
			int32_t operator/(const float& value) const; 

			/**
			* The Default Destructor of the IntegerVariable class
			*/
			~IntegerVariable() {};

		};
	}
}