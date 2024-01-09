#include "base.hpp"

Vector2D Vector2D::operator + (const Vector2D & v)const
{
	return { X + v.X,Y + v.Y };
}
Vector2D Vector2D::operator - (const Vector2D & v)const
{
	return { X - v.X,Y - v.Y };
}
Vector2D Vector2D::operator* (const float& n)const
{
	return { X * n,Y * n };
}
Vector2D Vector2D::operator / (const float& n)const
{
	return { X / n,Y / n };
}
Vector2D Vector2D::operator - () const
{
	return{ -X,-Y };
}
bool Vector2D::operator== (const Vector2D& other)const
{
	return (X == other.X) && (Y == other.Y);
}
double Vector2D::dot(const Vector2D& other) const {
	return (double)X * other.X + (double)Y * other.Y;
}
Vector2D Vector2D::GetNormal()const
{
	return { Y,-X };
}