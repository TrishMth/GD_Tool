#pragma once

#define VERYSMALL (1.0E-150)
#define EPSILON (1.0E-8)
#define GRAVITY (9.807)
#define PI (3.14159265359)

#pragma region Internal Includes
#include "FVector3D.h"
#pragma endregion 
#pragma region External Includes
#include <cstdint>
#include <cmath>
#pragma endregion 

namespace PhysicsLibrary
{
	namespace Basics
	{
		static float InvSqrt(const float& value) {return 1 / std::sqrt(value);}
		static float Square(const float& value) { return value*value; }

		//static float FProjectileTrajectory();
	}
}