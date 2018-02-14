#pragma once
#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
#include <string>
#include <cstdint>
#pragma endregion 

enum class ENodeType
{
	Integer, 
	Boolean, 
	Float, 
	Double, 
	Operator
};

namespace GD_Tool
{
	namespace Mainframework
	{
		class BaseNode
		{
		private:
			const ENodeType m_varType;
		public:
			/**
			* Default Constructor of the BaseNode class. Don't use this, only inherit from it.
			* 
			* @param The type of the Node.
			*/
			BaseNode(const ENodeType& type) : m_varType(type){};
			/**
			* Getter function to get the type of the node variable
			*
			* @return The type of the Node
			*/
			ENodeType GetVarType() const { return m_varType; };
			/**
			* Default Destructor of the Basenode class
			*/
			~BaseNode() {};
		};
	}
}