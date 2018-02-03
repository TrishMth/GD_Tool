#pragma once
#pragma region Internal Includes
#include "BaseMath.h"
#include "FVector2D.h"
#pragma endregion 
#pragma region External Includes
#include <cstdint>
#include <cmath>
#pragma endregion 


namespace PhysicsLibrary
{
	namespace Basics
	{
		///\class FVector3D.h "src/include/FVector3D.h
		///\brief This is the Vector class in 3-dimension with automatically converts every input in float and calculate everything intern in the less 
		///accurate float. Use this class for every normal Vector. It will only works with the cstdint x_t integer types.

		class FVector3D
		{
		private: 
			float m_XValue; 
			float m_YValue; 
			float m_ZValue; 
		public: 
			/**
			* Default Constructor. Sets every variable to Zero
			*
			*/
			inline FVector3D(); 
			/**
			* Constructor for long 
			* 
			* @param X X-coordinate as long 
			* @param Y Y-coordinate as long 
			* @param Z Z-coordinate as long 
			*/
			inline FVector3D(const int64_t& X, const int64_t& Y, const int64_t& Z); 
			/**
			*Constructor for int 
			*
			* @param X X-coordinate as int 
			* @param Y Y-coordinate as int 
			* @param Z Z-coordinate as int 
			*/
			inline FVector3D(const int32_t& X, const int32_t& Y, const int32_t& Z); 
			/** 
			*Constructor for short 
			*
			* @param X X-coordinate as short 
			* @param Y Y-coordinate as short 
			* @param Z Z-coordinate as short 
			*/
			inline FVector3D(const int16_t& X, const int16_t& Y, const int16_t& Z); 
			/**
			*Constructor for floats
			* 
			* @param X X-coordinate as float 
			* @param Y Y-coordinate as float 
			* @param Z Z-coordinate as float 
			*/
			inline FVector3D(const float& X, const float& Y, const float& Z); 
			/**
			*Constructor for doubles
			* 
			* @param X X-coordinate as double (possible data loss)
			* @param Y Y-coordinate as double (possible data loss)
			* @param Z Z-coordinate as double (possible data loss)
			*/
			inline FVector3D(const double& X, const double& Y, const double& Z); 

			/**
			*Sets all values to 0. 
			*/
			inline void Zero() { m_XValue = 0; m_YValue = 0; m_ZValue = 0; }

