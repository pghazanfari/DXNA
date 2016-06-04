#include <math.h>

#pragma once

struct Vector2
{
public:
	float X, Y;

	inline Vector2() : X(0.0f), Y(0.0f)
	{}

	inline Vector2(float x, float y) : X(x), Y(y)
	{}

	inline bool operator == (const Vector2& v) const
	{
		return X == v.X && Y == v.Y;
	}

	inline Vector2 operator + (const Vector2& V) const
	{
		return Vector2(X + V.X, Y + V.Y);
	}

	inline Vector2 operator - (const Vector2& V) const
	{
		return Vector2(X - V.X, Y - V.Y);
	}

	inline Vector2 operator *(const float& f)
	{
		return Vector2(X * f, Y * f);
	}

	inline Vector2 operator /(const float& f)
	{
		return Vector2(X / f, Y / f);
	}

	inline float Length()
	{
		return sqrtf(X * X + Y * Y);
	}

	inline float LengthSquared()
	{
		return X * X + Y * Y;
	}

	inline float Dot(const Vector2& V) const
	{
		return X * V.X + Y * V.Y;
	}
};