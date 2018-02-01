#include "include\FMatrix3x3.h"


inline PhysicsLibrary::Basics::FMatrix3x3::FMatrix3x3(bool identity)
{
	if (!identity)
		m_ppMatrix[3][3] = { 0 };
	else
	{
		m_ppMatrix[0][0] = 1; m_ppMatrix[0][1] = 0; m_ppMatrix[0][2] = 0;
		m_ppMatrix[1][0] = 0; m_ppMatrix[1][1] = 1; m_ppMatrix[1][2] = 0;
		m_ppMatrix[2][0] = 0; m_ppMatrix[2][1] = 0; m_ppMatrix[2][2] = 1;
	}
}

inline PhysicsLibrary::Basics::FMatrix3x3::FMatrix3x3(const FMatrix3x3& mat)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_ppMatrix[i][j] = mat.m_ppMatrix[i][j];
		}
	}
}

inline PhysicsLibrary::Basics::FMatrix3x3::FMatrix3x3(const FVector3D& vec1, const FVector3D& vec2, const FVector3D& vec3)
{
	m_ppMatrix[0][0] = vec1.GetX(); m_ppMatrix[0][1] = vec1.GetY(); m_ppMatrix[0][2] = vec1.GetZ();
	m_ppMatrix[1][0] = vec2.GetX(); m_ppMatrix[1][1] = vec2.GetY(); m_ppMatrix[1][2] = vec2.GetZ();
	m_ppMatrix[2][0] = vec3.GetX(); m_ppMatrix[2][1] = vec3.GetY(); m_ppMatrix[2][2] = vec3.GetZ();
}

inline PhysicsLibrary::Basics::FMatrix3x3::FMatrix3x3(const float& value1, const float& value2, const float& value3, const float& value4,
	const float& value5, const float& value6, const float& value7, const float& value8,
	const float& value9)
{
	m_ppMatrix[0][0] = value1; m_ppMatrix[0][1] = value2; m_ppMatrix[0][2] = value3;
	m_ppMatrix[0][3] = value4; m_ppMatrix[1][0] = value5; m_ppMatrix[1][1] = value6; 
	m_ppMatrix[1][2] = value7; m_ppMatrix[1][3] = value8; m_ppMatrix[2][0] = value9; 
}

inline float** PhysicsLibrary::Basics::FMatrix3x3::GetMatrix() const
{
	return m_ppMatrix;
}

inline float PhysicsLibrary::Basics::FMatrix3x3::GetValue(const uint8_t& row, const uint8_t& column)
{
	return m_ppMatrix[row][column];
}

inline void PhysicsLibrary::Basics::FMatrix3x3::SetValue(const uint8_t& row, const uint8_t& column, const float& value)
{
	m_ppMatrix[row][column] = value;
}

inline float PhysicsLibrary::Basics::FMatrix3x3::Determinante() const
{
	return
		(m_ppMatrix[0][0] * m_ppMatrix[1][1] * m_ppMatrix[2][2]) +
		(m_ppMatrix[0][1] * m_ppMatrix[1][2] * m_ppMatrix[2][0]) +
		(m_ppMatrix[0][2] * m_ppMatrix[1][0] * m_ppMatrix[2][1]) -
		(m_ppMatrix[2][0] * m_ppMatrix[1][1] * m_ppMatrix[0][2]) -
		(m_ppMatrix[2][1] * m_ppMatrix[1][2] * m_ppMatrix[0][0]) -
		(m_ppMatrix[2][2] * m_ppMatrix[1][0] * m_ppMatrix[0][1]);
}

inline PhysicsLibrary::Basics::FMatrix3x3 PhysicsLibrary::Basics::FMatrix3x3::Transpose() const
{
	return FMatrix3x3(
		m_ppMatrix[0][0], m_ppMatrix[1][0], m_ppMatrix[2][0],
		m_ppMatrix[0][1], m_ppMatrix[1][1], m_ppMatrix[2][1],
		m_ppMatrix[0][2], m_ppMatrix[1][2], m_ppMatrix[2][2]);
}

