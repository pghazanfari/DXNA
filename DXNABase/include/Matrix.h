#include <math.h>
#include "Vector3.h"

#pragma once

class Matrix
{
	public:
		float m11;
		float m12;
		float m13;
		float m14;

		float m21;
		float m22;
		float m23;
		float m24;

		float m31;
		float m32;
		float m33;
		float m34;

		float m41;
		float m42;
		float m43;
		float m44;


		//Constructor
		Matrix() : 
			m11(0.0f), m12(0.0f), m13(0.0f), m14(0.0f),
			m21(0.0f), m22(0.0f), m23(0.0f), m24(0.0f),
			m31(0.0f), m32(0.0f), m33(0.0f), m34(0.0f),
			m41(0.0f), m42(0.0f), m43(0.0f), m44(0.0f)
		{}


		//Member Functions
		inline void transpose()
		{
			float temp;

			temp = m12;
			m12 = m21;
			m21 = temp;

			temp = m13;
			m13 = m31;
			m31 = temp;

			temp = m14;
			m14 = m41;
			m41 = temp;

			temp = m23;
			m23 = m32;
			m32 = temp;

			temp = m24;
			m24 = m42;
			m42 = temp;

			temp = m34;
			m34 = m43;
			m43 = temp;
		}


		//Operators
		inline Matrix operator+(const Matrix& other)
		{
			Matrix result;
			result.m11 = m11 + other.m11;
			result.m12 = m12 + other.m12;
			result.m13 = m13 + other.m13;
			result.m14 = m14 + other.m14;

			result.m21 = m21 + other.m21;
			result.m22 = m22 + other.m22;
			result.m23 = m23 + other.m23;
			result.m24 = m24 + other.m24;

			result.m31 = m31 + other.m31;
			result.m32 = m32 + other.m32;
			result.m33 = m33 + other.m33;
			result.m34 = m34 + other.m34;

			result.m41 = m41 + other.m41;
			result.m42 = m42 + other.m42;
			result.m43 = m43 + other.m43;
			result.m44 = m44 + other.m44;

			return result;
		}

		inline Matrix operator-(const Matrix& other)
		{
			Matrix result;
			result.m11 = m11 - other.m11;
			result.m12 = m12 - other.m12;
			result.m13 = m13 - other.m13;
			result.m14 = m14 - other.m14;

			result.m21 = m21 - other.m21;
			result.m22 = m22 - other.m22;
			result.m23 = m23 - other.m23;
			result.m24 = m24 - other.m24;

			result.m31 = m31 - other.m31;
			result.m32 = m32 - other.m32;
			result.m33 = m33 - other.m33;
			result.m34 = m34 - other.m34;

			result.m41 = m41 - other.m41;
			result.m42 = m42 - other.m42;
			result.m43 = m43 - other.m43;
			result.m44 = m44 - other.m44;

			return result;
		}

		inline Matrix operator*(const Matrix& other)
		{
			Matrix result;

			//Row 1
			result.m11 =
				m11 * other.m11 +
				m12 * other.m21 +
				m13 * other.m31 +
				m14 * other.m41;

			result.m12 =
				m11 * other.m12 +
				m12 * other.m22 +
				m13 * other.m32 +
				m14 * other.m42;

			result.m13 =
				m11 * other.m13 +
				m12 * other.m23 +
				m13 * other.m33 +
				m14 * other.m43;

			result.m14 =
				m11 * other.m14 +
				m12 * other.m24 +
				m13 * other.m34 +
				m14 * other.m44;

			//Row 2
			result.m21 =
				m21 * other.m11 +
				m22 * other.m21 +
				m23 * other.m31 +
				m24 * other.m41;

			result.m22 =
				m21 * other.m12 +
				m22 * other.m22 +
				m23 * other.m32 +
				m24 * other.m42;

			result.m23 =
				m21 * other.m13 +
				m22 * other.m23 +
				m23 * other.m33 +
				m24 * other.m43;

			result.m24 =
				m21 * other.m14 +
				m22 * other.m24 +
				m23 * other.m34 +
				m24 * other.m44;

			//Row 3
			result.m31 =
				m31 * other.m11 +
				m32 * other.m21 +
				m33 * other.m31 +
				m34 * other.m41;

			result.m32 =
				m31 * other.m12 +
				m32 * other.m22 +
				m33 * other.m32 +
				m34 * other.m42;

			result.m33 =
				m31 * other.m13 +
				m32 * other.m23 +
				m33 * other.m33 +
				m34 * other.m43;

			result.m34 =
				m31 * other.m14 +
				m32 * other.m24 +
				m33 * other.m34 +
				m34 * other.m44;

			//Row 4
			result.m41 =
				m41 * other.m11 +
				m42 * other.m21 +
				m43 * other.m31 +
				m44 * other.m41;

			result.m42 =
				m41 * other.m12 +
				m42 * other.m22 +
				m43 * other.m32 +
				m44 * other.m42;

			result.m43 =
				m41 * other.m13 +
				m42 * other.m23 +
				m43 * other.m33 +
				m44 * other.m43;

			result.m44 =
				m41 * other.m14 +
				m42 * other.m24 +
				m43 * other.m34 +
				m44 * other.m44;

			return result;
		}

