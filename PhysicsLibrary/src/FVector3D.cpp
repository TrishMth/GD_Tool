#include "include\FVector3D.h"

inline PhysicsLibrary::Basics::FVector3D::FVector3D()
	:m_XValue(0)
	,m_YValue(0)
	,m_ZValue(0)
{
}

inline PhysicsLibrary::Basics::FVector3D::FVector3D(const int64_t & X, const int64_t & Y, const int64_t & Z)
	:m_XValue(X)
	,m_YValue(Y)
	,m_ZValue(Z)
{
}

inline PhysicsLibrary::Basics::FVector3D::FVector3D(const int32_t & X, const int32_t & Y, const int32_t & Z)
	:m_XValue(X)
	,m_YValue(Y)
	,m_ZValue(Z)
{
}

inline PhysicsLibrary::Basics::FVector3D::FVector3D(const int16_t & X, const int16_t & Y, const int16_t & Z)
	:m_XValue(X)
	,m_YValue(Y)
	,m_ZValue(Z)
{
}

inline PhysicsLibrary::Basics::FVector3D::FVector3D(const float & X, const float & Y, const float & Z)
	:m_XValue(X)
	,m_YValue(Y)
	,m_ZValue(Z)
{
}

inline PhysicsLibrary::Basics::FVector3D::FVector3D(const double & X, const double & Y, const double & Z)
	:m_XValue(X)
	,m_YValue(Y)
	,m_ZValue(Z)
{
}

inline PhysicsLibrary::Basics::FVector3D PhysicsLibrary::Basics::FVector3D::operator*(const FVector3D & vec) const
{
	return FVector3D(m_XValue* vec.m_XValue, m_YValue * vec.m_YValue, m_ZValue * vec.m_ZValue);
}

inline PhysicsLibrary::Basics::FVector3D PhysicsLibrary::Basics::FVector3D::operator+(const FVector3D & vec) const
{
	return FVector3D(m_XValue + vec.m_XValue, m_YValue + vec.m_YValue, m_ZValue + vec.m_ZValue);
}

inline PhysicsLibrary::Basics::FVector3D PhysicsLibrary::Basics::FVector3D::operator-(const FVector3D & vec) const
{
	return FVector3D(m_XValue - vec.m_XValue, m_YValue -vec.m_YValue, m_ZValue - vec.m_ZValue);
}

inline PhysicsLibrary::Basics::FVector3D PhysicsLibrary::Basics::FVector3D::operator/(const FVector3D & vec) const
{
	return FVector3D(m_XValue / vec.m_XValue, m_YValue / vec.m_YValue, m_ZValue / vec.m_ZValue);
}

inline void PhysicsLibrary::Basics::FVector3D::operator*=(const FVector3D & vec) 
{
	m_XValue *= vec.m_XValue; 
	m_YValue *= vec.m_YValue;
	m_ZValue *= vec.m_ZValue; 
}

inline void PhysicsLibrary::Basics::FVector3D::operator+=(const FVector3D & vec) 
{
	m_XValue += vec.m_XValue;
	m_YValue += vec.m_YValue;
	m_ZValue += vec.m_ZValue; 
}

inline void PhysicsLibrary::Basics::FVector3D::operator-=(const FVector3D & vec) 
{
	m_XValue -= vec.m_XValue; 
	m_YValue -= vec.m_YValue; 
	m_ZValue -= vec.m_ZValue;
}

inline void PhysicsLibrary::Basics::FVector3D::operator/=(const FVector3D & vec) 
{
	m_XValue /= vec.m_XValue; 
	m_YValue /= vec.m_YValue; 
	m_ZValue /= vec.m_ZValue;
}

inline void PhysicsLibrary::Basics::FVector3D::operator=(const FVector3D & vec)
{
	m_XValue = vec.m_XValue;
	m_YValue = vec.m_YValue; 
	m_ZValue = vec.m_ZValue;
}

inline bool PhysicsLibrary::Basics::FVector3D::operator==(const FVector3D & vec)
{
	return std::fabs(this->m_XValue - vec.m_XValue) <= EPSILON && std::fabs(this->m_YValue - vec.m_YValue) <= EPSILON && std::fabs(this->m_ZValue -vec.m_ZValue) <= EPSILON; 
}

inline bool PhysicsLibrary::Basics::FVector3D::operator!=(const FVector3D & vec)
{
	return std::fabs(this->m_XValue - vec.m_XValue) <= EPSILON || std::fabs(this->m_YValue - vec.m_YValue) <= EPSILON || std::fabs(this->m_ZValue - vec.m_ZValue) <= EPSILON;
}

float PhysicsLibrary::Basics::FVector3D::Magnitude() const
{
	return std::sqrt(Basics::Square(m_XValue) + Basics::Square(m_YValue) + Basics::Square(m_ZValue));
}

float PhysicsLibrary::Basics::FVector3D::SquaredMagnitude() const
{
	return Basics::Square(m_XValue) + Basics::Square(m_YValue) + Basics::Square(m_ZValue);
}

void PhysicsLibrary::Basics::FVector3D::Normalize(float tolerance)
{
	const float sum = Basics::Square(m_XValue) + Basics::Square(m_YValue) + Basics::Square(m_ZValue);
	if (sum > tolerance)
	{
		const float scale = Basics::InvSqrt(sum);
		m_XValue *= scale;
		m_YValue *= scale;
		m_ZValue *= scale;
		return;
	}
	else
	{
		m_XValue = 0; 
		m_YValue = 0; 
		m_ZValue = 0; 
	}
}

float PhysicsLibrary::Basics::FVector3D::DotProduct(const FVector3D & vec1, const FVector3D & vec2)
{
	return vec1.m_XValue * vec2.m_XValue + vec1.m_YValue * vec2.m_YValue + vec1.m_ZValue * vec2.m_ZValue;
}

float PhysicsLibrary::Basics::FVector3D::SquaredDist(const FVector3D & vec1, const FVector3D & vec2)
{
	return Basics::Square(vec2.m_XValue-vec1.m_XValue) + Basics::Square(vec2.m_YValue - vec1.m_YValue) + Basics::Square(vec2.m_ZValue - vec1.m_ZValue);
}
float PhysicsLibrary::Basics::FVector3D::Dist(const FVector3D & vec1, const FVector3D & vec2)
{
	return std::sqrt(SquaredDist(vec1, vec2));
}
PhysicsLibrary::Basics::FVector3D PhysicsLibrary::Basics::FVector3D::CrossProduct(const FVector3D & vec1, const FVector3D & vec2)
{
	return FVector3D(vec1.m_YValue * vec2.m_ZValue - vec1.m_ZValue * vec2.m_YValue, vec1.m_ZValue * vec2.m_XValue - vec1.m_XValue * vec2.m_ZValue, vec1.m_XValue * vec2.m_XValue - vec1.m_YValue * m_XValue);
}
