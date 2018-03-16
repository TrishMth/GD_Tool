#include "include\Formula.h"
#include "include\ProjectManager.h"

GD_Tool::Mainframework::Formula::Formula(std::string name)
	:m_name(name)
	, m_nodeIndex(0)
	, m_isDirty(true)
{
	Save();
}

void GD_Tool::Mainframework::Formula::CreateNode(const GlobalEnums::ENodeType& type)
{
	switch (type)
	{
		case GlobalEnums::ENodeType::Variable:
		{
			VariableNodes* newNode = new VariableNodes(m_nodeIndex);
			AddNode(newNode);
		}
			break;
		case GlobalEnums::ENodeType::Operator:
		{
			OperatorNodes* newNode = new OperatorNodes(m_nodeIndex);
			AddNode(newNode);
		}
			break;
	}	
}

bool GD_Tool::Mainframework::Formula::ConnectNodes(BaseNode * begNode, BaseNode * endNode)
{
	begNode->SetNextNode(endNode); 
	endNode->SetPrevNode(begNode); 
	return true; 
}

void GD_Tool::Mainframework::Formula::AddNode(BaseNode* node)
{	
	m_nodes.insert(std::pair<uint32_t, BaseNode*>(m_nodeIndex, node));
	m_nodeIndex++;
}

void GD_Tool::Mainframework::Formula::RemoveNode(BaseNode* node)
{
	m_nodes.erase(node->GetIndex());
}

void GD_Tool::Mainframework::Formula::Save()
{
	if (m_isDirty)
	{
		std::string projectFilePath = ProjectManager::GetInstance().GetFilePath() + "//Formulas"; 
		CreateDirectory(projectFilePath.c_str(), NULL);

		std::fstream fileStream; 
		m_fileName = projectFilePath + "//" + m_name + "_Formula.txt";

		fileStream.open(m_fileName, std::fstream::out);
		if (fileStream.is_open())
		{
			m_isDirty = false;
		}
		fileStream.close();
		
		
	}
}

void GD_Tool::Mainframework::Formula::Delete()
{
	remove(m_fileName.c_str());
}