//inline PhysicsLibrary::Basics::FMatrix3x3 PhysicsLibrary::Basics::FMatrix3x3::Cofactor() const
//{
//	return FMatrix3x3(
//		FMatrix3x3(m_ppMatrix[1][1], m_ppMatrix[1][2], m_ppMatrix[1][3], m_ppMatrix[2][1], m_ppMatrix[2][2], m_ppMatrix[2][3], m_ppMatrix[3][1], m_ppMatrix[3][2], m_ppMatrix[3][3]).Determinante(),
//		FMatrix3x3(m_ppMatrix[1][0], m_ppMatrix[1][2], m_ppMatrix[1][3], m_ppMatrix[2][0], m_ppMatrix[2][2], m_ppMatrix[2][3], m_ppMatrix[3][0], m_ppMatrix[3][2], m_ppMatrix[3][3]).Determinante(),
//		FMatrix3x3(m_ppMatrix[1][0], m_ppMatrix[1][1], m_ppMatrix[1][3], m_ppMatrix[2][0], m_ppMatrix[2][1], m_ppMatrix[2][3], m_ppMatrix[3][0], m_ppMatrix[3][1], m_ppMatrix[3][3]).Determinante(),
//		FMatrix3x3(m_ppMatrix[1][0], m_ppMatrix[1][1], m_ppMatrix[1][2], m_ppMatrix[2][0], m_ppMatrix[2][1], m_ppMatrix[2][2], m_ppMatrix[3][0], m_ppMatrix[3][1], m_ppMatrix[3][2]).Determinante(),
//		FMatrix3x3(m_ppMatrix[0][1], m_ppMatrix[0][2], m_ppMatrix[0][3], m_ppMatrix[2][1], m_ppMatrix[2][2], m_ppMatrix[2][3], m_ppMatrix[3][1], m_ppMatrix[3][2], m_ppMatrix[3][3]).Determinante(),
//		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][2], m_ppMatrix[0][3], m_ppMatrix[2][0], m_ppMatrix[2][2], m_ppMatrix[2][3], m_ppMatrix[3][0], m_ppMatrix[3][2], m_ppMatrix[3][3]).Determinante(),
//		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][1], m_ppMatrix[0][3], m_ppMatrix[2][0], m_ppMatrix[2][1], m_ppMatrix[2][3], m_ppMatrix[3][0], m_ppMatrix[3][1], m_ppMatrix[3][3]).Determinante(),
//		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][1], m_ppMatrix[0][2], m_ppMatrix[2][0], m_ppMatrix[2][1], m_ppMatrix[2][2], m_ppMatrix[3][0], m_ppMatrix[3][1], m_ppMatrix[3][2]).Determinante(),
//		FMatrix3x3(m_ppMatrix[0][1], m_ppMatrix[0][2], m_ppMatrix[0][3], m_ppMatrix[1][1], m_ppMatrix[1][2], m_ppMatrix[1][3], m_ppMatrix[3][1], m_ppMatrix[3][2], m_ppMatrix[3][3]).Determinante(),
//		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][2], m_ppMatrix[0][3], m_ppMatrix[1][0], m_ppMatrix[1][2], m_ppMatrix[1][3], m_ppMatrix[3][0], m_ppMatrix[3][2], m_ppMatrix[3][3]).Determinante(),
//		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][1], m_ppMatrix[0][3], m_ppMatrix[1][0], m_ppMatrix[1][1], m_ppMatrix[1][3], m_ppMatrix[3][0], m_ppMatrix[3][1], m_ppMatrix[3][3]).Determinante(),
//		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][1], m_ppMatrix[0][2], m_ppMatrix[1][0], m_ppMatrix[1][1], m_ppMatrix[1][2], m_ppMatrix[3][0], m_ppMatrix[3][1], m_ppMatrix[3][2]).Determinante(),
//		FMatrix3x3(m_ppMatrix[0][1], m_ppMatrix[0][2], m_ppMatrix[0][3], m_ppMatrix[1][1], m_ppMatrix[1][2], m_ppMatrix[1][3], m_ppMatrix[2][1], m_ppMatrix[2][2], m_ppMatrix[3][3]).Determinante(),
//		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][2], m_ppMatrix[0][3], m_ppMatrix[1][0], m_ppMatrix[1][2], m_ppMatrix[1][3], m_ppMatrix[2][0], m_ppMatrix[2][2], m_ppMatrix[2][3]).Determinante(),
//		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][1], m_ppMatrix[0][3], m_ppMatrix[1][0], m_ppMatrix[1][1], m_ppMatrix[1][3], m_ppMatrix[2][0], m_ppMatrix[2][1], m_ppMatrix[2][3]).Determinante(),
//		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][1], m_ppMatrix[0][2], m_ppMatrix[1][0], m_ppMatrix[1][1], m_ppMatrix[1][2], m_ppMatrix[2][0], m_ppMatrix[2][1], m_ppMatrix[2][2]).Determinante());
//}

