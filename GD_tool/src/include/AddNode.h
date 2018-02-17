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
		class AddNote : public OperatorNodes
		{
		private: 
			float m_baseValue; 
			float m_summandValue;
		public: 
			/**
			* Default Constructor of the Addnote class which inherits from the OperatorNodes base
			*/
			AddNote() {}
			/**
			* Function to set the base of the operation(int). 
			* 
			* @param base The value of the base of the operation 
			*/
			void SetBase(const float& base) { m_baseValue = base; }
			/**
			* Function to set the summand of the operation 
			* 
			* @param sum The value of the summand of the operation
			*/
			void SetSummand(const float& sum) { m_summandValue = sum; }
			/**
			* Getter function to get the result of the operation
			* 
			* @return The result of the operation 
			*/
			float GetResult() const { return m_baseValue + m_summandValue; }
			/**
			* Default Destructof of the AddNote class
			*/
			~AddNote() {}
		};
	}
}