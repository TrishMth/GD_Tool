#include "include\ProjectManager.h"

GD_Tool::Mainframework::ProjectManager* GD_Tool::Mainframework::ProjectManager::s_pProManager = nullptr;


GD_Tool::Mainframework::ProjectManager::ProjectManager(const std::string& name)
	:m_name(name)
	,m_objIndex(0)
	,m_formulaIndex(0)
	,m_isDirty(true)
	, m_globalVarIndex(0)
{
	m_filePath = ".//" + m_name;
	Save();
	s_pProManager = this;
}



void GD_Tool::Mainframework::ProjectManager::CreateInstance(const std::string & name)
{
	if(s_pProManager == nullptr)
		s_pProManager = new ProjectManager(name);
}

GD_Tool::Mainframework::ProjectManager& GD_Tool::Mainframework::ProjectManager::GetInstance()
{
	return *s_pProManager;
}

bool GD_Tool::Mainframework::ProjectManager::IsInstantiated() const
{
	return s_pProManager != nullptr ? true : false; 
}

void GD_Tool::Mainframework::ProjectManager::ChangeName(const std::string newName)
{
	m_name = newName; 
	m_isDirty = true;
}

void GD_Tool::Mainframework::ProjectManager::CreateObject(const std::string & name)
{
	for (std::map<uint32_t, Object*>::iterator it = m_baseObjects.begin(); it != m_baseObjects.end(); ++it)
		if (name == it->second->GetName())
		{
			MessageSystem::Error("Project Manager", "Failed to create new object", "A object with the name " + name + " already exists and can't created");
			return;
		}

	Object* newObj = new Object(m_objIndex,name);
	m_objIndex++;
	AddObject(newObj);
	m_isDirty = true; 
}

void GD_Tool::Mainframework::ProjectManager::CreateGlobalVariable(const GlobalEnums::EVariableTypes & type, const std::string & name, const int32_t & value)
{
	for (std::map<uint32_t, BaseVariable*>::iterator it = m_globalVariables.begin(); it != m_globalVariables.end(); ++it)
		if (name == it->second->GetName())
		{
			MessageSystem::Error("ProjectManager", "Failed to create the new Variable", "A variable with this name already exists");
			return;
		}
	BaseVariable* newVariable = new BaseVariable(type, name, value);
	AddVariable(newVariable);
}

void GD_Tool::Mainframework::ProjectManager::CreateGlobalVariable(const GlobalEnums::EVariableTypes & type, const std::string & name, const float & value)
{
	for (std::map<uint32_t, BaseVariable*>::iterator it = m_globalVariables.begin(); it != m_globalVariables.end(); ++it)
		if (name == it->second->GetName())
		{
			MessageSystem::Error("ProjectManager", "Failed to create the new Variable", "A variable with this name already exists");
			return;
		}
	BaseVariable* newVariable = new BaseVariable(type, name, value);
	AddVariable(newVariable);
}

void GD_Tool::Mainframework::ProjectManager::CreateGlobalVariable(const GlobalEnums::EVariableTypes & type, const std::string & name, const double & value)
{
	for (std::map<uint32_t, BaseVariable*>::iterator it = m_globalVariables.begin(); it != m_globalVariables.end(); ++it)
		if (name == it->second->GetName())
		{
			MessageSystem::Error("ProjectManager", "Failed to create the new Variable", "A variable with this name already exists");
			return;
		}
	BaseVariable* newVariable = new BaseVariable(type, name, value);
	AddVariable(newVariable);
}

void GD_Tool::Mainframework::ProjectManager::CreateGlobalVariable(const GlobalEnums::EVariableTypes & type, const std::string & name, const bool & value)
{
	for (std::map<uint32_t, BaseVariable*>::iterator it = m_globalVariables.begin(); it != m_globalVariables.end(); ++it)
		if (name == it->second->GetName())
		{
			MessageSystem::Error("ProjectManager", "Failed to create the new Variable", "A variable with this name already exists");
			return;
		}
	BaseVariable* newVariable = new BaseVariable(type, name, value);
	AddVariable(newVariable);
}