//inline const PhysicsLibrary::Basics::FMatrix3x3 PhysicsLibrary::Basics::FMatrix3x3::Inverse()
//{
//	if (std::fabs(Determinante()) > EPSILON)
//	{
//		FMatrix3x3 cofactor = Cofactor();
//		FMatrix3x3 transposedMat = cofactor.Transpose();
//		return transposedMat / transposedMat.Determinante();
//	}
//	else
//		return FMatrix3x3(false);
//}

inline PhysicsLibrary::Basics::FMatrix3x3 PhysicsLibrary::Basics::FMatrix3x3::operator*(const FMatrix3x3& mat) const
{
	return FMatrix3x3(
		(m_ppMatrix[0][0] * mat.m_ppMatrix[0][0]) + (m_ppMatrix[0][1] * mat.m_ppMatrix[1][0]) + (m_ppMatrix[0][2] * mat.m_ppMatrix[2][0]),
		(m_ppMatrix[0][0] * mat.m_ppMatrix[0][1]) + (m_ppMatrix[0][1] * mat.m_ppMatrix[1][1]) + (m_ppMatrix[0][2] * mat.m_ppMatrix[2][1]),
		(m_ppMatrix[0][0] * mat.m_ppMatrix[0][2]) + (m_ppMatrix[0][1] * mat.m_ppMatrix[1][2]) + (m_ppMatrix[0][2] * mat.m_ppMatrix[2][2]),
		(m_ppMatrix[1][0] * mat.m_ppMatrix[0][0]) + (m_ppMatrix[1][1] * mat.m_ppMatrix[1][0]) + (m_ppMatrix[1][2] * mat.m_ppMatrix[2][0]),
		(m_ppMatrix[1][0] * mat.m_ppMatrix[0][1]) + (m_ppMatrix[1][1] * mat.m_ppMatrix[1][1]) + (m_ppMatrix[1][2] * mat.m_ppMatrix[2][1]),
		(m_ppMatrix[1][0] * mat.m_ppMatrix[0][2]) + (m_ppMatrix[1][1] * mat.m_ppMatrix[1][2]) + (m_ppMatrix[1][2] * mat.m_ppMatrix[2][2]),
		(m_ppMatrix[2][0] * mat.m_ppMatrix[0][0]) + (m_ppMatrix[2][1] * mat.m_ppMatrix[1][0]) + (m_ppMatrix[2][2] * mat.m_ppMatrix[2][0]),
		(m_ppMatrix[2][0] * mat.m_ppMatrix[0][1]) + (m_ppMatrix[2][1] * mat.m_ppMatrix[1][1]) + (m_ppMatrix[2][2] * mat.m_ppMatrix[2][1]),
		(m_ppMatrix[2][0] * mat.m_ppMatrix[0][2]) + (m_ppMatrix[2][1] * mat.m_ppMatrix[1][2]) + (m_ppMatrix[2][2] * mat.m_ppMatrix[2][2]));
}

inline PhysicsLibrary::Basics::FMatrix3x3 PhysicsLibrary::Basics::FMatrix3x3::operator+(const FMatrix3x3& mat) const
{
	return(FMatrix3x3(
		(m_ppMatrix[0][0] + mat.m_ppMatrix[0][0]), (m_ppMatrix[0][1] + mat.m_ppMatrix[0][1]), (m_ppMatrix[0][2] + mat.m_ppMatrix[0][2]),
		(m_ppMatrix[1][0] + mat.m_ppMatrix[1][0]), (m_ppMatrix[1][1] + mat.m_ppMatrix[1][1]), (m_ppMatrix[1][2] + mat.m_ppMatrix[1][2]),
		(m_ppMatrix[2][0] + mat.m_ppMatrix[2][0]), (m_ppMatrix[2][1] + mat.m_ppMatrix[2][1]), (m_ppMatrix[2][2] + mat.m_ppMatrix[2][2])));
}
inline PhysicsLibrary::Basics::FMatrix3x3 PhysicsLibrary::Basics::FMatrix3x3::operator-(const FMatrix3x3& mat) const
{
	return(FMatrix3x3(
		(m_ppMatrix[0][0] - mat.m_ppMatrix[0][0]), (m_ppMatrix[0][1] - mat.m_ppMatrix[0][1]), (m_ppMatrix[0][2] - mat.m_ppMatrix[0][2]),
		(m_ppMatrix[1][0] - mat.m_ppMatrix[1][0]), (m_ppMatrix[1][1] - mat.m_ppMatrix[1][1]), (m_ppMatrix[1][2] - mat.m_ppMatrix[1][2]),
		(m_ppMatrix[2][0] - mat.m_ppMatrix[2][0]), (m_ppMatrix[2][1] - mat.m_ppMatrix[2][1]), (m_ppMatrix[2][2] - mat.m_ppMatrix[2][2])));		
}
//inline PhysicsLibrary::Basics::FMatrix3x3 PhysicsLibrary::Basics::FMatrix3x3::operator/(FMatrix3x3& mat) const
//{
//	FMatrix3x3 invMat = mat.Inverse();
//	if (invMat != FMatrix3x3(false))
//		return *this * mat.Inverse();
//	else
//		return FMatrix3x3(false);
//}

