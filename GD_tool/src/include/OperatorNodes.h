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
			OperatorNodes() : BaseNode(ENodeType::Operator){}
			/**
			* Default Destructor of the OperatorNodes base class
			*/
			~OperatorNodes() {};
		};
	}
}