		friend inline Matrix operator*(const Matrix& a, const float& b)
		{
			Matrix result;
			result.m11 = a.m11 * b;
			result.m12 = a.m12 * b;
			result.m13 = a.m13 * b;
			result.m14 = a.m14 * b;

			result.m21 = a.m21 * b;
			result.m22 = a.m22 * b;
			result.m23 = a.m23 * b;
			result.m24 = a.m24  * b;

			result.m31 = a.m31 * b;
			result.m32 = a.m32 * b;
			result.m33 = a.m33 * b;
			result.m34 = a.m34 * b;

			result.m41 = a.m41 * b;
			result.m42 = a.m42 * b;
			result.m43 = a.m43 * b;
			result.m44 = a.m44 * b;

			return result;
		}

		friend inline Matrix operator*(const float& b, const Matrix& a)
		{
			Matrix result;
			result.m11 = a.m11 * b;
			result.m12 = a.m12 * b;
			result.m13 = a.m13 * b;
			result.m14 = a.m14 * b;

			result.m21 = a.m21 * b;
			result.m22 = a.m22 * b;
			result.m23 = a.m23 * b;
			result.m24 = a.m24  * b;

			result.m31 = a.m31 * b;
			result.m32 = a.m32 * b;
			result.m33 = a.m33 * b;
			result.m34 = a.m34 * b;

			result.m41 = a.m41 * b;
			result.m42 = a.m42 * b;
			result.m43 = a.m43 * b;
			result.m44 = a.m44 * b;

			return result;
		}


		//Static Functions
		static Matrix Identity()
		{
			Matrix result = Matrix();
			result.m11 = 1.0f;
			result.m22 = 1.0f;
			result.m33 = 1.0f;
			result.m44 = 1.0f;

			return result;
		}
		
		static inline Matrix Multiply(const Matrix& a, const Matrix& b)
		{
			Matrix result;

			//Row 1
			result.m11 = 
				a.m11 * b.m11 + 
				a.m12 * b.m21 + 
				a.m13 * b.m31 + 
				a.m14 * b.m41;

			result.m12 =
				a.m11 * b.m12 +
				a.m12 * b.m22 +
				a.m13 * b.m32 +
				a.m14 * b.m42;

			result.m13 =
				a.m11 * b.m13 +
				a.m12 * b.m23 +
				a.m13 * b.m33 +
				a.m14 * b.m43;

			result.m14 =
				a.m11 * b.m14 +
				a.m12 * b.m24 +
				a.m13 * b.m34 +
				a.m14 * b.m44;

			//Row 2
			result.m21 =
				a.m21 * b.m11 +
				a.m22 * b.m21 +
				a.m23 * b.m31 +
				a.m24 * b.m41;

			result.m22 =
				a.m21 * b.m12 +
				a.m22 * b.m22 +
				a.m23 * b.m32 +
				a.m24 * b.m42;

			result.m23 =
				a.m21 * b.m13 +
				a.m22 * b.m23 +
				a.m23 * b.m33 +
				a.m24 * b.m43;

			result.m24 =
				a.m21 * b.m14 +
				a.m22 * b.m24 +
				a.m23 * b.m34 +
				a.m24 * b.m44;

			//Row 3
			result.m31 =
				a.m31 * b.m11 +
				a.m32 * b.m21 +
				a.m33 * b.m31 +
				a.m34 * b.m41;

			result.m32 =
				a.m31 * b.m12 +
				a.m32 * b.m22 +
				a.m33 * b.m32 +
				a.m34 * b.m42;

			result.m33 =
				a.m31 * b.m13 +
				a.m32 * b.m23 +
				a.m33 * b.m33 +
				a.m34 * b.m43;

			result.m34 =
				a.m31 * b.m14 +
				a.m32 * b.m24 +
				a.m33 * b.m34 +
				a.m34 * b.m44;

			//Row 4
			result.m41 =
				a.m41 * b.m11 +
				a.m42 * b.m21 +
				a.m43 * b.m31 +
				a.m44 * b.m41;

			result.m42 =
				a.m41 * b.m12 +
				a.m42 * b.m22 +
				a.m43 * b.m32 +
				a.m44 * b.m42;

			result.m43 =
				a.m41 * b.m13 +
				a.m42 * b.m23 +
				a.m43 * b.m33 +
				a.m44 * b.m43;

			result.m44 =
				a.m41 * b.m14 +
				a.m42 * b.m24 +
				a.m43 * b.m34 +
				a.m44 * b.m44;

			return result;
		}

