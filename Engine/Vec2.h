#pragma once

#include <cmath>

template<typename T>
class Vec2_
{
public:
	Vec2_() = default;
	Vec2_(T x_in, T y_in)
		:
		x(x_in),
		y(y_in)
	{
	}
	Vec2_& operator=(const Vec2_& rhs)
	{
		x = rhs.x;
		y = rhs.y;

		return *this;
	}
	Vec2_ operator+(const Vec2_& rhs) const
	{
		return Vec2_(x + rhs.x, y + rhs.y);
	}
	Vec2_& operator+=(const Vec2_& rhs)
	{
		return *this = *this + rhs;
	}
	Vec2_ operator*(T rhs) const
	{
		return Vec2_(x * rhs, y * rhs);
	}
	Vec2_& operator*=(T rhs)
	{
		return *this = *this * rhs;
	}
	Vec2_ operator/(T rhs) const
	{
		return Vec2_(x / rhs, y / rhs);
	}
	Vec2_& operator/=(T rhs)
	{
		return *this = *this / rhs;
	}
	Vec2_ operator-(const Vec2_& rhs) const
	{
		return Vec2_(x - rhs.x, y - rhs.y);
	}
	Vec2_& operator-=(const Vec2_& rhs)
	{
		return *this = *this - rhs;
	}
	T GetLength() const
	{
		return T(std::sqrt(GetLengthSq()));
	}
	T GetLengthSq() const
	{
		return x * x + y * y;
	}
	Vec2_ GetNormalized() const
	{
		const T len = GetLength();
		if (len != T(0))
		{
			return *this * (T(1) / len);
		}
		return *this;
	}
	float GetAngle(const float absRelative) const
	{
		//RelativeToWhat must be an absolute angle ( between 0 and 2PI )
		//It will be between 0 and PI and never negative
		const float a = GetAngle() + (absRelative > 3.1415926f ? 6.2831853f - absRelative : -absRelative);
		return a > 3.1415926f ? a - 6.2831853f : a;
	}
	float GetAngle() const
	{
		//It will be between 0 and 2PI
		return y < 0 ? 6.2831853f + atan2(y, x) : atan2(y, x);
	}
	static float GetAngleBetween(const Vec2_& a, const Vec2_& b)
	{
		//It will be between 0 and PI and never negative
		return acos(DotProduct(a, b) / (a.GetLength() * b.GetLength()));
	}
	Vec2_ GetRotated(float dTheta) const
	{
		const float c = cos(dTheta);
		const float s = sin(dTheta);
		return Vec2_(x * c - y * s, x * s + y * c);
	}
	static float Dot(const Vec2_& a, const Vec2_& b)
	{
		return float(a.x * b.x + a.y * b.y);
	}
	Vec2_ GetNormal() const
	{
		return { -y, x };
	}
public:
	T x;
	T y;
};

typedef Vec2_<float> Vec2;
typedef Vec2_<int> Vei2;