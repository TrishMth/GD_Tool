#pragma region Internal Includes
#include "ProjectManager.h"
#include "LoadSystem.h"
#include "MessageSystem.h"
#pragma endregion 
#pragma region External Includes
#include <cstring>
#pragma endregion 

namespace GD_Tool
{
	namespace Mainframework
	{
		class AppManager
		{
		private: 
			static AppManager* s_pAppManager; 
			ProjectManager* m_pProManager;
			AppManager();

			AppManager(const AppManager&) = delete; 
		public: 
			~AppManager();

			static void CreateInstance();

			void NewProject(const std::string& ProjectName);

			void LoadProject(const std::string& FilePath);
			
			static AppManager& GetInstance();

			static void Release();
		};
	}
}