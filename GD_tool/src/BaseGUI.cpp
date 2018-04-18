#include "include\BaseGUI.h"

GD_Tool::Mainframework::BaseGUI* GD_Tool::Mainframework::BaseGUI::s_pBaseGUI = nullptr;
bool GD_Tool::Mainframework::BaseGUI::m_bShowReleasePopup = false;

GD_Tool::Mainframework::BaseGUI::BaseGUI()
	:m_bShowNewProjWnd(false)
	, m_bShowOpenProjWnd(false)
	, m_bShowConsole(true)
	, m_bShowObjectManager(false)
	, m_bShowCreateSubObject(false)
	, m_bShowGlobalVariables(false)
	, m_bShowCreateVariables(false)
	, m_bShowGeneralSettings(false)
	, m_bVSync(true)
	, m_bShowStats(false)
	, m_bUpdateWndSize(false)
	
{
	s_pBaseGUI = this;
	ImGui::CreateContext();
}

void GD_Tool::Mainframework::BaseGUI::Init()
{
	switch (AppManager::GetInstance().GetCurrentConfig().Styles)
	{
	case 0:
		ImGui::StyleColorsDark();
		break;
	case 1:
		ImGui::StyleColorsLight();
		break;
	case 2:
		ImGui::StyleColorsClassic();
		break;
	}
	m_recentOpenFiles = AppManager::GetInstance().GetCurrentConfig().RecentlyOpenedPaths;

	
}

bool GD_Tool::Mainframework::BaseGUI::Run()
{

	// TODO: A lot of optimization 

	CreateMenuBar();
	if (m_bShowNewProjWnd)
		CreateNewWindow("New Project");
	else if (m_bShowOpenProjWnd)
		CreateNewWindow("Open Project");

	if (m_bShowObjectManager)
		CreateObjectMngWnd();

	if (m_bShowConsole)
		CreateConsole();

	if (m_bShowGlobalVariables && ProjectManager::GetInstance().IsInstantiated())
		CreateGlobalVars();


	if (m_bShowGeneralSettings)
		CreateGeneralSettings();

	if (m_bShowProjectSettings)
		CreateProjectSettings();

	if (m_bShowStats)
		CreateStats();

	if (m_bShowLevelEditor)
		CreateLevelEditor();

	for (std::list<Formula*>::iterator it = m_showNodeWndContainer.begin(); it != m_showNodeWndContainer.end(); ++it)
	{
		Formula* formula = *it;
		if (formula->GetShowNodeWindow())
			CreateFormulaNodeWnd(formula);
		else
			m_showNodeWndContainer.erase(it);
	}

	if (m_bShowReleasePopup)
		CreateReleasePopUp();
	if (!s_pBaseGUI)
		return false;
	return true;
}

void GD_Tool::Mainframework::BaseGUI::AddLogToConsole(char* text, ImVec4 col)
{
	m_inputBuf.push_back(text);
	m_inputCol.push_back(col);
}

bool GD_Tool::Mainframework::BaseGUI::VSync()
{
	return m_bVSync;
}

void GD_Tool::Mainframework::BaseGUI::UpdateAllWndSizes()
{
	//TODO: Code for updating the window size after resize the window.
}


GD_Tool::Mainframework::BaseGUI::~BaseGUI()
{
	s_pBaseGUI = nullptr;
}

bool GD_Tool::Mainframework::BaseGUI::IsInstantiated() const
{

	return s_pBaseGUI!= nullptr ? true : false;

}

void GD_Tool::Mainframework::BaseGUI::CreateInstance()
{
	if (s_pBaseGUI == nullptr)
	{
		s_pBaseGUI = new BaseGUI();
	}
}

GD_Tool::Mainframework::BaseGUI & GD_Tool::Mainframework::BaseGUI::GetInstance()
{
	return *s_pBaseGUI;
}

bool GD_Tool::Mainframework::BaseGUI::Release(const bool& showPopUp)
{
	if (showPopUp)
	{
		m_bShowReleasePopup = true;
		if (m_bShowReleasePopup)
			return false;
	}

	ImGui::DestroyContext();
	delete s_pBaseGUI;
	return true;
}

