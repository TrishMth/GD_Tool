#include "include\ProjectManager.h"

GD_Tool::Mainframework::ProjectManager::ProjectManager(const std::string name)
	:m_name(name)
	,m_objIndex(0)
{
}

void GD_Tool::Mainframework::ProjectManager::ChangeName(const std::string newName)
{
	m_name = newName; 
}

void GD_Tool::Mainframework::ProjectManager::CreateObject(const std::string & name)
{
	Object* newObj = new Object(m_objIndex,name);
	m_objIndex++;
	AddObject(newObj);
}

std::vector<GD_Tool::Mainframework::Object*> GD_Tool::Mainframework::ProjectManager::GetObjects()
{
	return m_baseObjects;
}

void GD_Tool::Mainframework::ProjectManager::AddObject(Object * obj)
{
	m_baseObjects.push_back(obj);
}
