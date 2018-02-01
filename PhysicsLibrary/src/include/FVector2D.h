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
		///\class FVector2D.h "src/include/FVector2D.h
		///\brief This is the Vector class in 2-dimension with automatically converts every input in float and calculate everything intern in the less 
		///accurate float. Use this class for every normal Vector. It will only works with the cstdint x_t integer types.

		class FVector2D
		{
		private:
			float m_XValue;
			float m_YValue;
		public:
			/**
			Default Constructor sets the values of the Vector2D to 0.
			*/
			inline FVector2D();
			/**
			* Constructor for long
			* 
			* @param X X coordinate as long 
			* @param Y Y coordinate as long 
			*/

			inline FVector2D(const int64_t& X, const int64_t& Y);
			/**
			* Constructor for int 
			* 
			* @param X X coordinate as int 
			* @param Y Y coordinate as int 
			*/
			inline FVector2D(const int32_t& X, const int32_t& Y);
			/**
			* Constructor for short
			* 
			* @param X X coordinate as short 
			* @param Y Y coordinate as short 
			*/ 
			inline FVector2D(const int16_t& X, const int16_t& Y);
			/**
			* Constructor for float 
			* 
			* @param X X coordinate as float 
			* @param X X coordinate as float 
			*/
			inline FVector2D(const float& X, const float& Y);
			/** 
			* Constructor for double (possible data loss)
			* 
			* @param X X coordinate as double 
			* @param Y Y coordinate as double 
			*/
			inline FVector2D(const double& X, const double& Y);
			/**
			* Copy Constructor
			* 
			* @param vec The Vector you want to copy.
			*/
			inline FVector2D(const FVector2D& vec);

			/**
			* Sets all values to Zero
			* 
			*/
			inline void Zero() { m_XValue = 0; m_YValue = 0; }

			/**
			* Setter function for X 
			* 
			* @param X The X Value you want to set as long 
			*/
			inline void SetX(const int64_t& X) { m_XValue = X; }
			/**
			* Setter function for X 
			* 
			* @param X The X Value you want to set as int 
			*/
			inline void SetX(const int32_t& X) { m_XValue = X; }
			/**
			* Setter function for X 
			* 
			* @param X The X Value you want to set as short 
			*/
			inline void SetX(const int16_t& X) { m_XValue = X; }
			/**
			* Setter function for X 
			* 
			* @param X The X Value you want to set as float 
			*/
			inline void SetX(const float& X) { m_XValue = X; }
			/**
			* Setter function for X (possible data loss)
			* 
			* @param X The X Value you want to set as double 
			*/
			inline void SetX(const double& X) { m_XValue = X; }
			/**
			* Setter function for Y 
			* 
			* @param Y The Y Value you want to set as long 
			*/
			inline void SetY(const int64_t& Y) { m_YValue = Y; }
			/**
			* Setter function for Y 
			* 
			* @param Y The Y Value you want to set as int 
			*/
			inline void SetY(const int32_t& Y) { m_YValue = Y; }
			/** 
			* Setter function for Y 
			* 
			* @param Y The Y Value you want to set as short
			*/
			inline void SetY(const int16_t& Y) { m_YValue = Y; }
			/** 
			* Setter function for Y 
			* 
			* @param Y The Y Value you want to set as float 
			*/
			inline void SetY(const float& Y) { m_YValue = Y; }
			/** 
			* Setter function for Y (possible data loss)
			* 
			* @param Y The Y Value you want to set as double */
			inline void SetY(const double& Y) { m_YValue = Y; }
			/**
			* Setter function for FVector2D 
			* 
			* @param vec The Vector you want to set 
			*/
			inline void SetVector2D(const FVector2D& vec) { m_XValue = vec.m_XValue; m_YValue = vec.m_YValue; }

			/**
			* Getter Function 
			*
			* @return The current Vector2D
			*/
			inline FVector2D GetVector2D() const { return *this; }
			/** 
			* Getter function for the X value 
			*
			* @return The current X-value 
			*/
			inline float GetX() const { return m_XValue; }
			/** 
			* Getter function for the Y value
			*
			* @return The current Y-value
			*/
			inline float GetY() const { return m_YValue; }
			/**
			* Operator overloading for multiplication 
			*
			* @param vec The Vector income to multiplicate with 
			* @return The multiplicated Vector2D
			*/
			inline FVector2D operator*(const FVector2D& vec) const;
			/**
			* Operator overloading for adding another Vector2D 
			* 
			* @param vec The Vector you want to add with 
			* @return the sum of the calculation
			*/
			inline FVector2D operator+(const FVector2D& vec) const;
			/** 
			* Operator overloading for substract another Vector2D
			* 
			* @param vec The vector you want to substract from the current vector
			* @return The result of this calculation 
			*/
			inline FVector2D operator-(const FVector2D& vec) const;
			/** 
			* Operator overloading for device another Vector2D 
			* 
			* @param vec The vector you want to divide through the current vector 
			* @return The result of this calculation 
			*/
			inline FVector2D operator/(const FVector2D& vec) const;

			/**
			* Operator overloading for the multiply-equals operation 
			* 
			* @param vec The Vector you want to multiplicate to the current vector 
			*/
			inline void operator*= (const FVector2D& vec);
			/**
			* Operator overloading for the add-equals operation 
			* 
			* @param vec The vector you want to add to the current vector
			*/
			inline void operator+=(const FVector2D& vec);
			/** 
			* Operator overloading for the minus-equals operation 
			* 
			* @param vec The Vector you want to substract from the current vector
			*/
			inline void operator-=(const FVector2D& vec);
			/**
			* Operator overloading for the divide-equals operation 
			* 
			* @param vec The Vector you want to divide through the current vector 
			*/
			inline void operator/=(const FVector2D& vec);
			/**
			* Operator overloading for the equals operation 
			* 
			* @param vec The Vector you want to make equal with this 
			*/
			inline void operator= (const FVector2D& vec);
			/**
			* Operator overloading for the compare operation 
			* 
			* @param vec The Vector you want to compare with the current vector 
			*/
			inline bool operator==(const FVector2D& vec) const;
			/**
			* Operator overloading for the negate compare operator
			*
			* @param vec The Vector you want to negate compare with the current vector 
			*/
			inline bool operator!=(const FVector2D& vec) const;


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
			* Normalize this vector in-place if it's large enough, set it to (0,0) otherwise. 
			* 
			* @param Tolerance min squared length of vector for normalization. 
			*/
			void Normalize(float tolerance = EPSILON);

			/**
			* Get the dot Product of the two Vector2D
			* 
			*@param vec1 The first Vector of the dot product
			*@param vec2 The second Vector of the dot product
			*/
			float DotProduct(const FVector2D& vec1, const FVector2D& vec2); 

			/**
			Get the distance of two Vector2D
			*
			*@param vec1 From where the distance starts
			*@param vec2 Where the distance ends
			*/
			float Dist(const FVector2D& vec1, const FVector2D& vec2);

			/**
			Get the distance of two Vector2D in euklidian space
			* 
			*@param vec1 Where the distance calculating starts
			*@param vec2 Where the distance calculating ends
			*/
			float SquaredDist(const FVector2D& vec1, const FVector2D& vec2); 
			/**
			* Calculates the cross product between two vectors
			* 
			* @param vec1 First vector to calculate the cross product
			* @param vec2 Second vector to calculate the cross product
			*/
			float CrossProduct(const FVector2D& vec1, const FVector2D& vec2); 
		};
	}
}