void GD_Tool::Mainframework::BaseGUI::CreateMenuBar()
{
	
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New")) 
				m_bShowNewProjWnd = true;

			if (ImGui::MenuItem("Save", "Ctrl+S"))
			{
				if (ProjectManager::GetInstance().IsInstantiated())
					ProjectManager::GetInstance().Save();
			}
			if (ImGui::MenuItem("Save all"))
			{
				if (ProjectManager::GetInstance().IsInstantiated())
				{
					std::map<uint32_t, Object*> objects = ProjectManager::GetInstance().GetObjects();
					std::map<uint32_t, Formula*>formulas = ProjectManager::GetInstance().GetFormulas();
					for(std::map<uint32_t, Object*>::iterator it = objects.begin(); it != objects.end(); ++it)
						it->second->Save();
					for (std::map<uint32_t, Formula*>::iterator it = formulas.begin(); it != formulas.end(); ++it)
						it->second->Save();
					ProjectManager::GetInstance().Save();
				}
			}
			if (ImGui::MenuItem("Open", "Ctrl+O"))
				m_bShowOpenProjWnd = true; 
			if (ImGui::BeginMenu("Open Recent"))
			{
				for (std::list<std::string>::iterator it = m_recentOpenFiles.begin(); it != m_recentOpenFiles.end(); ++it)
				{
					if (ImGui::MenuItem(it->c_str()))
						AppManager::GetInstance().LoadProject(it->c_str());
					
				}
				ImGui::EndMenu();
			}
			
		ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Options"))
		{
			if (ImGui::MenuItem("General settings", nullptr, &m_bShowGeneralSettings))
			{

			}
			if (ProjectManager::GetInstance().IsInstantiated())
			{
				if (ImGui::MenuItem("Project settings", nullptr, &m_bShowProjectSettings))
				{
				}
			}


		ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::MenuItem("Console", nullptr, &m_bShowConsole))
			{

			}

			if (ImGui::MenuItem("Stats", nullptr, &m_bShowStats))
			{

			}
	
			if (ProjectManager::GetInstance().IsInstantiated())
			{
				if (ImGui::MenuItem("Object Manager", nullptr, &m_bShowObjectManager))
				{
					MessageSystem::Log("GUI", "Open Object Manager Window", "Successfully opened the object creation manager window");
				}
				if (ImGui::MenuItem("Global Variables", nullptr, &m_bShowGlobalVariables))
				{
					MessageSystem::Log("GUI", "Open global variables window", "Successfully opened the global variables window");
				}		

				if (ImGui::MenuItem("Level Editor", nullptr, &m_bShowLevelEditor))
				{
					MessageSystem::Log("GUI", "Open level editor window", "Successfully opened the global variables window");
				}
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void GD_Tool::Mainframework::BaseGUI::CreateNewWindow(const char* wndName)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);
	
	ImGui::SetNextWindowPos(ImVec2((io.DisplaySize.x / 2 )-100, (io.DisplaySize.y / 2)- 100), ImGuiCond_FirstUseEver);
	static char str[128] = "Enter name here";
	if (m_bShowNewProjWnd || m_bShowOpenProjWnd)
	{
		if (ImGui::Begin(wndName))
		{
			if (m_bShowNewProjWnd)
			{
				m_bShowOpenProjWnd = false;
				ImGui::InputText("Project name", str, IM_ARRAYSIZE(str));
				if (ImGui::Button("Accept"))
				{
					AppManager::GetInstance().NewProject(str);
					m_bShowNewProjWnd = false;
				}
				if (ImGui::Button("Cancel"))
					m_bShowNewProjWnd = false;
			}
			else if (m_bShowOpenProjWnd)
			{
				m_bShowNewProjWnd = false; 
				ImGui::InputText("Project file path", str, IM_ARRAYSIZE(str));
				if (ImGui::Button("Accept"))
				{
					std::string filePath = ".\\"; 
					filePath.append(str);
					filePath.append("\\project.txt");
					AppManager::GetInstance().LoadProject(str);
					m_bShowOpenProjWnd = false;
				}
				if (ImGui::Button("Cancel"))
					m_bShowOpenProjWnd = false;
			}
		}
		ImGui::End();
	}
}

