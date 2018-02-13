#pragma once
#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
#include <string>
#include <cstdint>
#pragma endregion 

namespace GD_Tool
{
	namespace Mainframework
	{
		class BaseNode
		{
		private:
			const EVariableTypes m_varType;
		public:
			BaseNode(const EVariableTypes& type) : m_varType(type){};
			EVariableTypes GetVarType() const { return m_varType; };
			~BaseNode() {};
		};
	}
}