		static inline Matrix Multiply(const Matrix& a, const float& b)
		{
			Matrix result;
			result.m11 = a.m11 * b;
			result.m12 = a.m12 * b;
			result.m13 = a.m13 * b;
			result.m14 = a.m14 * b;

			result.m21 = a.m21 * b;
			result.m22 = a.m22 * b;
			result.m23 = a.m23 * b;
			result.m24 = a.m24  * b;

			result.m31 = a.m31 * b;
			result.m32 = a.m32 * b;
			result.m33 = a.m33 * b;
			result.m34 = a.m34 * b;

			result.m41 = a.m41 * b;
			result.m42 = a.m42 * b;
			result.m43 = a.m43 * b;
			result.m44 = a.m44 * b;

			return result;
		}

		static inline Matrix Add(const Matrix& a, const Matrix& b)
		{
			Matrix result;
			result.m11 = a.m11 + b.m11;
			result.m12 = a.m12 + b.m12;
			result.m13 = a.m13 + b.m13;
			result.m14 = a.m14 + b.m14;

			result.m21 = a.m21 + b.m21;
			result.m22 = a.m22 + b.m22;
			result.m23 = a.m23 + b.m23;
			result.m24 = a.m24 + b.m24;

			result.m31 = a.m31 + b.m31;
			result.m32 = a.m32 + b.m32;
			result.m33 = a.m33 + b.m33;
			result.m34 = a.m34 + b.m34;

			result.m41 = a.m41 + b.m41;
			result.m42 = a.m42 + b.m42;
			result.m43 = a.m43 + b.m43;
			result.m44 = a.m44 + b.m44;

			return result;
		}

		static inline Matrix Subtract(const Matrix& a, const Matrix& b)
		{
			Matrix result;
			result.m11 = a.m11 - b.m11;
			result.m12 = a.m12 - b.m12;
			result.m13 = a.m13 - b.m13;
			result.m14 = a.m14 - b.m14;

			result.m21 = a.m21 - b.m21;
			result.m22 = a.m22 - b.m22;
			result.m23 = a.m23 - b.m23;
			result.m24 = a.m24 - b.m24;

			result.m31 = a.m31 - b.m31;
			result.m32 = a.m32 - b.m32;
			result.m33 = a.m33 - b.m33;
			result.m34 = a.m34 - b.m34;

			result.m41 = a.m41 - b.m41;
			result.m42 = a.m42 - b.m42;
			result.m43 = a.m43 - b.m43;
			result.m44 = a.m44 - b.m44;

			return result;
		}


		//Rotations
		//XYZ NOT WORKING
		static inline Matrix RotationXYZ(const float& x, const float& y, const float& z)
		{
			float xcos = (float)cos(x);
			float xsin = (float)sin(x);
			float ycos = (float)cos(y);
			float ysin = (float)sin(y);
			float zcos = (float)cos(z);
			float zsin = (float)sin(z);

			Matrix result;
			result.m11 = zcos * ycos + zsin * xsin * ysin;
			result.m12 = zsin * xcos;
			result.m13 = zcos * -ysin + zsin * xsin * ycos;
			result.m14 = 0.0f;
			result.m21 = -zsin * ycos + zcos * xsin * ysin;
			result.m22 = zcos * xcos;
			result.m23 = zsin * ysin + zcos * xsin * ycos;
			result.m24 = 0.0f;
			result.m31 = xcos * ysin;
			result.m32 = -xsin;
			result.m33 = xcos * ycos;
			result.m34 = 0.0f;
			result.m41 = 0.0f;
			result.m42 = 0.0f;
			result.m43 = 0.0f;
			result.m44 = 1.0f;

			return result;
		}

		static inline Matrix RotationX(const float& x)
		{
			float cosx = (float)cos(x);
			float sinx = (float)sin(x);

			Matrix result;
			result.m11 = 1.0f;
			result.m12 = 0.0f;
			result.m13 = 0.0f;
			result.m14 = 0.0f;
			result.m21 = 0.0f;
			result.m22 = cosx;
			result.m23 = sinx;
			result.m24 = 0.0f;
			result.m31 = 0.0f;
			result.m32 = -sinx;
			result.m33 = cosx;
			result.m34 = 0.0f;
			result.m41 = 0.0f;
			result.m42 = 0.0f;
			result.m43 = 0.0f;
			result.m44 = 1.0f;

			return result;
		}

