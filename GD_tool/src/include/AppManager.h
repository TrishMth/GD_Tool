#pragma once
#pragma region Internal Includes
#include "ProjectManager.h"
#include "LoadSystem.h"
#include "MessageSystem.h"
#include "GlobalStructs.h"
#include "DX11Graph.h"
#include "DX11Map.h"
#include "DX11BaseWindow.h"
#pragma endregion 
#pragma region External Includes
#include <cstring>
#include <fstream>
#pragma endregion 

namespace GD_Tool
{
	namespace Mainframework
	{
		class AppManager
		{
		private: 
			/**
			* Instance of the AppManager
			*/
			static AppManager* s_pAppManager; 
			AppConfigDesc m_configDesc{};
			/**
			* Default Constructor of the AppManager
			*
			*/
			AppManager();
			/**
			* Copy Constructor of the AppManager, it will denie that the AppManager can get copied
			*
			* @param The AppManager to copy
			*/
			AppManager(const AppManager&) = delete; 
			/**
			*/
			void Save();
		public: 
			/**
			* Default Destructor of the AppManager, will only set the s_pAppManager to nullptr
			*/
			~AppManager();
			/**
			* Creates the instance of the AppManager, will call the Constructor 
			*/
			static void CreateInstance();
			/**
			* Initializes the Application and creates the window 
			* 
			* @param hInstance The instance handler of the window 
			* @param nCmdShow The mode of the currentwindow
			*/
			int32_t InitApp(HINSTANCE hInstance);
			/**
			* Creates a new Project 
			* 
			* @param ProjectName The name of the new project
			*/
			void NewProject(const std::string& ProjectName);
			inline AppConfigDesc& GetCurrentConfig() { return m_configDesc;  }
			void AddNewProjectFile(const std::string& fileName) { m_configDesc.RecentlyOpenedPaths.push_back(fileName); if (m_configDesc.RecentlyOpenedPaths.size() > 3) m_configDesc.RecentlyOpenedPaths.pop_front(); }
			inline void SetNewConfig(const AppConfigDesc& configDesc) { m_configDesc = configDesc; }
			inline void SetNewWindowSize(const uint32_t& resolutionX, const uint32_t& resolutionY) { m_configDesc.WindowWidth = resolutionX; m_configDesc.WindowHeight = resolutionY; }
			inline void SetNewWndPos(const int32_t& posX, const int32_t& posY) { m_configDesc.WindowPosX = posX; m_configDesc.WindowPosY = posY; }
			bool CheckNewProjectFile(const std::string& ProjectName);
			/**
			* Loads a existing project by getting the filepath 
			*
			* @param FilePath The path of the file you want to load
			*/
			void LoadProject(const std::string& FilePath);
			/**
			* Static function to get the instance of the AppManager and to call functions of the AppManager
			* 
			* @return Returns the instance of the AppManager Singleton 
			*/
			static AppManager& GetInstance();
			/**
			* Safe Release the instance of the AppManager
			*/
			static bool Release();
		};
	}
}