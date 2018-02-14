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
		class IntAddFloatNode : public BaseNode
		{
		private:
			int32_t m_iValue;
			float m_fValue;
		public:
			IntAddFloatNode(const int32_t& value) :m_iValue(value), m_fValue(value), BaseNode(ENodeType::Operator) {};
			void AddInt(const float& value) { m_iValue += value; m_fValue += value; }
			int32_t GetIValue() { return m_iValue; }
			float GetFValue() { return m_fValue; }
			~IntAddFloatNode() {}
		};
	}
}