#pragma once

#include <vector>
struct Vector2D
{
	float X;
	float Y;
	Vector2D(const float& x, const float& y)
	{
		X = x;
		Y = y;
	}
	Vector2D()
	{
		X = 0.f;
		Y = 0.f;
	}
	Vector2D operator+(const Vector2D& v)const;
	Vector2D operator-(const Vector2D& v)const;
	Vector2D operator*(const float& n)const;
	Vector2D operator/(const float& n)const;
	Vector2D operator-() const;
	bool operator== (const Vector2D& other)const;
	double dot(const Vector2D& other) const;
	Vector2D Vector2D::GetNormal()const;
};

struct Triangle
{
	Vector2D point[3];
};

namespace Math
{
    float FastSquare(float number) //快速开方
	{
		long i;
		float x, y;
		const float f = 1.5F;

		x = number * 0.5F;
		y = number;
		i = *(long*)&y;
		i = 0x5f3759df - (i >> 1);
		y = *(float*)&i;
		y = y * (f - (x * y * y));
		y = y * (f - (x * y * y));
		return number * y;
	}

    float GetLength(const Vector2D& a)
	{
		return FastSquare(a.X * a.X + a.Y * a.Y);
	}

    Vector2D TripleCorss(const Vector2D& a, const Vector2D& b, const Vector2D& c)
	{
		Vector2D r;
		float ac = a.X * c.X + a.Y * c.Y;
		float bc = b.X * c.X + b.Y * c.Y;

		r.X = b.X * ac - a.X * bc;
		r.Y = b.Y * ac - a.Y * bc;
		return r;
	}
    Vector2D Normalize(const Vector2D& vec)
	{
		float length = GetLength(vec);
		return vec / length;
	}
}


struct Hit//用于返回碰撞结果
{
	bool is_collision;
	Vector2D direct;
	float depth;
};

Hit GJK(const std::vector<Vector2D>& convex1, const Vector2D origin1, const std::vector<Vector2D>& convex2, const Vector2D origin2);
Hit EPA(Triangle& semple, const std::vector<Vector2D>& object1, const std::vector<Vector2D>& object2);

Vector2D support(const std::vector<Vector2D>& convex1, const std::vector<Vector2D>& convex2, const Vector2D& direct);