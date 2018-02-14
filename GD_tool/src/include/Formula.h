#pragma once
#pragma region Internal Includes
#include "FloatVariable.h"
#include "IntegerVariable.h"
#include "FloatAddFloatNode.h"
#include "FloatAddIntNode.h"
#include "IntAddFloatNode.h"
#include "IntAddIntNode.h"
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
		class Formula
		{
		private: 
			BaseVariable m_variable;
			std::vector<BaseNode*> m_nodes; 
		public: 
			/** 
			* Default Constructor of the Formula class
			*
			* @param variable The variable to start the node 
			*/
			Formula(const BaseVariable& variable) :m_variable(variable) {};
			/**
			* Function to add a node to the Formula
			* 
			* @param node The node you want to add to the Formula
			*/
			bool AddNode(BaseNode* node); 
			/**
			* Default Destructor of the Formula class
			*/
			~Formula() {};
		};
	}
}