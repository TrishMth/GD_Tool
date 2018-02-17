#pragma once
#pragma region Internal Includes
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
		class BaseNode
		{
		private:
			const ENodeType m_nodeType;
		public:
			/**
			* Default Constructor of the BaseNode class. Don't use this, only inherit from it.
			* 
			* @param The type of the Node.
			*/
			BaseNode(const ENodeType& type) : m_nodeType(type){};
			/**
			* Getter function to get the type of the node variable
			*
			* @return The type of the Node
			*/
			ENodeType GetNodeType() const { return m_nodeType; };
			/**
			* Default Destructor of the Basenode class
			*/
			~BaseNode() {};
		};
	}
}