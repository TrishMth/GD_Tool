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
			* The Default Destructor of the IntegerVariable class
			*/
			~IntegerVariable() {};
		private: 
			int32_t m_value; 
		};
	}
}