inline PhysicsLibrary::Basics::FMatrix3x3 PhysicsLibrary::Basics::FMatrix3x3::operator/(const float& value) const
{
	return(FMatrix3x3(
		(m_ppMatrix[0][0] / value), (m_ppMatrix[0][1] / value), (m_ppMatrix[0][2] / value),
		(m_ppMatrix[1][0] / value), (m_ppMatrix[1][1] / value), (m_ppMatrix[1][2] / value),
		(m_ppMatrix[2][0] / value), (m_ppMatrix[2][1] / value), (m_ppMatrix[2][2] / value)));
}

inline void PhysicsLibrary::Basics::FMatrix3x3::operator*=(const FMatrix3x3& mat)
{
	m_ppMatrix[0][0] = (m_ppMatrix[0][0] *= mat.m_ppMatrix[0][0]) + (m_ppMatrix[0][1] *= mat.m_ppMatrix[1][0]) + (m_ppMatrix[0][2] *= mat.m_ppMatrix[2][0]);
	m_ppMatrix[0][1] = (m_ppMatrix[0][0] *= mat.m_ppMatrix[0][1]) + (m_ppMatrix[0][1] *= mat.m_ppMatrix[1][1]) + (m_ppMatrix[0][2] *= mat.m_ppMatrix[2][1]);
	m_ppMatrix[0][2] = (m_ppMatrix[0][0] *= mat.m_ppMatrix[0][2]) + (m_ppMatrix[0][1] *= mat.m_ppMatrix[1][2]) + (m_ppMatrix[0][2] *= mat.m_ppMatrix[2][2]);
	m_ppMatrix[1][0] = (m_ppMatrix[1][0] *= mat.m_ppMatrix[0][0]) + (m_ppMatrix[1][1] *= mat.m_ppMatrix[1][0]) + (m_ppMatrix[1][2] *= mat.m_ppMatrix[2][0]);
	m_ppMatrix[1][1] = (m_ppMatrix[1][0] *= mat.m_ppMatrix[0][1]) + (m_ppMatrix[1][1] *= mat.m_ppMatrix[1][1]) + (m_ppMatrix[1][2] *= mat.m_ppMatrix[2][1]);
	m_ppMatrix[1][2] = (m_ppMatrix[1][0] *= mat.m_ppMatrix[0][2]) + (m_ppMatrix[1][1] *= mat.m_ppMatrix[1][2]) + (m_ppMatrix[1][2] *= mat.m_ppMatrix[2][2]);
	m_ppMatrix[2][0] = (m_ppMatrix[2][0] *= mat.m_ppMatrix[0][0]) + (m_ppMatrix[2][1] *= mat.m_ppMatrix[1][0]) + (m_ppMatrix[2][2] *= mat.m_ppMatrix[2][0]);
	m_ppMatrix[2][1] = (m_ppMatrix[2][0] *= mat.m_ppMatrix[0][1]) + (m_ppMatrix[2][1] *= mat.m_ppMatrix[1][1]) + (m_ppMatrix[2][2] *= mat.m_ppMatrix[2][1]);
	m_ppMatrix[2][2] = (m_ppMatrix[2][0] *= mat.m_ppMatrix[0][2]) + (m_ppMatrix[2][1] *= mat.m_ppMatrix[1][2]) + (m_ppMatrix[2][2] *= mat.m_ppMatrix[2][2]);

}

