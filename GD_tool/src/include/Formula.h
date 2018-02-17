#pragma once
#pragma region Internal Includes
#include "BaseNode.h"
#include "OperatorNodes.h"
#include "GlobalEnums.h"
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
			std::vector<BaseNode*> m_nodes; 

			std::string m_name; 
		public: 
			/** 
			* Default Constructor of the Formula class
			*
			* @param variable The variable to start the node 
			*/
			Formula(std::string name) :m_name(name) {};
			/**
			* Function to change the name of the formula
			*
			* @param newName The new name of the formula
			*/
			void ChangeName(std::string name) { m_name = name; }
			/**
			* Function to create a node within the formula
			* 
			* @param varType The Variabletype of the node you want to create 
			* @param name The name of the node you want to create 
			*/
			void CreateNode(const ENodeType& type);
			/**
			* Function to add a node to the Formula
			* 
			* @param node The node you want to add to the Formula
			*/
			void AddNode(BaseNode* node); 
			/**
			* Default Destructor of the Formula class
			*/
			~Formula() { };
		};
	}
}