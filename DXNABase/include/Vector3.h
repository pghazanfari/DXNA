#include <DirectXMath.h>

#pragma once

struct Vector3
{
private:
	static Vector3 _up;

public:
	float X, Y, Z;

	inline Vector3() : X(0.0f), Y(0.0f), Z(0.0f)
	{}

	inline Vector3(float x, float y, float z) : X(x), Y(y), Z(z)
	{}


	//Operators
	inline bool operator ==(const Vector3& v) const
	{
		return X == v.X && Y == v.Y && Z == v.Z;
	}

	inline Vector3 operator + (const Vector3& V) const
	{
		return Vector3(X + V.X, Y + V.Y, Z + V.Z);
	}

	friend inline Vector3 operator - (const Vector3& a, const Vector3& b)
	{
		return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
	}

	inline Vector3 operator *(const float& f)
	{
		return Vector3(X * f, Y * f, Z * f);
	}

	inline Vector3 operator /(const float& f)
	{
		return Vector3(X / f, Y / f, Z / f);
	}


	//Member Functions
	inline float length() const
	{
		return (float)sqrt( (X * X) + (Y * Y) + (Z * Z));
	}

	inline float lengthSquared() const
	{
		return X * X + Y * Y + Z * Z;
	}

	inline void normalize()
	{
		float l = length();
		X /= l;
		Y /= l;
		Z /= l;
	}


	//Static Functions
	static inline Vector3 Up() { return _up; }

	static inline float Dot(const Vector3& v1, const Vector3& v2)
	{
		return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
	}

	static inline Vector3 Cross(const Vector3& vector1, const Vector3& vector2)
	{
		Vector3 vector;
		vector.X = (vector1.Y * vector2.Z) - (vector1.Z * vector2.Y);
		vector.Y = (vector1.Z * vector2.X) - (vector1.X * vector2.Z);
		vector.Z = (vector1.X * vector2.Y) - (vector1.Y * vector2.X);
		return vector;
	}

	static inline Vector3 Normalize(const Vector3& v1)
	{
		Vector3 result;
		float l = v1.length();
		result.X = v1.X / l;
		result.Y = v1.Y / l;
		result.Z = v1.Z / l;
		return result;
	}
};