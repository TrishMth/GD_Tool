#include "include\FMatrix4x4.h"


inline PhysicsLibrary::Basics::FMatrix4x4::FMatrix4x4(bool identity)
{
	if (!identity)
		m_ppMatrix[4][4] = { 0 };
	else
	{
		m_ppMatrix[0][0] = 1; m_ppMatrix[0][1] = 0; m_ppMatrix[0][2] = 0; m_ppMatrix[0][3] = 0;
		m_ppMatrix[1][0] = 0; m_ppMatrix[1][1] = 1; m_ppMatrix[1][2] = 0; m_ppMatrix[1][3] = 0;
		m_ppMatrix[2][0] = 0; m_ppMatrix[2][1] = 0; m_ppMatrix[2][2] = 1; m_ppMatrix[2][3] = 0;
		m_ppMatrix[3][0] = 0; m_ppMatrix[3][1] = 0; m_ppMatrix[3][2] = 0; m_ppMatrix[3][3] = 1;
	}
}

inline PhysicsLibrary::Basics::FMatrix4x4::FMatrix4x4(const FMatrix4x4& mat)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_ppMatrix[i][j] = mat.m_ppMatrix[i][j];
		}
	}
}

inline PhysicsLibrary::Basics::FMatrix4x4::FMatrix4x4(const FVector4D& vec1, const FVector4D& vec2, const FVector4D& vec3, const FVector4D& vec4)
{
	m_ppMatrix[0][0] = vec1.GetX(); m_ppMatrix[0][1] = vec1.GetY(); m_ppMatrix[0][2] = vec1.GetZ(); m_ppMatrix[0][3] = vec1.GetW();
	m_ppMatrix[1][0] = vec2.GetX(); m_ppMatrix[1][1] = vec2.GetY(); m_ppMatrix[1][2] = vec2.GetZ(); m_ppMatrix[1][3] = vec2.GetW();
	m_ppMatrix[2][0] = vec3.GetX(); m_ppMatrix[2][1] = vec3.GetY(); m_ppMatrix[2][2] = vec3.GetZ(); m_ppMatrix[2][3] = vec3.GetW();
	m_ppMatrix[3][0] = vec4.GetX(); m_ppMatrix[3][1] = vec4.GetY(); m_ppMatrix[3][2] = vec4.GetZ(); m_ppMatrix[3][3] = vec4.GetW();
}

inline PhysicsLibrary::Basics::FMatrix4x4::FMatrix4x4(const float& value1, const float& value2, const float& value3, const float& value4,
	const float& value5, const float& value6, const float& value7, const float& value8,
	const float& value9, const float& value10, const float& value11, const float& value12,
	const float& value13, const float& value14, const float& value15, const float& value16)
{
	m_ppMatrix[0][0] = value1; m_ppMatrix[0][1] = value2; m_ppMatrix[0][2] = value3; m_ppMatrix[0][3] = value4;
	m_ppMatrix[1][0] = value5; m_ppMatrix[1][1] = value6; m_ppMatrix[1][2] = value7; m_ppMatrix[1][3] = value8;
	m_ppMatrix[2][0] = value9; m_ppMatrix[2][1] = value10; m_ppMatrix[2][2] = value11; m_ppMatrix[2][3] = value12;
	m_ppMatrix[3][0] = value13; m_ppMatrix[3][1] = value14; m_ppMatrix[3][2] = value15; m_ppMatrix[3][3] = value16;
}

inline float** PhysicsLibrary::Basics::FMatrix4x4::GetMatrix() const
{
	return m_ppMatrix;
}

inline float PhysicsLibrary::Basics::FMatrix4x4::GetValue(const uint8_t& row, const uint8_t& column)
{
	return m_ppMatrix[row][column];
}

inline void PhysicsLibrary::Basics::FMatrix4x4::SetValue(const uint8_t& row, const uint8_t& column, const float& value)
{
	m_ppMatrix[row][column] = value;
}

