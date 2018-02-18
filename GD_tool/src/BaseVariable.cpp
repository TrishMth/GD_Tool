#include "include\BaseVariable.h"

auto GD_Tool::Mainframework::BaseVariable::GetValue() const
{
	auto value = m_iValue; 
	switch (m_variableType)
	{
	case EVariableTypes::Integer:
		value = m_iValue;
		break; 
	case EVariableTypes::Float:
		value = m_fValue; 
		break; 
	case EVariableTypes::Boolean:
		value = m_bValue; 
		break;
	case EVariableTypes::Double:
		value = m_dValue; 
		break; 
	}
	return value; 
}