#include "include\IntegerVariable.h"

GD_Tool::Mainframework::IntegerVariable::IntegerVariable(const int32_t& value, const std::string& name)
	:BaseVariable(EVariableTypes::Integer, name, value)
	,BaseNode(ENodeType::Variable)
{
}

int32_t GD_Tool::Mainframework::IntegerVariable::GetValue() const
{
	return m_iValue;
}

void GD_Tool::Mainframework::IntegerVariable::SetValue(const int32_t & value)
{
	m_iValue = value; 
}

void GD_Tool::Mainframework::IntegerVariable::SetValue(const float & value)
{
	m_iValue = value;
}

int32_t GD_Tool::Mainframework::IntegerVariable::operator+(const int32_t& value) const
{
	return m_iValue + value;
}


int32_t GD_Tool::Mainframework::IntegerVariable::operator+(const float& value) const
{
	return m_iValue + value;
}


int32_t GD_Tool::Mainframework::IntegerVariable::operator-(const int32_t& value) const
{
	return m_iValue - value;
}


int32_t GD_Tool::Mainframework::IntegerVariable::operator-(const float& value) const
{
	return m_iValue - value;
}


int32_t GD_Tool::Mainframework::IntegerVariable::operator*(const int32_t& value) const
{
	return m_iValue * value; ;
}


int32_t GD_Tool::Mainframework::IntegerVariable::operator*(const float& value) const
{
	return m_iValue * value;
}


int32_t GD_Tool::Mainframework::IntegerVariable::operator/(const int32_t& value) const
{
	return m_iValue / value;
}


int32_t GD_Tool::Mainframework::IntegerVariable::operator/(const float& value) const
{
	return m_iValue / value;
}

