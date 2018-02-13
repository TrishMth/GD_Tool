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
		class FloatAddFloatNode : public BaseNode
		{
		private:			
			float m_value;
		public:
			FloatAddFloatNode(const int32_t& value) :m_value(value), BaseNode(EVariableTypes::Float) {};
			void AddInt(const float& value) { m_value += value;}
			float GetValue() { return m_value; }
			~FloatAddFloatNode() {}
		};
	}
}