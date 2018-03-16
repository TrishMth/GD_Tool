#pragma once
#pragma region Internal Includes
#include "BaseNode.h"
#include "BaseVariable.h"
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
		class VariableNodes :public BaseNode
		{
		public:
			/** 
			* Default Constructor of the VariableNodes class which inherist from the BaseNode class
			*/
			VariableNodes(const uint32_t& index) :BaseNode(GlobalEnums::ENodeType::Variable, index){};
			/**
			* The overridden function to save the current node.
			*/
			virtual void Save() final;
			/** 
			* Default Destructor of the VariableNodes class 
			*/
			~VariableNodes() {};
		};
	}
}