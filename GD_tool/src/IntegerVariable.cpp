#include "include\IntegerVariable.h"

GD_Tool::Mainframework::IntegerVariable::IntegerVariable(const int32_t& value, const std::string& name)
	:IVariable(EVariableTypes::Integer, name)
	,m_value(value)
{
}

int32_t GD_Tool::Mainframework::IntegerVariable::GetValue() const
{
	return m_value;
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

