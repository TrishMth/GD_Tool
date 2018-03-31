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

int32_t GD_Tool::Mainframework::AppManager::InitApp(HINSTANCE hInstance, int32_t nCmdShow)
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	m_configDesc = LoadSystem::LoadConfig();
	DX11BaseWindow dx11Base(hInstance); 
	if (!dx11Base.Init(m_configDesc.WindowWidth, m_configDesc.WindowHeight))
		return false; 
	dx11Base.Run();
	//DX11Graph dx11(hInstance);
	//if (!dx11.Init(m_configDesc.WindowWidth, m_configDesc.WindowHeight))
	//	return false; 
	//dx11m.Run();
	//return dx11.Run();
	return 0;
}

void GD_Tool::Mainframework::AppManager::NewProject(const std::string & ProjectName)
{
	ProjectManager::CreateInstance(ProjectName);
}

void GD_Tool::Mainframework::AppManager::LoadProject(const std::string & FilePath)
{
	if (ProjectManager::GetInstance().IsInstantiated())
	{
		ProjectManager::GetInstance().~ProjectManager(); 
	}
	LoadSystem::LoadProject(FilePath);
	if (!ProjectManager::GetInstance().IsInstantiated())
		MessageSystem::Error("AppManager", "Couldn't load the project", "The project data couldn't get load or the file isn't compatible.");	
}

GD_Tool::Mainframework::AppManager& GD_Tool::Mainframework::AppManager::GetInstance()
{
	return *s_pAppManager; 
}

void GD_Tool::Mainframework::AppManager::Release()
{
	ProjectManager::Release();
	delete s_pAppManager;
}
