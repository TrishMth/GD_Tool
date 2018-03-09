#include "include\Object.h"
#include "include\ProjectManager.h"

GD_Tool::Mainframework::Object::Object(const uint32_t& objIndex, const std::string& name, GD_Tool::Mainframework::ProjectManager* proMan)
	:m_objIndex(objIndex)
	, m_name(name)
	, m_variableIndex(0)
	, m_attachedIndex(0)
	, m_isDirty(true)
	,m_pProMan(proMan)
{
	Save();
}

void GD_Tool::Mainframework::Object::AddObject(Object* obj)
{
	if (obj->GetIndex() != m_objIndex)
	{
		m_attachedObjs.insert(std::pair<uint32_t, Object*>(m_attachedIndex, obj));
		m_attachedIndex++;
	}
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
void GD_Tool::Mainframework::Object::SetIndex(const uint32_t& index)
{
	m_objIndex = index; 
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
		std::string projectFilePath = m_pProMan->GetFilePath() + "//Objects";
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