void GD_Tool::Mainframework::BaseGUI::CreateObjectMngWnd()
{
	ImGui::SetNextWindowSize(ImVec2(200, 700), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(800, 20), ImGuiCond_FirstUseEver);
	
	if (!ImGui::Begin("Object Manager", &m_bShowObjectManager))
	{
		ImGui::End();
		return;
	}
	int32_t selectionMask = (1 << 2);
	int32_t nodeClicked = -1;
	if (!ProjectManager::GetInstance().GetObjects().empty())
	{
		if (ImGui::TreeNode("Objects"))
		{
			uint32_t counter = 0;
			std::map<uint32_t, Object*> objects = ProjectManager::GetInstance().GetObjects();
			for (std::map<uint32_t, Object*>::iterator it = objects.begin(); it != objects.end(); ++it, counter++)
			{
				CreateObjectTree(it->second,counter, selectionMask, nodeClicked);
			}
			if (nodeClicked != -1)
			{
				if (ImGui::GetIO().KeyCtrl)
					selectionMask ^= (1 << nodeClicked);
				else
					selectionMask = (1 << nodeClicked);
			}
			ImGui::TreePop();
		}
	}
	if (ImGui::Button("Create Object"))
	{
		m_bShowCreateObject = true;
	}
	if (m_bShowCreateObject)
		CreateObjectWnd();
	if (!ProjectManager::GetInstance().GetFormulas().empty())
	{
		if (ImGui::TreeNode("Formulas"))
		{
			uint32_t counter = 0;
			std::map<uint32_t, Formula*> formulas = ProjectManager::GetInstance().GetFormulas();
			for (std::map<uint32_t, Formula*>::iterator it = formulas.begin(); it != formulas.end(); ++it, counter++)
			{
				CreateFormulaTree(it->second, counter, selectionMask, nodeClicked);
			}
			if (nodeClicked != -1)
			{
				if (ImGui::GetIO().KeyCtrl)
					selectionMask ^= (1 << nodeClicked);
				else
					selectionMask = (1 << nodeClicked);
			}
			ImGui::TreePop();
		}
	}
	if (ImGui::Button("Create Formula"))
		m_bShowCreateFormula = true;

	if (m_bShowCreateFormula)
		CreateFormulaWnd();
	
	ImGui::End();
}

void GD_Tool::Mainframework::BaseGUI::CreateObjectWnd()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowSize(ImVec2(450, 100), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x / 2 - 100, io.DisplaySize.y / 2 - 100), ImGuiCond_FirstUseEver);
	if(ImGui::Begin("Create new object"), &m_bShowCreateObject)
	{
		ImGui::PushItemWidth(150);
		static char str[128] = "Object name";
		ImGui::InputText("Please enter a name for the new object", str, IM_ARRAYSIZE(str));
		if (ImGui::Button("Create") && str != nullptr)
		{
			ProjectManager::GetInstance().CreateObject(str);
			m_bShowCreateObject = false;
		}
		if (ImGui::Button("Cancel"))
		{
			m_bShowCreateObject = false; 
			ImGui::End();
			return;
		}
	}
	ImGui::End();
}

void GD_Tool::Mainframework::BaseGUI::CreateConsole()
{
	ImGui::SetNextWindowSize(ImVec2(700, 120), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(200, 600), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Console", &m_bShowConsole))
	{
		ImGui::End();
		return;
	}
	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
	if (ImGui::BeginPopupContextWindow())
	{
		ImGui::EndPopup();
	}
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1));
	ImGui::LogToClipboard();

	ImVec4 col_default_text = ImGui::GetStyleColorVec4(ImGuiCol_Text);

	ImGuiListClipper clipper(m_inputBuf.Size);
	while (clipper.Step())
		for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
		{
			const char* input = m_inputBuf[i];
			ImGui::PushStyleColor(ImGuiCol_Text, m_inputCol[i]);
			ImGui::TextUnformatted(input);
			ImGui::PopStyleColor();
		}

	ImGui::LogFinish();
	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::End();
}

