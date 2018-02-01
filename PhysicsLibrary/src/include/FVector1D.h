#pragma once
#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
#include <cstdint>
#pragma endregion 


namespace PhysicsLibrary
{
	namespace Basics
	{
		///\class FVector1D.h "src/include/FVector1D.h
		///\brief This is the Vector class in 1-dimension with automatically converts every input in float and calculate everything intern in the less 
		///accurate float. Use this class for every normal Vector. It will only works with the cstdint x_t integer types.

		class FVector1D
		{
		private: 
			float m_XValue; 
		public:
			///Default Constructor initializes the value with 0
			FVector1D(); 
			///Constructor for long 
			FVector1D(int64_t& value); 
			///Constructor for int
			FVector1D(int32_t& value);
			///Constructor for short
			FVector1D(int16_t& value);
			///Constructor for float types
			FVector1D(float& value);
			///Constructor for double types. Be aware using this convertion it will make the value less accurate.
			FVector1D(double& value); 
			///Copy Constructor
			FVector1D(FVector1D& vec);

			///Sets the value to 0.
			inline void Zero() {m_XValue = 0;}

			///Setter functions for different input types
			inline void SetX(const int64_t& value) { m_XValue = value;  }
			inline void SetX(const int32_t& value) { m_XValue = value; }
			inline void SetX(const int16_t& value) { m_XValue = value; }
			inline void SetX(const float& value) { m_XValue = value;  }
			inline void SetX(const double& value) { m_XValue = value;  }
			///Getter function for the value
			inline float const GetX() { return m_XValue;  }
		};
	}
}