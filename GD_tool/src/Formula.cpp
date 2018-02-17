#include "include\Formula.h"

void GD_Tool::Mainframework::Formula::CreateNode(const ENodeType& type)
{
	BaseNode* newNode = new BaseNode(type); 
	AddNode(newNode); 
}

void GD_Tool::Mainframework::Formula::AddNode(BaseNode* node)
{
	m_nodes.push_back(node);
}