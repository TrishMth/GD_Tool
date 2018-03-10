#include "include\ProjectManager.h"

GD_Tool::Mainframework::ProjectManager* GD_Tool::Mainframework::ProjectManager::s_pProManager = nullptr;


GD_Tool::Mainframework::ProjectManager::ProjectManager(const std::string name)
	:m_name(name)
	,m_objIndex(0)
	,m_formulaIndex(0)
	,m_isDirty(true)
{
	
	m_filePath = ".//" + m_name;
	s_pProManager = this;
	Save();
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
	Object* newObj = new Object(m_objIndex,name);
	m_objIndex++;
	AddObject(newObj);
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
		CreateDirectory(m_filePath.c_str(),NULL);
		std::fstream fileStream;
		m_fileName = m_filePath + "//project.txt";

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
	}
}

void GD_Tool::Mainframework::ProjectManager::Delete()
{

	if (remove(m_fileName.c_str()))
		printf("successfully deleted");
	else
		printf("error deleting the file");
	delete s_pProManager;
}

void GD_Tool::Mainframework::ProjectManager::Release()
{
	delete s_pProManager;
}

GD_Tool::Mainframework::ProjectManager::~ProjectManager()
{
	s_pProManager = nullptr; 
}



