#include "include\Formula.h"

bool GD_Tool::Mainframework::Formula::AddNode(BaseNode* node)
{
	if (m_variable.GetType == node->GetVarType())
	{
		m_nodes.push_back(node);
		return true;
	}
	else
		return false;
}