#include "include\SaveSystem.h"

void GD_Tool::Mainframework::SaveSystem::BreakDownStruct()
{
	std::string informations; 
	informations.append((m_currentProject.Name + "\n").c_str());
	informations.append((std::to_string(m_currentProject.ObjIndex) + "\n").c_str());
	informations.append((std::to_string(m_currentProject.VariableIndex) + "\n").c_str());
	informations.append((std::to_string(m_currentProject.FormulaIndex) + "\n").c_str()); 
	for (int i = 0; i < m_currentProject.Objects.size(); i++)
	{
		informations.append(SpreadOutObject(m_currentProject.Objects[i]).c_str()); 
	}

}



std::string GD_Tool::Mainframework::SaveSystem::SpreadOutObject(Object * obj)
{
	std::string infos; 
	infos.append((obj->GetName() + "\n").c_str());
	infos.append((std::to_string(obj->GetIndex()) + "\n").c_str());
	for (int i = 0; i < obj->GetVariables().size(); i++)
	{
		infos.append((obj->GetVariables()[i].GetName() + "\n").c_str());
		infos.append((std::to_string(obj->GetVariables()[i].GetValue()) + "\n").c_str());
	}
	for (int i = 0; i < obj->GetAttachedObjs().size(); i++)
		SpreadOutObject(obj->GetAttachedObjs()[i]);
	
	return infos; 
}

void GD_Tool::Mainframework::SaveSystem::SaveProject(std::string informationsToSave)
{

}

GD_Tool::Mainframework::SaveSystem::SaveSystem(const ProjectPackage package)
	:m_currentProject(package)
{
	BreakDownStruct();
}