			/**
			*Setter function for X 
			* 
			* @param X The X value you want to set as long
			*/
			inline void SetX(const int64_t& X) { m_XValue = X; }
			/**
			*Setter function for X 
			* 
			* @param X The X value you want to set as int 
			*/
			inline void SetX(const int32_t& X) { m_XValue = X; }
			/**
			*Setter function for X 
			* 
			* @param X The X value you want to set as short 
			*/
			inline void SetX(const int16_t& X) { m_XValue = X; }
			/**
			*Setter function for X
			*
			* @param X The X value you want to set as float 
			*/
			inline void SetX(const float& X) { m_XValue = X;  }
			/**
			*Setter function for X 
			*
			* @param X The X value you want to set as double (possible data loss)
			*/
			inline void SetX(const double& X) { m_XValue = X; }
			/**
			* Setter function for Y 
			*
			* @param Y The Y value you want to set as long 
			*/
			inline void SetY(const int64_t& Y) { m_YValue = Y; }
			/**
			* Setter function for Y
			*
			* @param Y The Y value you want to set as int 
			*/
			inline void SetY(const int32_t& Y) { m_YValue = Y; }
			/**
			* Setter function for Y 
			* 
			* @param Y The Y value you want to set as short 
			*/
			inline void SetY(const int16_t& Y) { m_YValue = Y; }
			/**
			* Setter function for Y 
			* 
			* @param Y The Y value you want to set as float
			*/
			inline void SetY(const float& Y) { m_YValue = Y; }
			/**
			* Setter function for Y 
			* 
			* @param Y The Y value you want to set as double (possible data loss)
			*/
			inline void SetY(const double& Y) { m_YValue = Y; }
			/**
			* Setter function for Z 
			* 
			* @param Z The Z value you want to set as long 
			*/
			inline void SetZ(const int64_t& Z) { m_ZValue = Z; }
			/**
			* Setter function for Z 
			* 
			* @param Z The Z value you want to set as int 
			*/
			inline void SetZ(const int32_t& Z) { m_ZValue = Z; }
			/**
			* Setter function for Z 
			* 
			* @param Z The Z value you want to set as short
			*/
			inline void SetZ(const int16_t& Z) { m_ZValue = Z; }
			/** 
			* Setter function for Z
			* 
			* @param Z The Z value you want to set as float 
			*/
			inline void SetZ(const float& Z) { m_ZValue = Z; }
			/**
			* Setter function for Z 
			* 
			* @param Z The Z value you want to set as double (possible data loss)
			*/
			inline void SetZ(const double& Z) { m_ZValue = Z; }
			/**
			* Setter function for Vector3D
			* 
			* @param vec The Vector3 you want to set as the current Vector 
			*/
			inline void SetVector3D(const FVector3D& vec) { m_XValue = vec.m_XValue; m_YValue = vec.m_YValue; m_ZValue = vec.m_ZValue; }
			/**
			* Setter function for Vector2D
			* 
			* @param vec The Vector2D yout want to set as part of the current Vector
			* @param float The variable you want to set as the Z variable of the Vector3D
			*/
			//inline void SetVector2D(const PhysicsLibrary::Basics::FVector2D& vec, const float& Z) { m_XValue = vec.GetX(); m_YValue = vec.GetY(); m_ZValue = Z; }
			/**
			* Getter function for Vector3D
			* 
			* @return The current Vector3D
			*/
			inline FVector3D GetVector3D() const { return *this; }
			/**
			* Getter function for X 
			* 
			* @return The current X-value
			*/
			inline float GetX() const { return m_XValue; }
			/**
			* Getter function for Y
			* 
			* @return The current Y-value
			*/
			inline float GetY() const { return m_YValue;  }
			/**
			* Getter function for Z
			* 
			* @return The current Z-value
			*/
			inline float GetZ() const { return m_ZValue; }
			/**
			* Operator overloading for multiplication 
			* 
			* @param vec The vector income to multiplicate with 
			* @return The multiplicated Vector3D
			*/
			inline FVector3D operator*(const FVector3D& vec) const; 
			/**
			* Operator overloading for adding 
			* 
			* @param vec The vector you want to add 
			* @return The sum of the calculation 
			*/
			inline FVector3D operator+(const FVector3D& vec) const; 
			/**
			* Operator overloading for substracting 
			* 
			* @param vec The vector you want to substract 
			* @return The difference of the calculation 
			*/
			inline FVector3D operator-(const FVector3D& vec) const; 
			/**
			* Operator overloading for dividing 
			* 
			* @param vec The vector you want to divide through 
			* @return The divided Vector from this calculation 
			*/
			inline FVector3D operator/(const FVector3D& vec) const; 
			/**
			* Operator overloading for the multiply-equals operator
			* 
			* @param vec The vector you want to multiplicate to the current vector 
			*/
			inline void operator*=(const FVector3D& vec); 
			/**
			* Operator overloading for the add-equals operator
			* 
			* @param vec The Vector you want to add to the current vector 
			*/
			inline void operator+=(const FVector3D& vec); 
			/**
			* Operator overloading for the minus-equals operator
			* 
			* @param vec The Vector you want to substract from the current vector
			*/
			inline void operator-=(const FVector3D& vec); 
			/**
			* Operator overloading for the divide-equals operator
			* 
			* @param vec The Vector you want to divide from the current Vector 
			*/
			inline void operator/=(const FVector3D& vec);
			/** 
			* Operator overloading for the equals operator
			* 
			* @param vec The vector you want to set as the current vector
			*/
			inline void operator=(const FVector3D& vec);
			/**
			* Operator overloading for the compare operator
			* 
			* @param vec The vector you want to compare with the current vector
			*/
			inline bool operator==(const FVector3D& vec); 
			/**
			* Operator overloading for the negate compare operator
			* 
			* @param vec The Vector you want to negate compare with the current vector
			*/
			inline bool operator!=(const FVector3D& vec); 
			/**
			* Get the magnitude(length) of this vector
			*
			* @return The magnitude(length) of this vector
			*/
			float Magnitude() const;

			/**
			* Get the squared magnitude(length) of this vector
			*
			* @return The squared magnitude(length) of this vector
			*/
			float SquaredMagnitude() const;

			/**
			* Normalize this vector in-place if it's large enough, set it to (0,0,0) otherwise.
			*
			* @param Tolerance min squared length of vector for normalization.
			*/
			void Normalize(float tolerance = EPSILON);
			/**
			* Get the dot product of two Vector3D 
			* 
			* @param vec1 The first vector of the dot product
			* @param vec2 The second vector of the dot product
			*/
			float DotProduct(const FVector3D& vec1, const FVector3D& vec2); 
			/**
			* Get the distance of two Vector3D
			* 
			* @param vec1 Where the distance calculation starts
			* @param vec2 Where the distance calculation ends
			*/
			float Dist(const FVector3D& vec1, const FVector3D& vec2); 
			/**
			* Get the squared distance of two Vector3D in euklidean space
			* 
			* @param vec1 Where the distance calculation starts
			* @param vec2 Where the distance calculation ends. 
			*/
			float SquaredDist(const FVector3D& vec1, const FVector3D& vec2);
			/**
			* Calculates the cross product between two Vector3D
			* 
			* @param vec1 First vector to calculate the cross product
			* @param vec2 Second vector to calculate the cross product
			*/
			FVector3D CrossProduct(const FVector3D& vec1, const FVector3D& vec2); 
		};
	}
}