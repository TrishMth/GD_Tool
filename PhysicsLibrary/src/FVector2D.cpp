#include "include\FVector2D.h"


PhysicsLibrary::Basics::FVector2D::FVector2D()
	:m_XValue(0)
	, m_YValue(0)
{

}

PhysicsLibrary::Basics::FVector2D::FVector2D(const int64_t& X, const int64_t& Y)
	:m_XValue(X)
	, m_YValue(Y)
{

}

PhysicsLibrary::Basics::FVector2D::FVector2D(const int32_t& X, const int32_t&Y)
	:m_XValue(X)
	, m_YValue(Y)
{

}

PhysicsLibrary::Basics::FVector2D::FVector2D(const int16_t& X, const int16_t& Y)
	:m_XValue(X)
	, m_YValue(Y)
{

}

PhysicsLibrary::Basics::FVector2D::FVector2D(const float& X, const float& Y)
	:m_XValue(X)
	, m_YValue(Y)
{

}

PhysicsLibrary::Basics::FVector2D::FVector2D(const double& X, const double& Y)
	:m_XValue(X)
	, m_YValue(Y)
{

}

PhysicsLibrary::Basics::FVector2D::FVector2D(const FVector2D& vec)
	:m_XValue(vec.m_XValue)
	, m_YValue(vec.m_YValue)
{

}


inline PhysicsLibrary::Basics::FVector2D PhysicsLibrary::Basics::FVector2D::operator*(const FVector2D& vec) const
{
	PhysicsLibrary::Basics::FVector2D product(this->m_XValue*vec.m_XValue, this->m_YValue*vec.m_YValue);
	return product;
}

inline PhysicsLibrary::Basics::FVector2D PhysicsLibrary::Basics::FVector2D::operator+(const FVector2D& vec) const
{
	PhysicsLibrary::Basics::FVector2D sum(this->m_XValue + vec.m_XValue, this->m_YValue + vec.m_YValue);
	return sum;
}

inline PhysicsLibrary::Basics::FVector2D PhysicsLibrary::Basics::FVector2D::operator-(const FVector2D& vec) const
{
	PhysicsLibrary::Basics::FVector2D diff(this->m_XValue - vec.m_XValue, this->m_YValue - vec.m_YValue);
	return diff;
}

inline PhysicsLibrary::Basics::FVector2D PhysicsLibrary::Basics::FVector2D::operator/(const FVector2D& vec) const
{
	PhysicsLibrary::Basics::FVector2D quot(this->m_XValue / vec.m_XValue, this->m_YValue / vec.m_YValue); 
}

inline void PhysicsLibrary::Basics::FVector2D::operator*=(const FVector2D& vec)
{
	this->m_XValue *= vec.m_XValue; 
	this->m_YValue *= vec.m_YValue; 
}

inline void PhysicsLibrary::Basics::FVector2D::operator+=(const FVector2D& vec)
{
	this->m_XValue += vec.m_XValue; 
	this->m_YValue += vec.m_YValue; 
}

inline void PhysicsLibrary::Basics::FVector2D::operator-=(const FVector2D& vec)
{
	this->m_XValue -= vec.m_XValue; 
	this->m_YValue -= vec.m_YValue; 
}

inline void PhysicsLibrary::Basics::FVector2D::operator/=(const FVector2D& vec)
{
	this->m_XValue /= vec.m_XValue; 
	this->m_YValue /= vec.m_YValue; 
}

inline void PhysicsLibrary::Basics::FVector2D::operator=(const FVector2D& vec)
{
	this->m_XValue = vec.m_XValue; 
	this->m_YValue = vec.m_YValue;
}
inline bool PhysicsLibrary::Basics::FVector2D::operator==(const FVector2D& vec) const
{
	return std::abs(this->m_XValue - vec.m_XValue) <= EPSILON && std::abs(this->m_YValue - vec.m_YValue) <= EPSILON;
}

inline bool PhysicsLibrary::Basics::FVector2D::operator!=(const FVector2D& vec) const
{
	return std::abs(this->m_XValue - vec.m_XValue) <= EPSILON || std::abs(this->m_YValue - vec.m_YValue) <= EPSILON;
}

float PhysicsLibrary::Basics::FVector2D::Magnitude() const
{
	return std::sqrt(Basics::Square(m_XValue) + Basics::Square(m_YValue));
}

float PhysicsLibrary::Basics::FVector2D::SquaredMagnitude() const
{
	return Basics::Square(m_XValue) + Basics::Square(m_YValue);
}

void PhysicsLibrary::Basics::FVector2D::Normalize(float tolerance)
{
	const float sum = Magnitude();
	if (sum > tolerance)
	{
		const float scale = PhysicsLibrary::Basics::InvSqrt(sum); 
		m_XValue *= scale; 
		m_YValue *= scale; 
		return; 
	}
	else
	{
		m_XValue = 0.0f; 
		m_YValue = 0.0f; 
	}
}

float PhysicsLibrary::Basics::FVector2D::DotProduct(const FVector2D& vec1,const FVector2D& vec2)
{
	return vec1.m_XValue* vec2.m_XValue + vec1.m_YValue * vec2.m_YValue;
}

float PhysicsLibrary::Basics::FVector2D::Dist(const FVector2D& vec1, const FVector2D& vec2)
{
	return (vec2.m_XValue - vec1.m_XValue) + (vec2.m_YValue - vec1.m_YValue); 
}

float PhysicsLibrary::Basics::FVector2D::SquaredDist(const FVector2D& vec1, const FVector2D& vec2)
{
	return PhysicsLibrary::Basics::Square(vec2.m_XValue - vec1.m_XValue) + PhysicsLibrary::Basics::Square(vec2.m_YValue - vec1.m_YValue);
}

float PhysicsLibrary::Basics::FVector2D::CrossProduct(const FVector2D & vec1, const FVector2D & vec2)
{
	return 0.0f;
}
