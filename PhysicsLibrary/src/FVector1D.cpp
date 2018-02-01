#include "include/FVector1D.h"


PhysicsLibrary::Basics::FVector1D::FVector1D()
	:m_XValue(0)
{

}

PhysicsLibrary::Basics::FVector1D::FVector1D(int64_t& value)
	:m_XValue(value)
{

}

PhysicsLibrary::Basics::FVector1D::FVector1D(int32_t& value)
	:m_XValue(value)
{

}

PhysicsLibrary::Basics::FVector1D::FVector1D(int16_t& value)
	: m_XValue(value)
{

}

PhysicsLibrary::Basics::FVector1D::FVector1D(float& value)
	: m_XValue(value)
{

}

PhysicsLibrary::Basics::FVector1D::FVector1D(double& value)
	: m_XValue(value)
{

}
