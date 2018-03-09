#include "include\AppManager.h"

GD_Tool::Mainframework::AppManager* GD_Tool::Mainframework::AppManager::s_pAppManager = nullptr;

GD_Tool::Mainframework::AppManager::AppManager()
{
	s_pAppManager = this; 
}

GD_Tool::Mainframework::AppManager::~AppManager()
{
	s_pAppManager = nullptr; 
}

void GD_Tool::Mainframework::AppManager::CreateInstance()
{
	if (s_pAppManager == nullptr)
		s_pAppManager = new AppManager();
}

void GD_Tool::Mainframework::AppManager::NewProject(const std::string & ProjectName)
{
	m_pProManager = new ProjectManager(ProjectName);
}

void GD_Tool::Mainframework::AppManager::LoadProject(const std::string & FilePath)
{
	m_pProManager = LoadSystem::LoadProject(FilePath);
	if (m_pProManager == nullptr)
		MessageSystem::Error("AppManager", "Couldn't load the project", "The project data couldn't get load or the file isn't compatible.");
}

GD_Tool::Mainframework::AppManager& GD_Tool::Mainframework::AppManager::GetInstance()
{
	return *s_pAppManager; 
}

void GD_Tool::Mainframework::AppManager::Release()
{
	delete s_pAppManager;
}
