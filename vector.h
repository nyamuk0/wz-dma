#pragma once
#include <d3d9.h>
#include <math.h>

#define M_PI 3.14159265358979323846264338327950288419716939937510

class Vector2
{
public:
	float x;
	float y;

	inline bool is_Zero() {
		return (x == 0) && (y == 0);
	}
};


struct FRotator
{
public:
	float Pitch;
	float Yaw;
	float Roll;
};



class Vector3
{
public:
	Vector3() : x(0.f), y(0.f), z(0.f)
	{

	}

	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{

	}
	~Vector3()
	{

	}

	float x;
	float y;
	float z;

	inline float Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3 v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	inline float Length()
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vector3 operator+(Vector3 v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3 v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 operator*(float number) const
	{
		return Vector3(x * number, y * number, z * number);
	}
};

struct FPlane : Vector3
{
	float W = 0;


	Vector3 ToVector3()
	{
		Vector3 value;
		value.x = this->x;
		value.y = this->y;
		value.z = this->y;

		return value;
	}
};

struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};

struct FMatrix
{
	FPlane XPlane;
	FPlane YPlane;
	FPlane ZPlane;
	FPlane WPlane;
};

