#include "include\IntegerVariable.h"

GD_Tool::Mainframework::IntegerVariable::IntegerVariable(const int32_t& value, const std::string& name)
	:BaseVariable(EVariableTypes::Integer, name, value)
	,m_value(value)
	,BaseNode(ENodeType::Variable)
{
}

void GD_Tool::Mainframework::IntegerVariable::SetValue(const int32_t & value)
{
	m_value = value; 
}

void GD_Tool::Mainframework::IntegerVariable::SetValue(const float & value)
{
	m_value = value; 
}

int32_t GD_Tool::Mainframework::IntegerVariable::operator+(const int32_t& value) const
{
	return m_value + value;
}


int32_t GD_Tool::Mainframework::IntegerVariable::operator+(const float& value) const
{
	return m_value + value;
}


int32_t GD_Tool::Mainframework::IntegerVariable::operator-(const int32_t& value) const
{
	return m_value - value;
}


int32_t GD_Tool::Mainframework::IntegerVariable::operator-(const float& value) const
{
	return m_value - value;
}


int32_t GD_Tool::Mainframework::IntegerVariable::operator*(const int32_t& value) const
{
	return m_value * value; ;
}


int32_t GD_Tool::Mainframework::IntegerVariable::operator*(const float& value) const
{
	return m_value * value;
}


int32_t GD_Tool::Mainframework::IntegerVariable::operator/(const int32_t& value) const
{
	return m_value / value;
}


int32_t GD_Tool::Mainframework::IntegerVariable::operator/(const float& value) const
{
	return m_value / value;
}

