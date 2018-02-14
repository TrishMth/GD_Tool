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
		class IntAddIntNode : public BaseNode
		{
		private: 
			int32_t m_value; 
		public: 
			IntAddIntNode(const int32_t& value) :m_value(value), BaseNode(ENodeType::Operator) {};
			void AddInt(const int32_t& value) { m_value += value; }
			int32_t GetValue() { return m_value; }
			~IntAddIntNode() {}
		};
	}
}