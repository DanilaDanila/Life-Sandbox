#ifndef PHYSICSBOX_HPP
#define PHYSICSBOX_HPP

#define pi 3.1415

#include <vector>


	int det2i(int a11, int a12, int a21, int a22);

	float det2f(float a11, float a12, float a21, float a22);

	int det3i(int a11, int a12, int a13, int a21, int a22, int a23, int a31, int a32, int a33);

	float det3f(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33);

	class vec2
	{
	public:
		float x;
		float y;

		vec2();

		vec2(float x, float y);

		float module();

		vec2 operator+(vec2);

		vec2 operator-(vec2);

		vec2 operator*(float);

		vec2 operator/(float);

		float operator*(vec2); // Модуль(со знаком) векторного произведение

		~vec2();
	};

	float distance(vec2, vec2);

	class line_segment
	{
	private:
		vec2 p0;
		vec2 p1;

		float A,B,C;

		void countABC();

	public:
		line_segment();

		line_segment(vec2, vec2);

		float getA();

		float getB();

		float getC();

		void setFirstPoint(vec2);

		void setSecondPoint(vec2);

		vec2 getFirstPoint();

		vec2 getSecondPoint();

		vec2 getMiddle();

		float getLength();

		vec2 getNormalFromPoint(vec2);

		vec2 getIntersectionWithLine(line_segment);

		float getDistanceFromPoint(vec2);

		bool intersects(line_segment);

		bool isPointOn(vec2);

		bool isPointsOnSameSide(vec2,vec2);

		~line_segment();
	};

	class polygon
	{
	private:

		int vertexes_count;
		vec2 *vertexes;

		vec2 position;
		vec2 origin;

		float rotation;
	public:
		polygon();

		line_segment *getLines();

		void setVertexCount(int);

		int getVertexCount();

		void setVertex(int vertex_num, vec2 coordinates);

		vec2 getVertex(int vertex_num);

		vec2 getVertexPosition(int vertex_num);

		void setOrigin(vec2);

		void setOriginToCenter();

		vec2 getOrigin();

		vec2 getCenter();

		void setRotation(float);

		float getRotation();

		void setPosition(vec2);

		vec2 getPosition();

		bool isPointInside(vec2);

		bool intersects(polygon);

		~polygon();
	};

#endif