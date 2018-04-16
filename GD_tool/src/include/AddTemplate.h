#pragma once
#pragma region Internal Includes
#include "OperatorNodes.h"
#include "GlobalEnums.h"
#include "VariableNodes.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <cstdint>
#pragma endregion 

namespace GD_Tool
{
	namespace Mainframework
	{
		template<typename T1, typename T2, typename T3>
		class AddTemplate
		{
		private: 
			T1 m_baseValue; 
			T2 m_summandValue;
		public: 
			/**
			* Default Constructor of the Addnote class which inherits from the OperatorNodes base
			*/
			AddTemplate(const uint32_t& index) {}
			/**
			* Function to set the base of the operation(int). 
			* 
			* @param base The value of the base of the operation 
			*/
			void SetBase(const T1& base) { m_baseValue = base; }
			/**
			* Function to set the summand of the operation 
			* 
			* @param sum The value of the summand of the operation
			*/
			void SetSummand(const T2& sum) { m_summandValue = sum; }
			/**
			* Getter function to get the result of the operation
			* 
			* @return The result of the operation 
			*/
			T3 GetResult() const { return m_baseValue + m_summandValue; }
			/**
			* Default Destructof of the AddNote class
			*/
			~AddTemplate() {}
		};
	}
}