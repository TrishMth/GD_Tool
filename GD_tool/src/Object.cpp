#include "include\Object.h"
#include "include\ProjectManager.h"

GD_Tool::Mainframework::Object::Object(const uint32_t& objIndex, const std::string& name, const std::string& objDirPath)
	:m_objIndex(objIndex)
	, m_name(name)
	, m_variableIndex(0)
	, m_attachedIndex(0)
	, m_formulaIndex(0)
	, m_isDirty(true)
{
	m_dirName = objDirPath;
	Save();
}

void GD_Tool::Mainframework::Object::CreateSubObject(const std::string & name)
{
	for(std::map<uint32_t, Object*>::iterator it = m_attachedObjs.begin(); it != m_attachedObjs.end(); ++it)
		if (it->second->GetName() == name)
		{
			MessageSystem::Error(GetName(), "Failed to create new object", "A object with the name " + name + " already exists and can't created");
			return;
		}
	Object* obj = new Object(m_attachedIndex, name, m_dirName + "//" + name);
	AddObject(obj);
}

void GD_Tool::Mainframework::Object::AddObject(Object* obj)
{
	
	m_attachedObjs.insert(std::pair<uint32_t, Object*>(m_attachedIndex, obj));
	m_attachedIndex++;

	m_isDirty = true; 
}

void GD_Tool::Mainframework::Object::RemoveObject(const uint32_t& index)
{
	m_attachedObjs.erase(index); 
	m_isDirty = true; 
}

uint32_t GD_Tool::Mainframework::Object::GetIndex() const 
{
	return m_objIndex;
}

bool GD_Tool::Mainframework::Object::GetDirtyStatus()
{
	if (!m_isDirty)
	{
		for (std::map<uint32_t, Object*>::iterator it = m_attachedObjs.begin(); it != m_attachedObjs.end(); ++it)
			if (it->second->GetDirtyStatus())
				return true;

		return false; 
	}
	return true;
}

void GD_Tool::Mainframework::Object::CreateVariable(const GlobalEnums::EVariableTypes & type, const std::string & name, const int32_t & value)
{
	for(std::map<uint32_t, BaseVariable*>::iterator it = m_variables.begin(); it != m_variables.end(); ++it)
		if (name == it->second->GetName())
		{
			MessageSystem::Error(m_name, "Couldn't create variable" + name, "The variable name: " + name + " is already in use and can't get created");
			return;
		}
	BaseVariable* newVariable = new BaseVariable(type, name, value);
	AddVariable(newVariable);
}

void GD_Tool::Mainframework::Object::CreateVariable(const GlobalEnums::EVariableTypes & type, const std::string & name, const float & value)
{
	for (std::map<uint32_t, BaseVariable*>::iterator it = m_variables.begin(); it != m_variables.end(); ++it)
		if (name == it->second->GetName())
		{
			MessageSystem::Error(m_name, "Couldn't create variable" + name, "The variable name: " + name + " is already in use and can't get created");
			return;
		}
	BaseVariable* newVariable = new BaseVariable(type, name, value); 
	AddVariable(newVariable); 
}

void GD_Tool::Mainframework::Object::CreateVariable(const GlobalEnums::EVariableTypes & type, const std::string & name, const double & value)
{
	for (std::map<uint32_t, BaseVariable*>::iterator it = m_variables.begin(); it != m_variables.end(); ++it)
		if (name == it->second->GetName())
		{
			MessageSystem::Error(m_name, "Couldn't create variable" + name, "The variable name: " + name + " is already in use and can't get created");
			return;
		}
	BaseVariable* newVariable = new BaseVariable(type, name, value); 
	AddVariable(newVariable); 
}

void GD_Tool::Mainframework::Object::CreateVariable(const GlobalEnums::EVariableTypes & type, const std::string & name, const bool & value)
{
	for (std::map<uint32_t, BaseVariable*>::iterator it = m_variables.begin(); it != m_variables.end(); ++it)
		if (name == it->second->GetName())
		{
			MessageSystem::Error(m_name, "Couldn't create variable" + name, "The variable name: " + name + " is already in use and can't get created");
			return;
		}
	BaseVariable* newVariable = new BaseVariable(type, name, value); 
	AddVariable(newVariable); 
}

void GD_Tool::Mainframework::Object::AddVariable(BaseVariable* variable)
{
	if (variable)
	{
		m_variables.insert(std::pair<uint32_t, BaseVariable*>(m_variableIndex, variable));
		m_variableIndex++;
		m_isDirty = true;
	}
}

void GD_Tool::Mainframework::Object::RemoveVariable(const uint32_t & index)
{
	m_variables.erase(index);
	m_isDirty = true; 
}

void GD_Tool::Mainframework::Object::CreateFormula(const std::string & name)
{
	for(std::map<uint32_t, Formula*>::iterator it = m_localFormulas.begin(); it != m_localFormulas.end(); ++it)
		if (name == it->second->GetName())
		{
			MessageSystem::Error(m_name, "Couldn't create " + name, "A formula with the name " + name + " already exists and can't get created");
			return;
		}
	Formula* formula = new Formula(name);
	AddFormula(formula);
}


void GD_Tool::Mainframework::Object::AddFormula(Formula * formula)
{
	if (formula)
	{
		m_localFormulas.insert(std::pair<uint32_t, Formula*>(m_formulaIndex, formula)); 
		m_formulaIndex++;
		m_isDirty = true;
	}
}

void GD_Tool::Mainframework::Object::RemoveFormula(const uint32_t & index)
{
	m_localFormulas.erase(index);
	m_isDirty = true;
}

void GD_Tool::Mainframework::Object::Save()
{
	
	if (GetDirtyStatus())
	{
		for (std::map<uint32_t, Object*>::iterator it = m_attachedObjs.begin(); it != m_attachedObjs.end(); ++it)
			it->second->Save();

		CreateDirectory(m_dirName.c_str(),NULL);

		std::fstream fileStream; 
		m_fileName = m_dirName + "//" + m_name + "_Obj.txt";
		fileStream.open(m_fileName, std::fstream::out);
		if (fileStream.is_open())
		{
			m_isDirty = false; 
		}
		fileStream.close();
		
		MessageSystem::Log("Object" + m_name, "Object saved", "Successfully saved " + m_name);
	}
}

void GD_Tool::Mainframework::Object::Delete()
{
	remove(m_fileName.c_str());
}

GD_Tool::Mainframework::Object::~Object()
{

}
