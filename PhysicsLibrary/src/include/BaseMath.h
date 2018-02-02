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
		static float FVelocity(const float& s, const float& t) { return s / t; }
		static float DVelocity(const double& s, const float& t) { return s / t; }
		static FVector3D FVelocity(const FVector3D& s, const FVector3D& t) { return s / t; }

		static float FAcceleration(const float& v, const float& t) { return v / t; }
		static float DAcceleration(const double& v, const double& t) { return v / t; }
		static FVector3D FAcceleration(const FVector3D& v, const FVector3D& t) { return v / t; }


	}
}