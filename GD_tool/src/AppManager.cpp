#include "include\AppManager.h"

GD_Tool::Mainframework::AppManager* GD_Tool::Mainframework::AppManager::s_pAppManager = nullptr;

GD_Tool::Mainframework::AppManager::AppManager()

{
	s_pAppManager = this; 
	BaseGUI::CreateInstance();
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

int32_t GD_Tool::Mainframework::AppManager::InitApp(HINSTANCE hInstance)
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	m_configDesc = LoadSystem::LoadConfig();
	DX11BaseWindow dx11Base(hInstance); 
	if (!dx11Base.Init(m_configDesc.WindowWidth, m_configDesc.WindowHeight))
		return false; 
	dx11Base.Run();
	return 0;
}

void GD_Tool::Mainframework::AppManager::NewProject(const std::string & ProjectName)
{

	if (CheckNewProjectFile(ProjectName))
	{
		MessageSystem::Log("AppManager", "Create new project", "A new project with the name: " + ProjectName + " is created");
		return;
	}
	ProjectManager::CreateInstance(ProjectName);
	
}

bool GD_Tool::Mainframework::AppManager::CheckNewProjectFile(const std::string & ProjectName)
{
	std::string str = ".//" + ProjectName;
	if (!CreateDirectory(str.c_str(), NULL))
	{
		MessageSystem::Error("AppManager", "Couldn't create new project.", "A project with this name already exists, please delete the directory before creating a new project with this name.");
		return false;
	}
	return true;
}

void GD_Tool::Mainframework::AppManager::LoadProject(const std::string & FilePath)
{
	if (ProjectManager::GetInstance().IsInstantiated())
	{
		ProjectManager::GetInstance().Release(); 
	}
	LoadSystem::LoadProject(FilePath);
	if (!ProjectManager::GetInstance().IsInstantiated())
		MessageSystem::Error("AppManager", "Couldn't load the project", "The project data couldn't get load or the file isn't compatible.");
	else
		MessageSystem::Log("LoadSystem", "Loading successful", "The data of: " + FilePath + "successfully loaded the project");

}

GD_Tool::Mainframework::AppManager& GD_Tool::Mainframework::AppManager::GetInstance()
{
	return *s_pAppManager; 
}

void GD_Tool::Mainframework::AppManager::Release()
{
	BaseGUI::Release();
	ProjectManager::Release();
	delete s_pAppManager;
}
