#include "include\Object.h"
#include "include\ProjectManager.h"

GD_Tool::Mainframework::Object::Object(const uint32_t& objIndex, const std::string& name)
	:m_objIndex(objIndex)
	, m_name(name)
	, m_variableIndex(0)
	, m_attachedIndex(0)
	, m_isDirty(true)
{
	Save();
}

void GD_Tool::Mainframework::Object::CreateSubObject(const std::string & name)
{
	Object* obj = new Object(m_attachedIndex, name);
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

void GD_Tool::Mainframework::Object::CreateVariable(const GlobalEnums::EVariableTypes & type, const std::string & name, const int32_t & value)
{
	BaseVariable* newVariable = new BaseVariable(type, name, value);
	AddVariable(newVariable);
}

void GD_Tool::Mainframework::Object::CreateVariable(const GlobalEnums::EVariableTypes & type, const std::string & name, const float & value)
{
	BaseVariable* newVariable = new BaseVariable(type, name, value); 
	AddVariable(newVariable); 
}

void GD_Tool::Mainframework::Object::CreateVariable(const GlobalEnums::EVariableTypes & type, const std::string & name, const double & value)
{
	BaseVariable* newVariable = new BaseVariable(type, name, value); 
	AddVariable(newVariable); 
}

void GD_Tool::Mainframework::Object::CreateVariable(const GlobalEnums::EVariableTypes & type, const std::string & name, const bool & value)
{
	BaseVariable* newVariable = new BaseVariable(type, name, value); 
	AddVariable(newVariable); 
}

void GD_Tool::Mainframework::Object::AddVariable(BaseVariable* variable)
{
	m_variables.insert(std::pair<uint32_t, BaseVariable*>(m_variableIndex, variable)); 
	m_variableIndex++;
	m_isDirty = true; 
}

void GD_Tool::Mainframework::Object::RemoveVariable(const uint32_t & index)
{
	m_variables.erase(index);
	m_isDirty = true; 
}



void GD_Tool::Mainframework::Object::Save()
{
	
	if (m_isDirty)
	{
		std::string projectFilePath = ProjectManager::GetInstance().GetFilePath() + "//Objects";
		CreateDirectory(projectFilePath.c_str(),NULL);

		std::fstream fileStream; 
		m_fileName = projectFilePath + "//" + m_name + "_Obj.txt";
		fileStream.open(m_fileName, std::fstream::out);
		if (fileStream.is_open())
		{
			m_isDirty = false; 
		}
		fileStream.close();
		
	}
}

void GD_Tool::Mainframework::Object::Delete()
{
	remove(m_fileName.c_str());
}

GD_Tool::Mainframework::Object::~Object()
{

}
