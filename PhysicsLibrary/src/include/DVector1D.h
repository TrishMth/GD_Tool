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
		///\class DVector1D.h "src/include/DVector1D.h
		///\brief This is the Vector class in 1-dimension with automatically converts every input in double and calculate everything intern in the more 
		///accurate double. Only use this if you need the more accuracy because double is more expensive. 
		class DVector1D
		{
		public:
			DVector1D(int64_t value);
			DVector1D(float value);
			DVector1D(double value);
			

		private:

		};
	}
}