inline float PhysicsLibrary::Basics::FMatrix4x4::Determinante() const
{
	return
		(m_ppMatrix[0][0] * m_ppMatrix[1][1] * m_ppMatrix[2][2] * m_ppMatrix[3][3]) +
		(m_ppMatrix[0][1] * m_ppMatrix[1][2] * m_ppMatrix[2][3] * m_ppMatrix[3][0]) +
		(m_ppMatrix[0][2] * m_ppMatrix[1][3] * m_ppMatrix[2][0] * m_ppMatrix[3][1]) +
		(m_ppMatrix[0][3] * m_ppMatrix[1][0] * m_ppMatrix[2][1] * m_ppMatrix[3][2]) -
		(m_ppMatrix[3][0] * m_ppMatrix[2][1] * m_ppMatrix[1][2] * m_ppMatrix[0][3]) -
		(m_ppMatrix[3][1] * m_ppMatrix[2][2] * m_ppMatrix[1][3] * m_ppMatrix[0][0]) -
		(m_ppMatrix[3][2] * m_ppMatrix[2][3] * m_ppMatrix[1][0] * m_ppMatrix[0][1]) -
		(m_ppMatrix[3][3] * m_ppMatrix[2][0] * m_ppMatrix[1][1] * m_ppMatrix[0][2]);
}

inline PhysicsLibrary::Basics::FMatrix4x4 PhysicsLibrary::Basics::FMatrix4x4::Transpose() const
{
	return FMatrix4x4(
		m_ppMatrix[0][0], m_ppMatrix[1][0], m_ppMatrix[2][0], m_ppMatrix[3][0],
		m_ppMatrix[0][1], m_ppMatrix[1][1], m_ppMatrix[2][1], m_ppMatrix[3][1],
		m_ppMatrix[0][2], m_ppMatrix[1][2], m_ppMatrix[2][2], m_ppMatrix[3][2],
		m_ppMatrix[0][3], m_ppMatrix[1][3], m_ppMatrix[2][3], m_ppMatrix[3][3]);
}

inline PhysicsLibrary::Basics::FMatrix4x4 PhysicsLibrary::Basics::FMatrix4x4::Cofactor() const
{
	return FMatrix4x4(
		FMatrix3x3(m_ppMatrix[1][1], m_ppMatrix[1][2], m_ppMatrix[1][3], m_ppMatrix[2][1], m_ppMatrix[2][2], m_ppMatrix[2][3], m_ppMatrix[3][1], m_ppMatrix[3][2], m_ppMatrix[3][3]).Determinante(),
		FMatrix3x3(m_ppMatrix[1][0], m_ppMatrix[1][2], m_ppMatrix[1][3], m_ppMatrix[2][0], m_ppMatrix[2][2], m_ppMatrix[2][3], m_ppMatrix[3][0], m_ppMatrix[3][2], m_ppMatrix[3][3]).Determinante(),
		FMatrix3x3(m_ppMatrix[1][0], m_ppMatrix[1][1], m_ppMatrix[1][3], m_ppMatrix[2][0], m_ppMatrix[2][1], m_ppMatrix[2][3], m_ppMatrix[3][0], m_ppMatrix[3][1], m_ppMatrix[3][3]).Determinante(),
		FMatrix3x3(m_ppMatrix[1][0], m_ppMatrix[1][1], m_ppMatrix[1][2], m_ppMatrix[2][0], m_ppMatrix[2][1], m_ppMatrix[2][2], m_ppMatrix[3][0], m_ppMatrix[3][1], m_ppMatrix[3][2]).Determinante(),
		FMatrix3x3(m_ppMatrix[0][1], m_ppMatrix[0][2], m_ppMatrix[0][3], m_ppMatrix[2][1], m_ppMatrix[2][2], m_ppMatrix[2][3], m_ppMatrix[3][1], m_ppMatrix[3][2], m_ppMatrix[3][3]).Determinante(),
		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][2], m_ppMatrix[0][3], m_ppMatrix[2][0], m_ppMatrix[2][2], m_ppMatrix[2][3], m_ppMatrix[3][0], m_ppMatrix[3][2], m_ppMatrix[3][3]).Determinante(),
		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][1], m_ppMatrix[0][3], m_ppMatrix[2][0], m_ppMatrix[2][1], m_ppMatrix[2][3], m_ppMatrix[3][0], m_ppMatrix[3][1], m_ppMatrix[3][3]).Determinante(),
		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][1], m_ppMatrix[0][2], m_ppMatrix[2][0], m_ppMatrix[2][1], m_ppMatrix[2][2], m_ppMatrix[3][0], m_ppMatrix[3][1], m_ppMatrix[3][2]).Determinante(),
		FMatrix3x3(m_ppMatrix[0][1], m_ppMatrix[0][2], m_ppMatrix[0][3], m_ppMatrix[1][1], m_ppMatrix[1][2], m_ppMatrix[1][3], m_ppMatrix[3][1], m_ppMatrix[3][2], m_ppMatrix[3][3]).Determinante(),
		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][2], m_ppMatrix[0][3], m_ppMatrix[1][0], m_ppMatrix[1][2], m_ppMatrix[1][3], m_ppMatrix[3][0], m_ppMatrix[3][2], m_ppMatrix[3][3]).Determinante(),
		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][1], m_ppMatrix[0][3], m_ppMatrix[1][0], m_ppMatrix[1][1], m_ppMatrix[1][3], m_ppMatrix[3][0], m_ppMatrix[3][1], m_ppMatrix[3][3]).Determinante(),
		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][1], m_ppMatrix[0][2], m_ppMatrix[1][0], m_ppMatrix[1][1], m_ppMatrix[1][2], m_ppMatrix[3][0], m_ppMatrix[3][1], m_ppMatrix[3][2]).Determinante(),
		FMatrix3x3(m_ppMatrix[0][1], m_ppMatrix[0][2], m_ppMatrix[0][3], m_ppMatrix[1][1], m_ppMatrix[1][2], m_ppMatrix[1][3], m_ppMatrix[2][1], m_ppMatrix[2][2], m_ppMatrix[3][3]).Determinante(),
		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][2], m_ppMatrix[0][3], m_ppMatrix[1][0], m_ppMatrix[1][2], m_ppMatrix[1][3], m_ppMatrix[2][0], m_ppMatrix[2][2], m_ppMatrix[2][3]).Determinante(),
		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][1], m_ppMatrix[0][3], m_ppMatrix[1][0], m_ppMatrix[1][1], m_ppMatrix[1][3], m_ppMatrix[2][0], m_ppMatrix[2][1], m_ppMatrix[2][3]).Determinante(),
		FMatrix3x3(m_ppMatrix[0][0], m_ppMatrix[0][1], m_ppMatrix[0][2], m_ppMatrix[1][0], m_ppMatrix[1][1], m_ppMatrix[1][2], m_ppMatrix[2][0], m_ppMatrix[2][1], m_ppMatrix[2][2]).Determinante());
}

