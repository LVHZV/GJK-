#include "base.hpp"
#include "cmath"

Vector2D GetUnFaceOriginVector(const Vector2D& a, const Vector2D& b)//获得线段背离原点的向量
{
	Vector2D delta = a - b;
	Vector2D nor =(Vector2D(delta.Y, -delta.X));
	if (nor.dot(a) < 0)
		return -nor;
	return nor;
}

struct Line
{
	Vector2D a;
	Vector2D b;
	float distance;
};

Hit EPA(Triangle& semple, const std::vector<Vector2D>& object1, const std::vector<Vector2D>& object2)
{
	Hit hit;
	hit.is_collision = true;

	std::vector<Line> line_set{ 
	{semple.point[0],semple.point[1],0.0},
	{semple.point[1],semple.point[2],0.0},
	{semple.point[2],semple.point[0],0.0} };

	for (int i = 0; i < 3;i++)
	{
		Vector2D dir = semple.point[i] - semple.point[(i+1)%3];
		line_set[i].distance = std::abs(Math::Normalize(dir.GetNormal()).dot(semple.point[i]));
	}

	for (;;)
	{
		int index = 0;
		for (int i = 1; i < line_set.size(); i++)
		{
			if (line_set[index].distance > line_set[i].distance)
			{
				Vector2D dir = Math::Normalize(line_set[i].b - line_set[i].a);
				if(dir.dot(line_set[i].a)* dir.dot(line_set[i].b)<=0)
				index = i;
			}
			
		}
		Vector2D sch_dir = Math::Normalize(GetUnFaceOriginVector(line_set[index].a, line_set[index].b));
		Vector2D minkowski_d = support(object1, object2, sch_dir);
		if (minkowski_d == line_set[index].a || minkowski_d == line_set[index].b)
		{
			hit.depth = line_set[index].distance;
			hit.direct = sch_dir;
			return hit;
		}

		line_set.push_back({ line_set[index].b,minkowski_d,0 });
		line_set[index].b = minkowski_d;

		Vector2D dir = line_set[index].a - line_set[index].b;
		line_set[index].distance = std::abs(Math::Normalize(dir.GetNormal()).dot(line_set[index].a));

		dir = line_set[line_set.size() - 1].a - line_set[index].b;
		line_set[line_set.size() - 1].distance = std::abs(Math::Normalize(dir.GetNormal()).dot(line_set[line_set.size() - 1].a));
	}
}