void GD_Tool::Mainframework::BaseGUI::CreateObjectTree(Object* obj, const int32_t& count, const int32_t& selectionMask, int32_t& nodeClicked)
{
	ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3);
	ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ((selectionMask & (1 << count)) ? ImGuiTreeNodeFlags_Selected : 0);
	bool nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)count, nodeFlags, obj->GetName().c_str(), count);
	if (ImGui::IsItemClicked())
		nodeClicked = count;
	if (nodeOpen)
	{

		if(ImGui::TreeNode("Attached Objects"))
		{
			uint32_t counter = 0;
			std::map<uint32_t, Object*> attachedObjs = obj->GetAttachedObjs();

			if (!obj->GetAttachedObjs().empty())
			{
				for (std::map<uint32_t, Object*>::iterator it = attachedObjs.begin(); it != attachedObjs.end(); ++it, counter++)
				{
					CreateObjectTree(it->second, counter, selectionMask, nodeClicked);
				}
			}
			if (ImGui::Button("Create sub-object"))
			{
				m_bShowCreateSubObject = true; 				
			}
			if (m_bShowCreateSubObject)
			{
				CreateSubObject(obj);
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::PopStyleVar();

}

void GD_Tool::Mainframework::BaseGUI::CreateFormulaTree(Formula * formula, const int32_t & count, const int32_t & selectionMask, int32_t & nodeClicked)
{
	ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3);
	ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
	ImGui::TreeNodeEx((void*)(intptr_t)count, nodeFlags, formula->GetName().c_str(), count); /*ImGui::SameLine(); ImGui::Button("Edit", ImVec2(50, 17));*/

	if (ImGui::IsItemClicked())
	{
		ImGuiIO io = ImGui::GetIO();
		for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++)
		{
			if (ImGui::IsMouseDoubleClicked(i))
			{
				formula->SetShowNodeWindow(true);
				m_showNodeWndContainer.push_back(formula);
			}
		}
		nodeClicked = count;
	}
	ImGui::PopStyleVar();
}

void GD_Tool::Mainframework::BaseGUI::CreateSubObject(Object* obj)
{
	if (ImGui::Begin("Create new sub-object"))
	{
		static char str[128] = "Sub-object name";
		{
			ImGui::InputText("Please enter a name for the new sub-object", str, IM_ARRAYSIZE(str));
			if (ImGui::Button("Create") && str != nullptr)
			{
				obj->CreateSubObject(str);
				m_bShowCreateSubObject = false;
			}
		}
		ImGui::End();
	}
}

void GD_Tool::Mainframework::BaseGUI::CreateFormulaWnd()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x / 2 - 100, io.DisplaySize.y / 2 - 50), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Create new formula"))
	{
		static char str[64] = "Formula name"; 
		ImGui::InputText("Name", str, IM_ARRAYSIZE(str));
		if (ImGui::Button("Create") && str != nullptr)
		{
			ProjectManager::GetInstance().CreateFormula(str);
			m_bShowCreateFormula = false; 
		}
		ImGui::End();
	}
}

void GD_Tool::Mainframework::BaseGUI::CreateGlobalVars()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowPos(ImVec2(1, 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(200, 150), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Global Variables", &m_bShowGlobalVariables))
	{
		ImGui::End();
	}

	uint32_t counter = 0;
	std::map<uint32_t, BaseVariable*> variables = ProjectManager::GetInstance().GetGlobalVars();
	int32_t selectionMask = (1 << 2);
	int32_t nodeClicked = -1;
	for (std::map<uint32_t, BaseVariable*>::iterator it = variables.begin(); it != variables.end(); it++, counter++)
	{
		ImGuiTreeNodeFlags node_flags =  ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ((selectionMask & (1 << counter)) ? ImGuiTreeNodeFlags_Selected : 0);
		bool nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)counter, node_flags, it->second->GetName().c_str(), counter);
			
		static char str[128] = "Enter new name here";
		static int inputInt = 0;
		if (ImGui::IsItemClicked())
			nodeClicked = counter;
		if (nodeOpen)
		{
			if (ImGui::InputText("New Name", str, IM_ARRAYSIZE(str)) && str != "Enter new name here" && str != it->second->GetName().c_str())
				it->second->ChangeName(str);

			switch (it->second->GetType())
			{
			case GlobalEnums::EVariableTypes::Integer:
			{
				IntegerVariable* intVar = (IntegerVariable*)it->second;
				if (intVar != nullptr)
				{
					inputInt = intVar->GetValue();
					if (ImGui::InputInt("Current Value", &inputInt) && inputInt != intVar->GetValue())
						it->second->Set(inputInt);
				}
			}
				break;
			}
			ImGui::TreePop();
		}
			
	}
	if (ImGui::Button("Create new variable"))
	{
		m_bShowCreateVariables = true; 
	}
	if (m_bShowCreateVariables)
	{
		CreateNewGlobalVar();
	}
	ImGui::End();
}

