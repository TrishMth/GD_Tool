#pragma once
#pragma region Internal Includes
#include "imgui.h"
#include "AppManager.h"
#include "ProjectManager.h"
#include "BaseVariable.h"
#pragma endregion 
#pragma region External Includes
#include <map>
#include <list>
#include <unordered_map>
#pragma endregion 


namespace GD_Tool
{
	namespace Mainframework
	{
		class BaseGUI
		{
		public: 
			static void CreateInstance();
			static BaseGUI& GetInstance();
			static bool Release(const bool& showPopUp);

			void Init();
			bool Run();
			void AddLogToConsole(char* text, ImVec4 col);
			bool VSync();
			void UpdateAllWndSizes();
			~BaseGUI();
			bool IsInstantiated() const; 

		private: 
			static BaseGUI* s_pBaseGUI;


			BaseGUI();
			BaseGUI(const BaseGUI&) = delete; 


			void CreateMenuBar();
			void CreateNewWindow(const char* wndName);
			void CreateObjectMngWnd();
			void CreateObjectWnd();
			void CreateConsole();
			void CreateObjectTree(Object* obj,const int32_t& count, const int32_t& selectionMask, int32_t& nodeClicked);
			void CreateFormulaTree(Formula* formula, const int32_t& count, const int32_t& selectionMask, int32_t& nodeClicked);
			void CreateSubObject(Object* obj);
			void CreateFormulaWnd();
			void CreateGlobalVars();
			void CreateNewGlobalVar();
			void CreateFormulaNodeWnd(Formula* formula);
			void CreateGeneralSettings();
			void CreateStats();
			void CreateNode(Formula* formula);
			void CreateLevelEditor();
			void CreateProjectSettings();
			void CreateLevelDetailsPanel(bool* active, const ImVec2& pos, const float& width);
			void CreateReleasePopUp();

			bool m_bShowNewProjWnd; 
			bool m_bShowOpenProjWnd;
			bool m_bShowConsole; 
			bool m_bShowObjectManager;
			bool m_bShowCreateObject;
			bool m_bShowCreateSubObject;
			bool m_bShowCreateFormula;
			bool m_bShowGlobalVariables;
			bool m_bShowCreateVariables;
			bool m_bShowGeneralSettings; 
			bool m_bShowStats; 
			bool m_bShowLevelEditor;
			bool m_bShowProjectSettings;
			static bool m_bShowReleasePopup;

			bool m_bVSync; 
			bool m_bUpdateWndSize; 

			ImVector<char*> m_inputBuf;
			ImVector<ImVec4> m_inputCol;
			
			std::list<Formula*> m_showNodeWndContainer;
			std::list<std::string> m_recentOpenFiles; 
		};
	}
}