inline const PhysicsLibrary::Basics::FMatrix4x4 PhysicsLibrary::Basics::FMatrix4x4::Inverse()
{
	if (std::fabs(Determinante()) > EPSILON)
	{
		FMatrix4x4 cofactor = Cofactor();
		FMatrix4x4 transposedMat = cofactor.Transpose();
		return transposedMat / transposedMat.Determinante();
	}
	else
		return FMatrix4x4(false);
}

inline void PhysicsLibrary::Basics::FMatrix4x4::Translate(const FVector3D& vec)
{
	*this *= FMatrix4x4(
		1, 0, 0, vec.GetX(),
		0, 1, 0, vec.GetY(),
		0, 0, 1, vec.GetZ(),
		0, 0, 0, 1);
}

inline void PhysicsLibrary::Basics::FMatrix4x4::RotateX(const float& angle)
{
	*this *= FMatrix4x4(
		cos(angle), -sin(angle), 0, 0,
		sin(angle), cos(angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}
inline void PhysicsLibrary::Basics::FMatrix4x4::RotateY(const float& angle)
{
	*this *= FMatrix4x4(
		1, 0, 0, 0,
		0, cos(angle), -sin(angle), 0,
		0, sin(angle), cos(angle), 0,
		0, 0, 0, 1);
}
inline void PhysicsLibrary::Basics::FMatrix4x4::RotateZ(const float& angle)
{
	*this *= FMatrix4x4(
		cos(angle), 0, sin(angle), 0,
		0, 1, 0, 0,
		-sin(angle), 0, cos(angle), 0,
		0, 0, 0, 1);
}

inline void PhysicsLibrary::Basics::FMatrix4x4::Scale(const float& value)
{
	*this *= FMatrix4x4(
		value, 0, 0, 0,
		0, value, 0, 0,
		0, 0, value, 0,
		0, 0, 0, 1); 
}

inline PhysicsLibrary::Basics::FMatrix4x4 PhysicsLibrary::Basics::FMatrix4x4::operator*(const FMatrix4x4& mat) const
{
	return FMatrix4x4(
		(m_ppMatrix[0][0] * mat.m_ppMatrix[0][0]) + (m_ppMatrix[0][1] * mat.m_ppMatrix[1][0]) + (m_ppMatrix[0][2] * mat.m_ppMatrix[2][0]) + (m_ppMatrix[0][3] * mat.m_ppMatrix[3][0]),
		(m_ppMatrix[0][0] * mat.m_ppMatrix[0][1]) + (m_ppMatrix[0][1] * mat.m_ppMatrix[1][1]) + (m_ppMatrix[0][2] * mat.m_ppMatrix[2][1]) + (m_ppMatrix[0][3] * mat.m_ppMatrix[3][1]),
		(m_ppMatrix[0][0] * mat.m_ppMatrix[0][2]) + (m_ppMatrix[0][1] * mat.m_ppMatrix[1][2]) + (m_ppMatrix[0][2] * mat.m_ppMatrix[2][2]) + (m_ppMatrix[0][3] * mat.m_ppMatrix[3][2]),
		(m_ppMatrix[0][0] * mat.m_ppMatrix[0][3]) + (m_ppMatrix[0][1] * mat.m_ppMatrix[1][3]) + (m_ppMatrix[0][2] * mat.m_ppMatrix[2][3]) + (m_ppMatrix[0][3] * mat.m_ppMatrix[3][3]),
		(m_ppMatrix[1][0] * mat.m_ppMatrix[0][0]) + (m_ppMatrix[1][1] * mat.m_ppMatrix[1][0]) + (m_ppMatrix[1][2] * mat.m_ppMatrix[2][0]) + (m_ppMatrix[1][3] * mat.m_ppMatrix[3][0]),
		(m_ppMatrix[1][0] * mat.m_ppMatrix[0][1]) + (m_ppMatrix[1][1] * mat.m_ppMatrix[1][1]) + (m_ppMatrix[1][2] * mat.m_ppMatrix[2][1]) + (m_ppMatrix[1][3] * mat.m_ppMatrix[3][1]),
		(m_ppMatrix[1][0] * mat.m_ppMatrix[0][2]) + (m_ppMatrix[1][1] * mat.m_ppMatrix[1][2]) + (m_ppMatrix[1][2] * mat.m_ppMatrix[2][2]) + (m_ppMatrix[1][3] * mat.m_ppMatrix[3][2]),
		(m_ppMatrix[1][0] * mat.m_ppMatrix[0][3]) + (m_ppMatrix[1][1] * mat.m_ppMatrix[1][3]) + (m_ppMatrix[1][2] * mat.m_ppMatrix[2][3]) + (m_ppMatrix[1][3] * mat.m_ppMatrix[3][3]),
		(m_ppMatrix[2][0] * mat.m_ppMatrix[0][0]) + (m_ppMatrix[2][1] * mat.m_ppMatrix[1][0]) + (m_ppMatrix[2][2] * mat.m_ppMatrix[2][0]) + (m_ppMatrix[2][3] * mat.m_ppMatrix[3][0]),
		(m_ppMatrix[2][0] * mat.m_ppMatrix[0][1]) + (m_ppMatrix[2][1] * mat.m_ppMatrix[1][1]) + (m_ppMatrix[2][2] * mat.m_ppMatrix[2][1]) + (m_ppMatrix[2][3] * mat.m_ppMatrix[3][1]),
		(m_ppMatrix[2][0] * mat.m_ppMatrix[0][2]) + (m_ppMatrix[2][1] * mat.m_ppMatrix[1][2]) + (m_ppMatrix[2][2] * mat.m_ppMatrix[2][2]) + (m_ppMatrix[2][3] * mat.m_ppMatrix[3][2]),
		(m_ppMatrix[2][0] * mat.m_ppMatrix[0][3]) + (m_ppMatrix[2][1] * mat.m_ppMatrix[1][3]) + (m_ppMatrix[2][2] * mat.m_ppMatrix[2][3]) + (m_ppMatrix[2][3] * mat.m_ppMatrix[3][3]),
		(m_ppMatrix[3][0] * mat.m_ppMatrix[0][0]) + (m_ppMatrix[3][1] * mat.m_ppMatrix[1][0]) + (m_ppMatrix[3][2] * mat.m_ppMatrix[2][0]) + (m_ppMatrix[3][3] * mat.m_ppMatrix[3][0]),
		(m_ppMatrix[3][0] * mat.m_ppMatrix[0][1]) + (m_ppMatrix[3][1] * mat.m_ppMatrix[1][1]) + (m_ppMatrix[3][2] * mat.m_ppMatrix[2][1]) + (m_ppMatrix[3][3] * mat.m_ppMatrix[3][1]),
		(m_ppMatrix[3][0] * mat.m_ppMatrix[0][2]) + (m_ppMatrix[3][1] * mat.m_ppMatrix[1][2]) + (m_ppMatrix[3][2] * mat.m_ppMatrix[2][2]) + (m_ppMatrix[3][3] * mat.m_ppMatrix[3][2]),
		(m_ppMatrix[3][0] * mat.m_ppMatrix[0][3]) + (m_ppMatrix[3][1] * mat.m_ppMatrix[1][3]) + (m_ppMatrix[3][2] * mat.m_ppMatrix[2][3]) + (m_ppMatrix[3][3] * mat.m_ppMatrix[3][3]));
}

inline PhysicsLibrary::Basics::FMatrix4x4 PhysicsLibrary::Basics::FMatrix4x4::operator+(const FMatrix4x4& mat) const
{
	return(FMatrix4x4(
		(m_ppMatrix[0][0] + mat.m_ppMatrix[0][0]), (m_ppMatrix[0][1] + mat.m_ppMatrix[0][1]), (m_ppMatrix[0][2] + mat.m_ppMatrix[0][2]), (m_ppMatrix[0][3] + mat.m_ppMatrix[0][3]),
		(m_ppMatrix[1][0] + mat.m_ppMatrix[1][0]), (m_ppMatrix[1][1] + mat.m_ppMatrix[1][1]), (m_ppMatrix[1][2] + mat.m_ppMatrix[1][2]), (m_ppMatrix[1][3] + mat.m_ppMatrix[1][3]),
		(m_ppMatrix[2][0] + mat.m_ppMatrix[2][0]), (m_ppMatrix[2][1] + mat.m_ppMatrix[2][1]), (m_ppMatrix[2][2] + mat.m_ppMatrix[2][2]), (m_ppMatrix[2][3] + mat.m_ppMatrix[2][3]),
		(m_ppMatrix[3][0] + mat.m_ppMatrix[3][0]), (m_ppMatrix[3][1] + mat.m_ppMatrix[3][1]), (m_ppMatrix[3][2] + mat.m_ppMatrix[3][2]), (m_ppMatrix[3][3] + mat.m_ppMatrix[3][3])));
}
inline PhysicsLibrary::Basics::FMatrix4x4 PhysicsLibrary::Basics::FMatrix4x4::operator-(const FMatrix4x4& mat) const
{
	return(FMatrix4x4(
		(m_ppMatrix[0][0] - mat.m_ppMatrix[0][0]), (m_ppMatrix[0][1] - mat.m_ppMatrix[0][1]), (m_ppMatrix[0][2] - mat.m_ppMatrix[0][2]), (m_ppMatrix[0][3] - mat.m_ppMatrix[0][3]),
		(m_ppMatrix[1][0] - mat.m_ppMatrix[1][0]), (m_ppMatrix[1][1] - mat.m_ppMatrix[1][1]), (m_ppMatrix[1][2] - mat.m_ppMatrix[1][2]), (m_ppMatrix[1][3] - mat.m_ppMatrix[1][3]),
		(m_ppMatrix[2][0] - mat.m_ppMatrix[2][0]), (m_ppMatrix[2][1] - mat.m_ppMatrix[2][1]), (m_ppMatrix[2][2] - mat.m_ppMatrix[2][2]), (m_ppMatrix[2][3] - mat.m_ppMatrix[2][3]),
		(m_ppMatrix[3][0] - mat.m_ppMatrix[3][0]), (m_ppMatrix[3][1] - mat.m_ppMatrix[3][1]), (m_ppMatrix[3][2] - mat.m_ppMatrix[3][2]), (m_ppMatrix[3][3] - mat.m_ppMatrix[3][3])));
}
inline PhysicsLibrary::Basics::FMatrix4x4 PhysicsLibrary::Basics::FMatrix4x4::operator/(FMatrix4x4& mat) const
{
	FMatrix4x4 invMat = mat.Inverse();
	if (invMat != FMatrix4x4(false))
		return *this * mat.Inverse();
	else
		return FMatrix4x4(false);
}

inline PhysicsLibrary::Basics::FMatrix4x4 PhysicsLibrary::Basics::FMatrix4x4::operator/(const float& value) const
{
	return(FMatrix4x4(
		(m_ppMatrix[0][0] / value), (m_ppMatrix[0][1] / value), (m_ppMatrix[0][2] / value), (m_ppMatrix[0][3] / value),
		(m_ppMatrix[1][0] / value), (m_ppMatrix[1][1] / value), (m_ppMatrix[1][2] / value), (m_ppMatrix[1][3] / value),
		(m_ppMatrix[2][0] / value), (m_ppMatrix[2][1] / value), (m_ppMatrix[2][2] / value), (m_ppMatrix[2][3] / value),
		(m_ppMatrix[3][0] / value), (m_ppMatrix[3][1] / value), (m_ppMatrix[3][2] / value), (m_ppMatrix[3][3] / value)));
}

inline void PhysicsLibrary::Basics::FMatrix4x4::operator*=(const FMatrix4x4& mat)
{
	m_ppMatrix[0][0] = (m_ppMatrix[0][0] *= mat.m_ppMatrix[0][0]) + (m_ppMatrix[0][1] *= mat.m_ppMatrix[1][0]) + (m_ppMatrix[0][2] *= mat.m_ppMatrix[2][0]) + (m_ppMatrix[0][3] *= mat.m_ppMatrix[3][0]);
	m_ppMatrix[0][1] = (m_ppMatrix[0][0] *= mat.m_ppMatrix[0][1]) + (m_ppMatrix[0][1] *= mat.m_ppMatrix[1][1]) + (m_ppMatrix[0][2] *= mat.m_ppMatrix[2][1]) + (m_ppMatrix[0][3] *= mat.m_ppMatrix[3][1]);
	m_ppMatrix[0][2] = (m_ppMatrix[0][0] *= mat.m_ppMatrix[0][2]) + (m_ppMatrix[0][1] *= mat.m_ppMatrix[1][2]) + (m_ppMatrix[0][2] *= mat.m_ppMatrix[2][2]) + (m_ppMatrix[0][3] *= mat.m_ppMatrix[3][2]);
	m_ppMatrix[0][3] = (m_ppMatrix[0][0] *= mat.m_ppMatrix[0][3]) + (m_ppMatrix[0][1] *= mat.m_ppMatrix[1][3]) + (m_ppMatrix[0][2] *= mat.m_ppMatrix[2][3]) + (m_ppMatrix[0][3] *= mat.m_ppMatrix[3][3]);
	m_ppMatrix[1][0] = (m_ppMatrix[1][0] *= mat.m_ppMatrix[0][0]) + (m_ppMatrix[1][1] *= mat.m_ppMatrix[1][0]) + (m_ppMatrix[1][2] *= mat.m_ppMatrix[2][0]) + (m_ppMatrix[1][3] *= mat.m_ppMatrix[3][0]);
	m_ppMatrix[1][1] = (m_ppMatrix[1][0] *= mat.m_ppMatrix[0][1]) + (m_ppMatrix[1][1] *= mat.m_ppMatrix[1][1]) + (m_ppMatrix[1][2] *= mat.m_ppMatrix[2][1]) + (m_ppMatrix[1][3] *= mat.m_ppMatrix[3][1]);
	m_ppMatrix[1][2] = (m_ppMatrix[1][0] *= mat.m_ppMatrix[0][2]) + (m_ppMatrix[1][1] *= mat.m_ppMatrix[1][2]) + (m_ppMatrix[1][2] *= mat.m_ppMatrix[2][2]) + (m_ppMatrix[1][3] *= mat.m_ppMatrix[3][2]);
	m_ppMatrix[1][3] = (m_ppMatrix[1][0] *= mat.m_ppMatrix[0][3]) + (m_ppMatrix[1][1] *= mat.m_ppMatrix[1][3]) + (m_ppMatrix[1][2] *= mat.m_ppMatrix[2][3]) + (m_ppMatrix[1][3] *= mat.m_ppMatrix[3][3]);
	m_ppMatrix[2][0] = (m_ppMatrix[2][0] *= mat.m_ppMatrix[0][0]) + (m_ppMatrix[2][1] *= mat.m_ppMatrix[1][0]) + (m_ppMatrix[2][2] *= mat.m_ppMatrix[2][0]) + (m_ppMatrix[2][3] *= mat.m_ppMatrix[3][0]);
	m_ppMatrix[2][1] = (m_ppMatrix[2][0] *= mat.m_ppMatrix[0][1]) + (m_ppMatrix[2][1] *= mat.m_ppMatrix[1][1]) + (m_ppMatrix[2][2] *= mat.m_ppMatrix[2][1]) + (m_ppMatrix[2][3] *= mat.m_ppMatrix[3][1]);
	m_ppMatrix[2][2] = (m_ppMatrix[2][0] *= mat.m_ppMatrix[0][2]) + (m_ppMatrix[2][1] *= mat.m_ppMatrix[1][2]) + (m_ppMatrix[2][2] *= mat.m_ppMatrix[2][2]) + (m_ppMatrix[2][3] *= mat.m_ppMatrix[3][2]);
	m_ppMatrix[2][3] = (m_ppMatrix[2][0] *= mat.m_ppMatrix[0][3]) + (m_ppMatrix[2][1] *= mat.m_ppMatrix[1][3]) + (m_ppMatrix[2][2] *= mat.m_ppMatrix[2][3]) + (m_ppMatrix[2][3] *= mat.m_ppMatrix[3][3]);
	m_ppMatrix[3][0] = (m_ppMatrix[3][0] *= mat.m_ppMatrix[0][0]) + (m_ppMatrix[3][1] *= mat.m_ppMatrix[1][0]) + (m_ppMatrix[3][2] *= mat.m_ppMatrix[2][0]) + (m_ppMatrix[3][3] *= mat.m_ppMatrix[3][0]);
	m_ppMatrix[3][1] = (m_ppMatrix[3][0] *= mat.m_ppMatrix[0][1]) + (m_ppMatrix[3][1] *= mat.m_ppMatrix[1][1]) + (m_ppMatrix[3][2] *= mat.m_ppMatrix[2][1]) + (m_ppMatrix[3][3] *= mat.m_ppMatrix[3][1]);
	m_ppMatrix[3][2] = (m_ppMatrix[3][0] *= mat.m_ppMatrix[0][2]) + (m_ppMatrix[3][1] *= mat.m_ppMatrix[1][2]) + (m_ppMatrix[3][2] *= mat.m_ppMatrix[2][2]) + (m_ppMatrix[3][3] *= mat.m_ppMatrix[3][2]);
	m_ppMatrix[3][3] = (m_ppMatrix[3][0] *= mat.m_ppMatrix[0][3]) + (m_ppMatrix[3][1] *= mat.m_ppMatrix[1][3]) + (m_ppMatrix[3][2] *= mat.m_ppMatrix[2][3]) + (m_ppMatrix[3][3] *= mat.m_ppMatrix[3][3]);
}

inline void PhysicsLibrary::Basics::FMatrix4x4::operator+=(const FMatrix4x4& mat)
{
	m_ppMatrix[0][0] += mat.m_ppMatrix[0][0];
	m_ppMatrix[0][1] += mat.m_ppMatrix[0][1];
	m_ppMatrix[0][2] += mat.m_ppMatrix[0][2];
	m_ppMatrix[0][3] += mat.m_ppMatrix[0][3];
	m_ppMatrix[1][0] += mat.m_ppMatrix[1][0];
	m_ppMatrix[1][1] += mat.m_ppMatrix[1][1];
	m_ppMatrix[1][2] += mat.m_ppMatrix[1][2];
	m_ppMatrix[1][3] += mat.m_ppMatrix[1][3];
	m_ppMatrix[2][0] += mat.m_ppMatrix[2][0];
	m_ppMatrix[2][1] += mat.m_ppMatrix[2][1];
	m_ppMatrix[2][2] += mat.m_ppMatrix[2][2];
	m_ppMatrix[2][3] += mat.m_ppMatrix[2][3];
	m_ppMatrix[3][0] += mat.m_ppMatrix[3][0];
	m_ppMatrix[3][1] += mat.m_ppMatrix[3][1];
	m_ppMatrix[3][2] += mat.m_ppMatrix[3][2];
	m_ppMatrix[3][3] += mat.m_ppMatrix[3][3];
}
inline void PhysicsLibrary::Basics::FMatrix4x4::operator-=(const FMatrix4x4& mat)
{
	m_ppMatrix[0][0] -= mat.m_ppMatrix[0][0];
	m_ppMatrix[0][1] -= mat.m_ppMatrix[0][1];
	m_ppMatrix[0][2] -= mat.m_ppMatrix[0][2];
	m_ppMatrix[0][3] -= mat.m_ppMatrix[0][3];
	m_ppMatrix[1][0] -= mat.m_ppMatrix[1][0];
	m_ppMatrix[1][1] -= mat.m_ppMatrix[1][1];
	m_ppMatrix[1][2] -= mat.m_ppMatrix[1][2];
	m_ppMatrix[1][3] -= mat.m_ppMatrix[1][3];
	m_ppMatrix[2][0] -= mat.m_ppMatrix[2][0];
	m_ppMatrix[2][1] -= mat.m_ppMatrix[2][1];
	m_ppMatrix[2][2] -= mat.m_ppMatrix[2][2];
	m_ppMatrix[2][3] -= mat.m_ppMatrix[2][3];
	m_ppMatrix[3][0] -= mat.m_ppMatrix[3][0];
	m_ppMatrix[3][1] -= mat.m_ppMatrix[3][1];
	m_ppMatrix[3][2] -= mat.m_ppMatrix[3][2];
	m_ppMatrix[3][3] -= mat.m_ppMatrix[3][3];
}

inline void PhysicsLibrary::Basics::FMatrix4x4::operator/=(FMatrix4x4& mat)
{
	*this *= mat.Inverse();
}

inline bool PhysicsLibrary::Basics::FMatrix4x4::operator==(const FMatrix4x4& mat)
{
	return std::fabs(m_ppMatrix[0][0] - mat.m_ppMatrix[0][0]) <= EPSILON
		&& std::fabs(m_ppMatrix[0][1] - mat.m_ppMatrix[0][1]) <= EPSILON
		&& std::fabs(m_ppMatrix[0][2] - mat.m_ppMatrix[0][2]) <= EPSILON
		&& std::fabs(m_ppMatrix[0][3] - mat.m_ppMatrix[0][3]) <= EPSILON
		&& std::fabs(m_ppMatrix[1][0] - mat.m_ppMatrix[1][0]) <= EPSILON
		&& std::fabs(m_ppMatrix[1][1] - mat.m_ppMatrix[1][1]) <= EPSILON
		&& std::fabs(m_ppMatrix[1][2] - mat.m_ppMatrix[1][2]) <= EPSILON
		&& std::fabs(m_ppMatrix[1][3] - mat.m_ppMatrix[1][3]) <= EPSILON
		&& std::fabs(m_ppMatrix[2][0] - mat.m_ppMatrix[2][0]) <= EPSILON
		&& std::fabs(m_ppMatrix[2][1] - mat.m_ppMatrix[2][1]) <= EPSILON
		&& std::fabs(m_ppMatrix[2][2] - mat.m_ppMatrix[2][2]) <= EPSILON
		&& std::fabs(m_ppMatrix[2][3] - mat.m_ppMatrix[2][3]) <= EPSILON
		&& std::fabs(m_ppMatrix[3][0] - mat.m_ppMatrix[3][0]) <= EPSILON
		&& std::fabs(m_ppMatrix[3][1] - mat.m_ppMatrix[3][1]) <= EPSILON
		&& std::fabs(m_ppMatrix[3][2] - mat.m_ppMatrix[3][2]) <= EPSILON
		&& std::fabs(m_ppMatrix[3][3] - mat.m_ppMatrix[3][3]) <= EPSILON;
}

inline bool PhysicsLibrary::Basics::FMatrix4x4::operator!=(const FMatrix4x4& mat)
{
	return std::fabs(m_ppMatrix[0][0] - mat.m_ppMatrix[0][0]) <= EPSILON
		|| std::fabs(m_ppMatrix[0][1] - mat.m_ppMatrix[0][1]) <= EPSILON
		|| std::fabs(m_ppMatrix[0][2] - mat.m_ppMatrix[0][2]) <= EPSILON
		|| std::fabs(m_ppMatrix[0][3] - mat.m_ppMatrix[0][3]) <= EPSILON
		|| std::fabs(m_ppMatrix[1][0] - mat.m_ppMatrix[1][0]) <= EPSILON
		|| std::fabs(m_ppMatrix[1][1] - mat.m_ppMatrix[1][1]) <= EPSILON
		|| std::fabs(m_ppMatrix[1][2] - mat.m_ppMatrix[1][2]) <= EPSILON
		|| std::fabs(m_ppMatrix[1][3] - mat.m_ppMatrix[1][3]) <= EPSILON
		|| std::fabs(m_ppMatrix[2][0] - mat.m_ppMatrix[2][0]) <= EPSILON
		|| std::fabs(m_ppMatrix[2][1] - mat.m_ppMatrix[2][1]) <= EPSILON
		|| std::fabs(m_ppMatrix[2][2] - mat.m_ppMatrix[2][2]) <= EPSILON
		|| std::fabs(m_ppMatrix[2][3] - mat.m_ppMatrix[2][3]) <= EPSILON
		|| std::fabs(m_ppMatrix[3][0] - mat.m_ppMatrix[3][0]) <= EPSILON
		|| std::fabs(m_ppMatrix[3][1] - mat.m_ppMatrix[3][1]) <= EPSILON
		|| std::fabs(m_ppMatrix[3][2] - mat.m_ppMatrix[3][2]) <= EPSILON
		|| std::fabs(m_ppMatrix[3][3] - mat.m_ppMatrix[3][3]) <= EPSILON;
}

inline PhysicsLibrary::Basics::FMatrix4x4::~FMatrix4x4()
{
	for (int i = 0; i < 4; i++)
	{
		delete[] m_ppMatrix[i];
	}
	delete[] m_ppMatrix;
}
