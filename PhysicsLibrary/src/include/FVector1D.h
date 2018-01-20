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
		///\brief This is the Vector class in 1-dimension with automatically converts every input in float and calculate everything intern in the less 
		///accurate float. Use this class for every normal Vector. 

		class FVector1D
		{
		private: 
			float m_XValue; 
		public:
			///Constructor for integer types
			FVector1D(int64_t& value); 
			///Constructor for float types
			FVector1D(float& value);
			///Constructor for double types. Be aware using this convertion it will make the value less accurate.
			FVector1D(double& value); 
			///Calculates and returns the magnitude of the current Vector to another Vector
			float Magnitude(FVector1D& vec);
			///Calculates and returns the magnitude of two different Vectors.
			float static Magnitude(FVector1D& vec1, FVector1D& vec2);

			///Sets the value to 0.
			void Zero();

			///Setter functions for different input types
			inline void SetX(const int64_t& value) { m_XValue = value;  }
			inline void SetX(const float& value) { m_XValue = value;  }
			inline void SetX(const double& value) { m_XValue = value;  }
			///Getter function for the value
			inline float const GetX() { return m_XValue;  }
		};
	}
}