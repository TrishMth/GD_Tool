#pragma once
#pragma region Internal Includes
#include "BaseNode.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#include <cstdint>
#pragma endregion 

namespace GD_Tool
{
	namespace Mainframework
	{
		class FloatAddIntNode : public BaseNode
		{
		private:
			float m_value;
		public:
			FloatAddIntNode(const float& value) :m_value(value), BaseNode(EVariableTypes::Float) {};
			void AddInt(const int32_t& value) { m_value += value; }
			float GetValue() { return m_value; }
			~FloatAddIntNode() {}
		};
	}
}