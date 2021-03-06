#include "include/FVector1D.h"


GD_Tool::PhysicsLibrary::FVector1D::FVector1D()
	:m_XValue(0)
{

}

GD_Tool::PhysicsLibrary::FVector1D::FVector1D(int64_t& value)
	:m_XValue(value)
{

}

GD_Tool::PhysicsLibrary::FVector1D::FVector1D(int32_t& value)
	:m_XValue(value)
{

}

GD_Tool::PhysicsLibrary::FVector1D::FVector1D(int16_t& value)
	: m_XValue(value)
{

}

GD_Tool::PhysicsLibrary::FVector1D::FVector1D(float& value)
	: m_XValue(value)
{

}

GD_Tool::PhysicsLibrary::FVector1D::FVector1D(double& value)
	: m_XValue(value)
{

}
