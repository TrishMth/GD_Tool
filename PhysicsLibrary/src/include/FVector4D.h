#pragma once

#pragma region Internal Includes
#include "BaseMath.h"
#pragma endregion 
#pragma region External Includes
#include <cstdint>
#include <cmath>
#pragma endregion 

namespace PhysicsLibrary
{
	namespace Basics
	{
		class FVector4D
		{
		private: 
			float m_XValue; 
			float m_YValue; 
			float m_ZValue; 
			float m_WValue; 
		public: 
			inline float GetX() const; 
			inline float GetY() const; 
			inline float GetZ() const; 
			inline float GetW() const; 
		};
	}
}