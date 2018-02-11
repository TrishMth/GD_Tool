#include "include\FloatVariable.h"

GD_Tool::Mainframework::FloatVariable::FloatVariable(const float& value, const std::string& name)
	:IVariable(EVariableTypes::Float, name)
	,m_value(value)
{
}

int32_t GD_Tool::Mainframework::FloatVariable::GetValue() const
{
	return m_value;
}

float GD_Tool::Mainframework::FloatVariable::operator+(const int32_t& value) const
{
	return m_value+value;
}

float GD_Tool::Mainframework::FloatVariable::operator+(const float& value) const
{
	return m_value + value;
}

float GD_Tool::Mainframework::FloatVariable::operator-(const int32_t& value) const
{
	return m_value -value;
}


float GD_Tool::Mainframework::FloatVariable::operator-(const float& value) const
{
	return m_value - value;
}


float GD_Tool::Mainframework::FloatVariable::operator*(const int32_t& value) const
{
	return m_value * value;
}


float GD_Tool::Mainframework::FloatVariable::operator*(const float& value) const
{
	return m_value * value;
}


float GD_Tool::Mainframework::FloatVariable::operator/(const int32_t& value) const
{
	return m_value / value;
}


float GD_Tool::Mainframework::FloatVariable::operator/(const float& value) const
{
	return m_value / value;
}