		static inline Matrix RotationY(const float& y)
		{
			float cosy = (float)cos(y);
			float siny = (float)sin(y);

			Matrix result;
			result.m11 = cosy;
			result.m12 = 0.0f;
			result.m13 = -siny;
			result.m14 = 0.0f;
			result.m21 = 0.0f;
			result.m22 = 1.0f;
			result.m23 = 0.0f;
			result.m24 = 0.0f;
			result.m31 = siny;
			result.m32 = 0;
			result.m33 = cosy;
			result.m34 = 0.0f;
			result.m41 = 0.0f;
			result.m42 = 0.0f;
			result.m43 = 0.0f;
			result.m44 = 1.0f;

			return result;
		}

		static inline Matrix RotationZ(const float& z)
		{
			float cosz = (float)cos(z);
			float sinz = (float)sin(z);

			Matrix result;
			result.m11 = cosz;
			result.m12 = sinz;
			result.m13 = 0.0f;
			result.m14 = 0.0f;
			result.m21 = -sinz;
			result.m22 = cosz;
			result.m23 = 0.0f;
			result.m24 = 0.0f;
			result.m31 = 0.0f;
			result.m32 = 0;
			result.m33 = 1.0f;
			result.m34 = 0.0f;
			result.m41 = 0.0f;
			result.m42 = 0.0f;
			result.m43 = 0.0f;
			result.m44 = 1.0f;

			return result;
		}

		//Untested
		static inline Matrix Translation(const float& x, const float& y, const float& z)
		{
			Matrix result;
			result.m11 = 1.0f;
			result.m22 = 1.0f;
			result.m33 = 1.0f;
			result.m44 = 1.0f;
			result.m14 = x;
			result.m24 = y;
			result.m34 = z;

			return result;
		}

		static Vector3 Transform(const Vector3& vec, const Matrix& mat)
		{
			Vector3 vector;
			float num3 = (((vec.X * mat.m11) + (vec.Y * mat.m21)) + (vec.Z * mat.m31)) + mat.m41;
			float num2 = (((vec.X * mat.m12) + (vec.Y * mat.m22)) + (vec.Z * mat.m32)) + mat.m42;
			float num = (((vec.X * mat.m13) + (vec.Y * mat.m23)) + (vec.Z * mat.m33)) + mat.m43;
			vector.X = num3;
			vector.Y = num2;
			vector.Z = num;
			return vector;


		}

		//View
		static Matrix CreateLookAt(const Vector3& cameraPosition, const Vector3& cameraTarget, const Vector3& cameraUpVector)
		{
			Vector3 zaxis = Vector3::Normalize(cameraTarget - cameraPosition);
			Vector3 xaxis = Vector3::Normalize(Vector3::Cross(cameraUpVector, zaxis));
			Vector3 yaxis = Vector3::Cross(zaxis, xaxis);

			Matrix matrix;
			matrix.m11 = xaxis.X;
			matrix.m21 = yaxis.X;
			matrix.m31 = zaxis.X;
			matrix.m41 = 0.0f;

			matrix.m12 = xaxis.Y;
			matrix.m22 = yaxis.Y;
			matrix.m32 = zaxis.Y;
			matrix.m42 = 0.0f;

			matrix.m13 = xaxis.Z;
			matrix.m23 = yaxis.Z;
			matrix.m33 = zaxis.Z;
			matrix.m43 = 0.0f;

			matrix.m14 = -Vector3::Dot(xaxis, cameraPosition);
			matrix.m24 = -Vector3::Dot(yaxis, cameraPosition);
			matrix.m34 = -Vector3::Dot(zaxis, cameraPosition);
			matrix.m44 = 1.0f;

			return matrix;
		}



		//Projection
		static inline Matrix CreatePerspectiveFieldOfView(const float& fieldOfView, const float& aspectRatio, const float& nearPlaneDistance, const float& farPlaneDistance)
		{
			Matrix matrix;
			float yScale = 1.0f / (float)tan(fieldOfView / 2.0f);
			float xScale = yScale / aspectRatio;

			matrix.m11 = xScale;
			matrix.m22 = yScale;
			matrix.m33 = farPlaneDistance / (farPlaneDistance - nearPlaneDistance);
			matrix.m43 = 1.0f;
			matrix.m34 = -nearPlaneDistance * farPlaneDistance / (farPlaneDistance - nearPlaneDistance);

			return matrix;
		}
};