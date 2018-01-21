#pragma once
#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
#include <cstdint>
#pragma endregion 


namespace GD_Tool
{
	namespace PhysicsLibrary
	{
		///\class FVector1D.h "src/include/FVector1D.h
		///\brief This is the Vector class in 2-dimension with automatically converts every input in float and calculate everything intern in the less 
		///accurate float. Use this class for every normal Vector. It will only works with the cstdint x_t integer types.

		class FVector2D
		{
		private: 
			float m_XValue; 
			float m_YValue; 
		public:
			///Default Constructor sets the values of the Vector2D to 0.
			FVector2D(); 
			///Constructor for long
			FVector2D(const int64_t& X, const int64_t& Y); 
			///Constructor for int 
			FVector2D(const int32_t& X, const int32_t& Y); 
			///Constructor for short
			FVector2D(const int16_t& X, const int16_t& Y); 
			///Constructor for float 
			FVector2D(const float& X, const float& Y);
			///Constructor for double
			FVector2D(const double& X, const double& Y); 
			///Copy Constructor
			FVector2D(const FVector2D& vec); 

			///Sets all values to Zero
			inline void Zero() { m_XValue = 0; m_YValue = 0; }

			///Setter functions
			inline void SetX(const int64_t& X) { m_XValue = X; }
			inline void SetX(const int32_t& X) { m_XValue = X; }
			inline void SetX(const int16_t& X) { m_XValue = X; }
			inline void SetX(const float& X) { m_XValue = X; }
			inline void SetX(const double& X) { m_XValue = X; }

			inline void SetY(const int64_t& Y) { m_YValue = Y; }
			inline void SetY(const int32_t& Y) { m_YValue = Y; }
			inline void SetY(const int16_t& Y) { m_YValue = Y; }
			inline void SetY(const float& Y) { m_YValue = Y; }
			inline void SetY(const double& Y) { m_YValue = Y; }

			inline void SetVector2D(const FVector2D& vec) {	m_XValue = vec.m_XValue; m_YValue = vec.m_YValue;}

			///Getter function 
			inline FVector2D GetVector2D() const {return *this;}

			///overloading of the math operators
			inline FVector2D operator*(const FVector2D& vec) const; 
			inline FVector2D operator+(const FVector2D& vec) const; 
			inline FVector2D operator-(const FVector2D& vec) const; 
			inline FVector2D operator/(const FVector2D& vec) const; 
			inline void operator*= (const FVector2D& vec); 
			inline void operator+=(const FVector2D& vec);
			inline void operator-=(const FVector2D& vec); 
			inline void operator/=(const FVector2D& vec); 
			inline void operator= (const FVector2D& vec); 
			inline bool operator==(const FVector2D& vec) const; 
			inline bool operator!=(const FVector2D& vec) const; 


		};
	}
}