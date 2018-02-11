#include "include\Object.h"

GD_Tool::Mainframework::Object::Object(const uint32_t& objIndex, const std::string& name)
	:m_objIndex(objIndex)
	,m_name(name)
{

}

void GD_Tool::Mainframework::Object::AddObject(Object* obj)
{
	m_attachedObjs.push_back(obj); 
}

void GD_Tool::Mainframework::Object::RemoveObject(const uint32_t& index)
{
	m_attachedObjs.erase(m_attachedObjs.begin() + index); 
}

uint32_t GD_Tool::Mainframework::Object::GetIndex() const 
{
	return m_objIndex;
}
void GD_Tool::Mainframework::Object::SetIndex(const uint32_t& index)
{
	m_objIndex = index; 
}

void GD_Tool::Mainframework::Object::AddVariable(const IVariable& variable)
{
	m_variables.push_back(variable); 
}

GD_Tool::Mainframework::Object::~Object()
{

}
