#pragma once
#pragma region Internal Includes
#include "BaseNode.h"
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
		class OperatorNodes : public BaseNode
		{

		public: 
			/**
			* Default Constructor of the OperatorNodes base class
			*/
			OperatorNodes(const uint32_t& index) : BaseNode(ENodeType::Operator, index){}
			/**
			* The overridden function to save the current node. 
			*/
			virtual void Save() final; 
			/**
			* Default Destructor of the OperatorNodes base class
			*/
			~OperatorNodes() {};
		};
	}
}