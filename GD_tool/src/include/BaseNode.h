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
			const GlobalEnums::ENodeType m_nodeType;
			const uint32_t m_formulaIndex; 
			BaseNode* m_pNextNode;
			BaseNode* m_pPrevNode;
		public:
			/**
			* Default Constructor of the BaseNode class. Don't use this, only inherit from it.
			* 
			* @param The type of the Node.
			*/
			BaseNode(const GlobalEnums::ENodeType& type, const uint32_t& index) : m_nodeType(type), m_formulaIndex(index), m_pNextNode(nullptr), m_pPrevNode(nullptr) {};
			/**
			* Setter function to set the node, this node is connected to
			* 
			*/
			void SetNextNode(BaseNode* nextNode) { m_pNextNode = nextNode; }
			/**
			* Setter function to set the node, this node is coming from.
			*/
			void SetPrevNode(BaseNode* prevNode) { m_pPrevNode = prevNode; }
			/**
			* Pure virtual function to save the node. It's overridden in the base files of the inherited classes
			*
			*/
			virtual void Save() = 0;
			/**
			* Getter function to get the index of the current node
			*/
			const uint32_t& GetIndex() { return m_formulaIndex; }
			/**
			* Getter function to get the type of the node variable
			*
			* @return The type of the Node
			*/
			GlobalEnums::ENodeType GetNodeType() const { return m_nodeType; };
			/**
			* Default Destructor of the Basenode class
			*/
			~BaseNode() { delete m_pNextNode; delete m_pPrevNode; };
		};
	}
}