inline void PhysicsLibrary::Basics::FMatrix3x3::operator+=(const FMatrix3x3& mat)
{
	m_ppMatrix[0][0] += mat.m_ppMatrix[0][0];
	m_ppMatrix[0][1] += mat.m_ppMatrix[0][1];
	m_ppMatrix[0][2] += mat.m_ppMatrix[0][2];
	m_ppMatrix[1][0] += mat.m_ppMatrix[1][0];
	m_ppMatrix[1][1] += mat.m_ppMatrix[1][1];
	m_ppMatrix[1][2] += mat.m_ppMatrix[1][2];
	m_ppMatrix[2][0] += mat.m_ppMatrix[2][0];
	m_ppMatrix[2][1] += mat.m_ppMatrix[2][1];
	m_ppMatrix[2][2] += mat.m_ppMatrix[2][2];

}
inline void PhysicsLibrary::Basics::FMatrix3x3::operator-=(const FMatrix3x3& mat)
{
	m_ppMatrix[0][0] -= mat.m_ppMatrix[0][0];
	m_ppMatrix[0][1] -= mat.m_ppMatrix[0][1];
	m_ppMatrix[0][2] -= mat.m_ppMatrix[0][2];
	m_ppMatrix[1][0] -= mat.m_ppMatrix[1][0];
	m_ppMatrix[1][1] -= mat.m_ppMatrix[1][1];
	m_ppMatrix[1][2] -= mat.m_ppMatrix[1][2];
	m_ppMatrix[2][0] -= mat.m_ppMatrix[2][0];
	m_ppMatrix[2][1] -= mat.m_ppMatrix[2][1];
	m_ppMatrix[2][2] -= mat.m_ppMatrix[2][2];

}

//inline void PhysicsLibrary::Basics::FMatrix3x3::operator/=(FMatrix3x3& mat)
//{
//	*this *= mat.Inverse();
//}

inline bool PhysicsLibrary::Basics::FMatrix3x3::operator==(const FMatrix3x3& mat)
{
	return std::fabs(m_ppMatrix[0][0] - mat.m_ppMatrix[0][0]) <= EPSILON
		&& std::fabs(m_ppMatrix[0][1] - mat.m_ppMatrix[0][1]) <= EPSILON
		&& std::fabs(m_ppMatrix[0][2] - mat.m_ppMatrix[0][2]) <= EPSILON
		&& std::fabs(m_ppMatrix[1][0] - mat.m_ppMatrix[1][0]) <= EPSILON
		&& std::fabs(m_ppMatrix[1][1] - mat.m_ppMatrix[1][1]) <= EPSILON
		&& std::fabs(m_ppMatrix[1][2] - mat.m_ppMatrix[1][2]) <= EPSILON
		&& std::fabs(m_ppMatrix[2][0] - mat.m_ppMatrix[2][0]) <= EPSILON
		&& std::fabs(m_ppMatrix[2][1] - mat.m_ppMatrix[2][1]) <= EPSILON
		&& std::fabs(m_ppMatrix[2][2] - mat.m_ppMatrix[2][2]) <= EPSILON;
}

inline bool PhysicsLibrary::Basics::FMatrix3x3::operator!=(const FMatrix3x3& mat)
{
	return std::fabs(m_ppMatrix[0][0] - mat.m_ppMatrix[0][0]) <= EPSILON
		|| std::fabs(m_ppMatrix[0][1] - mat.m_ppMatrix[0][1]) <= EPSILON
		|| std::fabs(m_ppMatrix[0][2] - mat.m_ppMatrix[0][2]) <= EPSILON
		|| std::fabs(m_ppMatrix[1][0] - mat.m_ppMatrix[1][0]) <= EPSILON
		|| std::fabs(m_ppMatrix[1][1] - mat.m_ppMatrix[1][1]) <= EPSILON
		|| std::fabs(m_ppMatrix[1][2] - mat.m_ppMatrix[1][2]) <= EPSILON
		|| std::fabs(m_ppMatrix[2][0] - mat.m_ppMatrix[2][0]) <= EPSILON
		|| std::fabs(m_ppMatrix[2][1] - mat.m_ppMatrix[2][1]) <= EPSILON
		|| std::fabs(m_ppMatrix[2][2] - mat.m_ppMatrix[2][2]) <= EPSILON
;
}

inline PhysicsLibrary::Basics::FMatrix3x3::~FMatrix3x3()
{
	for (int i = 0; i < 3; i++)
	{
		delete[] m_ppMatrix[i];
	}
	delete[] m_ppMatrix;
}
