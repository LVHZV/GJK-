#include "base.hpp"

Hit GJK(const std::vector<Vector2D>& convex1, const Vector2D origin1, const std::vector<Vector2D>& convex2, const Vector2D origin2)
{
	Hit hit;
	hit.is_collision=false;
	Vector2D direct =Math::Normalize(origin1 - origin2);
	Triangle semple;
	semple.point[0]=support(convex1, convex2, direct);
	if (semple.point[0].dot(direct) < 0)
		return hit;
	semple.point[1] =support(convex1, convex2, -direct);
	if (semple.point[1].dot(-direct) < 0)
		return hit;
	direct = GetFaceOriginVector(semple.point[1], semple.point[0]);
	Vector2D minkowski_d = support(convex1, convex2, direct);
	if (minkowski_d.dot(direct) < 0)
		return hit;
	semple.point[2] = minkowski_d;

	for (;;)
	{
		if (OriginInTriangle(semple))
			return EPA(semple,convex1,convex2);

		direct = GetFaceOriginVector(semple.point[1], semple.point[2]);
		Vector2D minkowski_d = support(convex1, convex2, direct);
		if (minkowski_d.dot(direct) < 0)
			return hit;
		if (minkowski_d == semple.point[1]|| minkowski_d == semple.point[2])
			return hit;
		semple.point[0] = semple.point[1];
		semple.point[1] = semple.point[2];
		semple.point[2] = minkowski_d;
			
	}
}

Vector2D support(const std::vector<Vector2D>& convex1, const std::vector<Vector2D>& convex2, const Vector2D& direct)
{
	Vector2D A, B;
	A = convex1[0];
	float distance = direct.dot(convex1[0]);
	for (std::size_t i = 1; i < convex1.size(); i++)
	{
		float t = direct.dot(convex1[i]);
		if (t > distance)
		{
			distance = t;
			A = convex1[i];
		}
	}

	Vector2D n_direct = -direct;
	B = convex2[0];
	distance = n_direct.dot(convex2[0]);
	for (std::size_t i = 1; i < convex2.size(); i++)
	{
		float t = n_direct.dot(convex2[i]);
		if (t > distance)
		{
			distance = t;
			B = convex2[i];
		}
	}
	return A - B;
}

//检测三角形是否包含原点
bool OriginInTriangle(const Triangle& semple)
{
	Vector2D AB = semple.point[1] - semple.point[2];
	Vector2D AC = semple.point[0] - semple.point[2];
	Vector2D AO = -semple.point[2];
	Vector2D nor =Math::Normalize(Math::TripleCorss(AB,AC,AC));
	if (nor.dot(AO) >= 0)
		return false;
	nor = Math::Normalize(Math::TripleCorss(AC, AB, AB));
	if (nor.dot(AO) >= 0)
		return false;
	return true;
}

//获得线段面向原点的向量
Vector2D GetFaceOriginVector(const Vector2D& a, const Vector2D& b)
{
	Vector2D delta = a - b;
	Vector2D nor = Math::Normalize(Vector2D(delta.Y, -delta.X));
	if (nor.dot(a) < 0)
		return nor;
	return -nor;
}