void GD_Tool::Mainframework::ProjectManager::AddVariable(BaseVariable * variable)
{
	m_globalVariables.insert(std::pair<uint32_t, BaseVariable*>(m_globalVarIndex, variable));
	m_globalVarIndex++;
	m_isDirty = true;
}

std::map<uint32_t, GD_Tool::Mainframework::BaseVariable*> GD_Tool::Mainframework::ProjectManager::GetGlobalVars() const
{
	return m_globalVariables;
}

void GD_Tool::Mainframework::ProjectManager::RemoveGlobalVar(const uint32_t & index)
{
	m_globalVariables.erase(index);
	m_isDirty = true;
}

void GD_Tool::Mainframework::ProjectManager::RemoveObject(const uint32_t & index)
{
	m_baseObjects.erase(index);
	m_isDirty = true; 
}

std::map<uint32_t, GD_Tool::Mainframework::Object*> GD_Tool::Mainframework::ProjectManager::GetObjects()
{
	return m_baseObjects;
}

std::map<uint32_t, GD_Tool::Mainframework::Formula*> GD_Tool::Mainframework::ProjectManager::GetFormulas()
{
	return m_formulas;
}

void GD_Tool::Mainframework::ProjectManager::AddObject(Object * obj)
{
	m_baseObjects.insert(std::pair<uint32_t, Object*>(m_objIndex, obj));
	m_isDirty = true;
}


void GD_Tool::Mainframework::ProjectManager::CreateFormula(const std::string& name)
{
	for (std::map<uint32_t, Formula*>::iterator it = m_formulas.begin(); it != m_formulas.end(); ++it)
		if (name == it->second->GetName())
		{
			MessageSystem::Error("ProjectManager", "Failed to create the new formula", "A formula with this name already exists");
			return;
		}

	Formula* newFormula = new Formula(name);
	m_formulas.insert(std::pair<uint32_t, Formula*>(m_formulaIndex, newFormula));
	m_formulaIndex++;
	m_isDirty = true;
}

void GD_Tool::Mainframework::ProjectManager::RemoveFormula(const uint32_t & index)
{
	m_formulas.at(index)->Delete();
	m_formulas.erase(index);
	m_isDirty = true;
}

void GD_Tool::Mainframework::ProjectManager::Save()
{
	if (m_isDirty)
	{
		std::fstream fileStream;
		m_fileName = m_filePath + "//project.txt";
		AppManager::GetInstance().GetCurrentConfig().CheckRecentlyOpenedFiles(m_fileName);
		AppManager::GetInstance().AddNewProjectFile(m_fileName);
		fileStream.open(m_fileName.c_str(),std::fstream::out);
		if (fileStream.is_open())
		{
			ProjectDesc package{};
			ObjectDesc objPackage{};
			FormulaDesc formDesc{};
			package.Name = m_name + "\n";
			std::string buffer = package.GetBuffer();
			buffer.append(objPackage.Begin);
			buffer.append(std::to_string(m_objIndex) + "\n");
			for (std::map<uint32_t, Object*>::iterator it = m_baseObjects.begin(); it != m_baseObjects.end(); ++it)
			{
				buffer.append(it->second->GetName() + "\n");

			}
			buffer.append(formDesc.Begin);
			buffer.append(std::to_string(m_formulaIndex) + "\n");
			for (std::map<uint32_t, Formula*>::iterator it = m_formulas.begin(); it != m_formulas.end(); ++it)
			{
				buffer.append(it->second->GetName() + "\n");
			}
			buffer.append(formDesc.End);
			fileStream.write(buffer.c_str(), buffer.size());
			m_isDirty = false;

		}
		fileStream.close();
		MessageSystem::Log("Project Manager", "Saved", "Successfully saved the current project");
	}
}

void GD_Tool::Mainframework::ProjectManager::Delete()
{
	if (remove(m_fileName.c_str()))
	{
		MessageSystem::Log("ProjectManager", "Project deleted", "The project is succesfully deleted");
	}
	else
	{
		MessageSystem::Error("ProjectManager", "Failed to delete", "The project couldn't get deleted");
		return;
	}
	Release();
}

void GD_Tool::Mainframework::ProjectManager::Release()
{
	delete s_pProManager;
}

GD_Tool::Mainframework::ProjectManager::~ProjectManager()
{
	s_pProManager = nullptr; 
}