void GD_Tool::Mainframework::BaseGUI::CreateNewGlobalVar()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_FirstUseEver); 
	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x / 2 - 100, io.DisplaySize.y / 2 -50), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Create new variable"))
	{
		static ImGuiComboFlags flags = 0;
		GlobalEnums::EVariableTypes varType = GlobalEnums::EVariableTypes::Integer; 
		const char* typeName[] = { "Integer", "Boolean", "Float", "Double" };
		static const char* currentType = typeName[0];
		if(ImGui::BeginCombo("Variable Type", currentType, flags))
		{
			for (uint32_t i = 0; i < IM_ARRAYSIZE(typeName); i++)
			{
				bool isSelected = (currentType == typeName[i]);
				if (ImGui::Selectable(typeName[i], isSelected))
					currentType = typeName[i];
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		static char str[128] = "Variable name";
		ImGui::InputText("Please enter a name for the new variable", str, IM_ARRAYSIZE(str));

		if (currentType == typeName[0])
			varType = GlobalEnums::EVariableTypes::Integer;
		else if (currentType == typeName[1])
			varType = GlobalEnums::EVariableTypes::Boolean;
		else if (currentType == typeName[2])
			varType = GlobalEnums::EVariableTypes::Float;
		else if (currentType == typeName[3])
			varType = GlobalEnums::EVariableTypes::Double;

		static int inputInt = 0;
		static float inputFloat = 0.0f; 
		static double inputDouble = 0.0f;
		static bool inputBool = false; 
		switch (varType)
		{
		case GlobalEnums::EVariableTypes::Integer:
			ImGui::InputInt("Value", &inputInt);
			break;
		case GlobalEnums::EVariableTypes::Float: 
			ImGui::InputFloat("Value", &inputFloat, 0.01f, 1.0f); 
			break;
		case GlobalEnums::EVariableTypes::Double: 
			ImGui::InputDouble("Value", &inputDouble, 0.00000000001f, 1.0f, "%6f");
			break;
		case GlobalEnums::EVariableTypes::Boolean:
			ImGui::Checkbox("Value", &inputBool);
			break;
		}
		if (ImGui::Button("Create variable"))
		{
			BaseVariable* var = nullptr;
			switch (varType)
			{
			case GlobalEnums::EVariableTypes::Integer:
				var = new BaseVariable(varType, str, inputInt);
				break;
			case GlobalEnums::EVariableTypes::Float:
				var = new BaseVariable(varType, str, inputFloat);
				break;
			case GlobalEnums::EVariableTypes::Double:
				var = new BaseVariable(varType, str, inputDouble);
				break;
			case GlobalEnums::EVariableTypes::Boolean:
				var = new BaseVariable(varType, str, inputBool);
				break;
			}
			if (var != nullptr)
			{
				ProjectManager::GetInstance().AddVariable(var);
				m_bShowCreateVariables = false;
				ImGui::End(); 
				return;
			}
			else
				MessageSystem::Error("GUI", "Couldn't create the variable", "The variable couldn't get generated.");
		}

		ImGui::End();
	}
}

void GD_Tool::Mainframework::BaseGUI::CreateFormulaNodeWnd(Formula* formula)
{
	ImGuiIO& io = ImGui::GetIO();
	static bool showContextMenu; 
	if (!ImGui::Begin("Formula node window"))
	{
		ImGui::End();
		return;
	}
	if (ImGui::IsMouseClicked(1) && ImGui::IsMouseHoveringWindow())
		showContextMenu = true; 
	
	if (showContextMenu)
	{
		CreateNode(formula);
	}

	ImGui::End();
}

void GD_Tool::Mainframework::BaseGUI::CreateGeneralSettings()
{
	ImGui::SetNextWindowSize(ImVec2(400, 100), ImGuiCond_FirstUseEver);

	AppConfigDesc currentConfig = AppManager::GetInstance().GetCurrentConfig();
	if (!ImGui::Begin("General Settings", &m_bShowGeneralSettings))
	{
		ImGui::End();
		return;
	}
	ImGui::Checkbox("VSync", &currentConfig.VSync);
	static ImGuiComboFlags flags = 0;
	const char* typeName[] = { "Dark", "Light", "Classic"};
	static const char* currentType;
	switch (AppManager::GetInstance().GetCurrentConfig().Styles)
	{
	case 0:
		currentType = "Dark";
		break;
	case 1:
		currentType = "Light";
		break;
	case 2:
		currentType = "Classic";
		break;
	}
	if (ImGui::BeginCombo("Select window style", currentType, flags))
	{
		for (uint32_t i = 0; i < IM_ARRAYSIZE(typeName); i++)
		{
			bool isSelected = (currentType == typeName[i]);
			if (ImGui::Selectable(typeName[i], isSelected))
				currentType = typeName[i];
			if (isSelected)
				ImGui::SetItemDefaultFocus();
		}		
		ImGui::EndCombo();
	}
	if (currentType == typeName[0])
	{
		ImGui::StyleColorsDark();
		currentConfig.Styles = 0;
	}
	else if (currentType == typeName[1])
	{
		ImGui::StyleColorsLight();
		currentConfig.Styles = 1;
	}
	else
	{
		ImGui::StyleColorsClassic();
		currentConfig.Styles = 2;
	}
	AppManager::GetInstance().SetNewConfig(currentConfig);
	ImGui::End();
}

void GD_Tool::Mainframework::BaseGUI::CreateStats()
{
	if (!ImGui::Begin("Stats", &m_bShowStats))
	{
		ImGui::End(); 
		return; 
	}	
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

void GD_Tool::Mainframework::BaseGUI::CreateNode(Formula* formula)
{
	ImGui::SetNextWindowPos(ImGui::GetMousePos(), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(100, 50), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Context"))
	{
		static ImGuiComboFlags flags = 0;
		static GlobalEnums::EVariableTypes varType;
		const char* typeName[] = { "Operators", "Variables" };
		static const char* currentType = typeName[0];
		if (ImGui::BeginCombo("Node type", currentType))
		{
			for (uint32_t i = 0; i < IM_ARRAYSIZE(typeName); i++)
			{
				bool isSelected = (currentType == typeName[i]);
				if (ImGui::Selectable(typeName[i], isSelected))
					currentType = typeName[i];
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
			
		}

		if (currentType == typeName[1])
		{
				static char str[128] = "Variable name";
				ImGui::InputText("Please enter a name for the new variable", str, IM_ARRAYSIZE(str));

				static GlobalEnums::ENodeType nodeType;
				const char* variableTypeName[] = { "Integer variable", "Float variable" };
				static const char* currentVarType = variableTypeName[0];
				if (ImGui::BeginCombo("Node type", currentVarType))
				{
					static ImGuiComboFlags flags = 0;
					for (uint32_t i = 0; i < IM_ARRAYSIZE(variableTypeName); i++)
					{
						bool isSelected = (currentVarType == variableTypeName[i]);
						if (ImGui::Selectable(variableTypeName[i], isSelected))
							currentVarType = variableTypeName[i];
						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}
				if (currentVarType == variableTypeName[0])
					varType = GlobalEnums::EVariableTypes::Integer;

				if (ImGui::Button("Create node"))
					formula->CreateVariableNode(varType, str);

		}
		ImGui::End();
	}
}

void GD_Tool::Mainframework::BaseGUI::CreateLevelEditor()
{
	ImGui::SetNextWindowSize(ImVec2(900, 500), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Level Editor", &m_bShowLevelEditor, ImGuiWindowFlags_MenuBar))
	{
		
		static bool detailsPanel = false; 
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Window"))
			{
				if (ImGui::MenuItem("Details Panel", nullptr, &detailsPanel))
				{
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		float width = ImGui::GetWindowWidth();
		ImVec2 pos = ImGui::GetWindowPos();
		if(detailsPanel)
			CreateLevelDetailsPanel(&detailsPanel, pos, width);

		ImDrawList* drawList = ImGui::GetWindowDrawList();

		ImVec2 canvasPos = ImGui::GetCursorScreenPos(); 
		ImVec2 canvasSize = ImGui::GetContentRegionAvail();

		if (canvasSize.x < 50.0f) canvasSize.x = 50.0f; 
		if (canvasSize.y < 50.0f) canvasSize.y = 50.0f; 
	
		drawList->AddRect(canvasPos, ImVec2(canvasPos.x + canvasSize.x, canvasPos.y + canvasSize.y), IM_COL32(255, 255, 255, 255));
		ImGui::InvisibleButton("canvas", canvasSize);



		ImGui::End();
	}

}

void GD_Tool::Mainframework::BaseGUI::CreateProjectSettings()
{
	ImGui::SetNextWindowSize(ImVec2(1000, 700), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Project settings", &m_bShowProjectSettings))
	{
		ImGui::End();
	}
	static char str[64] = "New project name";
	ImGui::InputText("Enter new name", str, IM_ARRAYSIZE(str)); ImGui::SameLine(); if (ImGui::Button("Change name")) { ProjectManager::GetInstance().ChangeName(str); }
	if (ImGui::Button("Delete project")) 
	{ 
		if (m_bShowObjectManager)
			m_bShowObjectManager = false;
		int32_t IRC = ProjectManager::GetInstance().Delete(ProjectManager::GetInstance().GetFilePath(), true); 
		MessageSystem::Log("GUI", "Delete", std::to_string(IRC));
		m_bShowProjectSettings = false; 
	}

	ImGui::End();
}

void GD_Tool::Mainframework::BaseGUI::CreateLevelDetailsPanel(bool* active, const ImVec2& pos, const float& width)
{
	ImGui::SetNextWindowSize(ImVec2(200, 700), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowPos(ImVec2(pos.x + width, pos.y), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Details Panel", active))
		ImGui::End();

	std::map<uint32_t, Object*> objects = ProjectManager::GetInstance().GetObjects();
	static const char* currentPlayer = "No Object";
	if (ImGui::BeginCombo("Choose Player", currentPlayer))
	{
		for (std::map<uint32_t, Object*>::iterator it = objects.begin(); it != objects.end(); ++it)
		{

			bool isSelected = (currentPlayer == _strdup(it->second->GetName().c_str()));
			if (ImGui::Selectable(_strdup(it->second->GetName().c_str()), isSelected))
				currentPlayer = _strdup(it->second->GetName().c_str());
			if (isSelected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	ImGui::End();
}

void GD_Tool::Mainframework::BaseGUI::CreateReleasePopUp()
{
	ImGui::OpenPopup("Save before quit?");
	if (ImGui::BeginPopupModal("Save before quit?", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("All unsaved changes will get discarded, do you want to save them before quit?");
		if (ImGui::Button("Yes", ImVec2(120, 0)))
		{
			ProjectManager::GetInstance().Save();
			ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
			BaseGUI::GetInstance().Release(false);
			ProjectManager::GetInstance().Release();
			return;
		}
		ImGui::SameLine();
		if (ImGui::Button("No", ImVec2(120, 0))) 
		{
			ImGui::CloseCurrentPopup();
			ImGui::EndPopup();
			BaseGUI::GetInstance().Release(false); 
			ProjectManager::GetInstance().Release(false);	
			return;
		}
		ImGui::EndPopup();
	}

}

