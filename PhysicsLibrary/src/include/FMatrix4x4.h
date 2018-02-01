#pragma once

#pragma region Internal Includes
#include "BaseMath.h"
#include "FVector4D.h"
#include "FMatrix3x3.h"
#pragma endregion 
#pragma region External Includes
#include <cstdint>
#include <cmath>
#pragma endregion 

namespace PhysicsLibrary
{
	namespace Basics
	{
		///\class FMatrix4x4.h "src/include/FMatrix4x4.h
		///\brief Matrix class for a 4x4 Matrix. Works intern with floats. If you need more accuracy pls use the DMatrix class
		/// 
		class FMatrix4x4
		{
		private: 
			float** m_ppMatrix;
		public: 
			/**
			* Default Constructor sets all values to zero			
			*/
			inline FMatrix4x4(bool identity);
			/** 
			* Constructor to initialize the matrix with values. Every row will get a Vector4D.
			*
			* @param vec1 The first Vector4D which will fill the m_ppMatrix[0] row.
			* @param vec2 The second Vector4D which will fill the m_ppMatrix[1] row. 
			* @param vec3 The third Vector4D which will fill the m_ppMatrix[2] row. 
			* @param vec4 The fourth Vector4D which will fill the m_ppMatrix[3] row. */
			inline FMatrix4x4(const FVector4D& vec1,const FVector4D& vec2,const FVector4D& vec3,const FVector4D& vec4);
			/**
			* Constructor to initialite the matrix with values. You can set all values manually. 
			* 
			* @param value1 The First float value to set in the matrix. 
			* @param value2 The second float value to set in the matrix. 
			* @param value3 The third float value to set in the matrix. 
			* @param value4 The fourth float value to set in the matrix. 
			* @param value5 The fifth float value to set in the matrix. 
			* @param value6 The 6th float value to set in the matrix. 
			* @param value7 The 7th float value to set in the matrix. 
			* @param value8 The 8th float value to set in the matrix. 
			* @param value9 The 9th float value to set in the matrix. 
			* @param value10 The 10th float value to set in the matrix. 
			* @param value11 The 11th float value to set in the matrix. 
			* @param value12 The 12th float value to set in the matrix. 
			* @param value13 The 13th float value to set in the matrix. 
			* @param value14 The 14th float value to set in the matrix. 
			* @param value15 The 15th float value to set in the matrix. 
			* @param value16 The 16th float value to set in the matrix. 
			*/
			inline FMatrix4x4(const float& value1, const float& value2, const float& value3, const float& value4,
				const float& value5, const float& value6, const float& value7, const float& value8,
				const float& value9, const float& value10, const float& value11, const float& value12,
				const float& value13, const float& value14, const float& value15, const float& value16);
			/**
			* Copy Constructor 
			* 
			* @param mat The Matrix you want to copy 
			*/
			inline FMatrix4x4(const FMatrix4x4& mat); 
			/**
			* Getter function for the current Matrix
			* 
			* @return The current 2D array of the matrix
			*/
			inline float** GetMatrix() const; 
			/**
			* Getter function for the value on the input position
			* 
			* @param row The row you want to get the value from
			* @param column The column you want to get the value from
			* return The value on the position
			*/
			inline float GetValue(const uint8_t& row, const uint8_t& column); 
			/**
			* Setter function to set a value in the matrix. First Value describes the row, second the column where you will set the value. 
			* 
			* @param row The row, where the value should set. 
			* @param column The column, where the value should set. 
			* @param value The value you want to set on the position in the matrix.
			*/
			inline void SetValue(const uint8_t& row, const uint8_t& column, const float& value);
			/**
			* Calculates the detereminante of the current matrix
			* 
			* @return The determinante of the current matrix
			*/
			inline float Determinante() const;
			/**
			* Transpose the current Matrix(turns all rows to columns and vice-versa).
			*
			*@return The transposed matrix
			*/
			inline FMatrix4x4 Transpose() const; 
			/**
			* Calculates the cofactor matrix of the current matrix
			*
			* @return The cofactor matrix
			*/
			inline FMatrix4x4 Cofactor() const;
			/**
			* Calculates the inverse of the current matrix
			* 
			* @return The calculated inverse Matrix
			*/
			inline const FMatrix4x4 Inverse();
			/**
			* Multiplies a translation matrix to the current Matrix
			*
			* @param vec The vector you want to translate the current vector
			*/
			inline void Translate(const FVector3D& vec);
			/**
			* Multiplies a rotation matrix around the x-axis with a declared angel to the current matrix
			*
			* @param angle The angle you want to rotate the matrix 
			*/
			inline void RotateX(const float& angle);
			/**
			* Multiplies a rotation matrix around the y-axis with a declared angel to the current matrix
			*
			* @param angle The angle you want to rotate the matrix
			*/
			inline void RotateY(const float& angle);
			/**
			* Multiplies a rotation matrix around the z-axis with a declared angel to the current matrix
			*
			* @param angle The angle you want to rotate the matrix
			*/
			inline void RotateZ(const float& angle);
			/**
			* Multiplies a scaling matrix with an value to the current matrix
			*
			* @param value The value you want to scale the current matrix. 
			*/
			inline void Scale(const float& value);
			/**
			* Operation overload for the multiplication of two matrices
			* 
			* @param mat The base Matrix
			* @return The calculated matrix
			*/
			inline FMatrix4x4 operator*(const FMatrix4x4& mat) const;
			/**
			* Overloads the addition operator
			*
			* @param mat The Matrix you want to add to the current matrix.
			* @return The calculated matrix
			*/
			inline FMatrix4x4 operator+(const FMatrix4x4& mat) const; 
			/**
			* Overloards the substrace operator
			* 
			* @param mat The matrix you want to substract from the current matrix.
			* @return The calculated matrix
			*/
			inline FMatrix4x4 operator-(const FMatrix4x4& mat) const; 
			/**
			* Overloads the divide operator
			* 
			* @param mat The matrix you want to divide through the current matrix. 
			* @return The calculated matrix
			*/
			inline FMatrix4x4 operator/(FMatrix4x4& mat) const; 
			/**
			* Overloads the divide operator
			*
			* @param value The float value you will divide the matrix through
			* @return The calculated matrix
			*/
			inline FMatrix4x4 operator/(const float& value) const; 
			/**
			* Operation overload for the multiplication-equals operation with another Matrix
			*
			* @param mat The matrix you want to multiply to the current Matrix
			*/
			inline void operator*=(const FMatrix4x4& mat);
			/**
			* Operation overload for the add-equals operation with another matrix4x4
			* 
			* @param mat The matrix you want to add to the current matrix. 
			*/
			inline void operator+=(const FMatrix4x4& mat);
			/**
			* Operation overload for the substract-equals operator with another matrix4x4
			* 
			* @param mat The matrix you want to substract from the current matrix. 
			*/
			inline void operator-=(const FMatrix4x4& mat);
			/** 
			* Operation overload for the divide-equals operator with another matrix4x4
			*
			* @param mat The matrix you want to divide through the current matrix. 
			*/
			inline void operator/=(FMatrix4x4& mat);
			/** 
			* Operation overloard for the equals-equals operator with another matrix4x4
			*
			* @patam mat The matrix you want to est if it's equal to the current matrix. 
			* @return True or false depending on the test result
			*/
			inline bool operator==(const FMatrix4x4& mat);
			/**
			* Operation overload for the negate-equals operator with another matrix4x4
			*
			* @param mat The matrix you want to test if it's not equal to the current matrix. 
			* @return True or false depending on the test result
			*/
			inline bool operator!=(const FMatrix4x4& mat);
			/**
			* Destroys the 2d array 
			* 
			*/
			inline ~FMatrix4x4();
		};
	}
}