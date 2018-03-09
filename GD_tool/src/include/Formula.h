#pragma once
#pragma region Internal Includes
#include "VariableNodes.h"
#include "OperatorNodes.h"
#include "GlobalEnums.h"
#include "BaseNode.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <vector>
#include <map>
#include <fstream>
#pragma endregion 

namespace GD_Tool
{
	namespace Mainframework
	{
		class ProjectManager;

		class Formula
		{
		private: 
			std::map<uint32_t, BaseNode*> m_nodes;
			uint32_t m_nodeIndex; 
			std::string m_name; 
			std::string m_fileName;
			bool m_isDirty; 
			ProjectManager* m_pProMan;
		public: 
			/** 
			* Default Constructor of the Formula class
			*
			* @param variable The variable to start the node 
			*/
			Formula(std::string name, ProjectManager* proMan);
			/**
			* Getter function to get the name of the current formula
			*
			* @return std::string The name of the current formula
			*/
			std::string GetName() const { return m_name; }
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
			* Function to remove a node from the current Formula. It's already stored. 
			* 
			* @param node The node you wanna remove from the current formula
			*/
			void RemoveNode(BaseNode* node); 
			/**
			* Function to save the current formula 
			*
			*/
			void Save();
			/**
			* Delete formula file
			*
			*/
			void Delete();
			/**
			* Default Destructor of the Formula class
			*/
			~Formula() { };
		};
	}
}