#pragma once
#include "vector.h"

class fvector2d
{
public:
	float x;
	float y;

	inline bool is_Zero() {
		return (x == 0) && (y == 0);
	}
};

class fvector
{
public:
	fvector() : x(0.f), y(0.f), z(0.f)
	{

	}

	fvector(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{

	}
	~fvector()
	{

	}

	float x;
	float y;
	float z;

	inline float Dot(fvector v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(fvector v)
	{
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}
	float length(void) {
		auto sqr = [](float n) {
			return static_cast<float>(n * n);
			};

		return sqrt(sqr(x) + sqr(y) + sqr(z));
	}

	float distance_to(const fvector& other) {
		fvector delta;
		delta.x = x - other.x;
		delta.y = y - other.y;
		delta.z = z - other.z;

		return delta.length();
	}
	inline float Length()
	{
		return sqrt(x * x + y * y + z * z);
	}

	fvector operator+(fvector v)
	{
		return fvector(x + v.x, y + v.y, z + v.z);
	}

	fvector operator-(fvector v)
	{
		return fvector(x - v.x, y - v.y, z - v.z);
	}

	fvector operator*(float number) const
	{
		return fvector(x * number, y * number, z * number);
	}
};

struct fplane : fvector
{
	float W = 0;


	fvector ToVector3()
	{
		fvector value;
		value.x = this->x;
		value.y = this->y;
		value.z = this->y;

		return value;
	}
};

struct fquat
{
	float x;
	float y;
	float z;
	float w;
};

struct fmatrix
{
	fplane XPlane;
	fplane YPlane;
	fplane ZPlane;
	fplane WPlane;
};

struct ftransform
{
	fplane  rot;
	fvector translation;
	char    pad[8];
	fvector scale;

	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.W * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.W * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.W * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}

D3DMATRIX Matrix(fvector rot, fvector origin = fvector(0, 0, 0))
{
	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

class frotator
{
public:
	frotator() : Pitch(0.f), Yaw(0.f), Roll(0.f)
	{

	}

	frotator(float _Pitch, float _Yaw, float _Roll) : Pitch(_Pitch), Yaw(_Yaw), Roll(_Roll)
	{

	}
	~frotator()
	{

	}

	float Pitch;
	float Yaw;
	float Roll;
	inline frotator get() {
		return frotator(Pitch, Yaw, Roll);
	}
	inline void set(float _Pitch, float _Yaw, float _Roll) {
		Pitch = _Pitch;
		Yaw = _Yaw;
		Roll = _Roll;
	}

	inline frotator Clamp() {
		frotator result = get();
		if (result.Pitch > 180)
			result.Pitch -= 360;
		else if (result.Pitch < -180)
			result.Pitch += 360;
		if (result.Yaw > 180)
			result.Yaw -= 360;
		else if (result.Yaw < -180)
			result.Yaw += 360;
		if (result.Pitch < -89)
			result.Pitch = -89;
		if (result.Pitch > 89)
			result.Pitch = 89;
		while (result.Yaw < -180.0f)
			result.Yaw += 360.0f;
		while (result.Yaw > 180.0f)
			result.Yaw -= 360.0f;

		result.Roll = 0;
		return result;

	}
	float Length() {
		return sqrt(Pitch * Pitch + Yaw * Yaw + Roll * Roll);
	}

	frotator operator+(frotator angB) { return frotator(Pitch + angB.Pitch, Yaw + angB.Yaw, Roll + angB.Roll); }
	frotator operator-(frotator angB) { return frotator(Pitch - angB.Pitch, Yaw - angB.Yaw, Roll - angB.Roll); }
	frotator operator/(float flNum) { return frotator(Pitch / flNum, Yaw / flNum, Roll / flNum); }
	frotator operator*(float flNum) { return frotator(Pitch * flNum, Yaw * flNum, Roll * flNum); }
	bool operator==(frotator angB) { return Pitch == angB.Pitch && Yaw == angB.Yaw && Yaw == angB.Yaw; }
	bool operator!=(frotator angB) { return Pitch != angB.Pitch || Yaw != angB.Yaw || Yaw != angB.Yaw; }

};

float __fastcall Atan2(float a1, float a2)
{
	float result;

	result = 0.0;
	if (a2 != 0.0 || a1 != 0.0)
		return atan2(a1, a2);
	return result;
}
float __fastcall FMod(float a1, float a2)
{
	if (fabs(a2) > 0.00000001)
		return fmod(a1, a2);
	else
		return 0.0;
}

float ClampAxis(float Angle)
{
	Angle = FMod(Angle, (float)360.0);

	if (Angle < (float)0.0)
	{
		Angle += (float)360.0;
	}

	return Angle;
}

float NormalizeAxis(float Angle)
{
	Angle = ClampAxis(Angle);

	if (Angle > (float)180.0)
	{
		Angle -= (float)360.0;
	}

	return Angle;
}

frotator rotator(fquat* F)
{
	const float SingularityTest = F->z * F->x - F->w * F->y;
	const float YawY = 2.f * (F->w * F->z + F->x * F->y);
	const float YawX = (1.f - 2.f * ((F->y * F->y) + (F->z * F->z)));

	const float SINGULARITY_THRESHOLD = 0.4999995f;
	const float RAD_TO_DEG = 57.295776;
	float Pitch, Yaw, Roll;

	if (SingularityTest < -SINGULARITY_THRESHOLD)
	{
		Pitch = -90.f;
		Yaw = (Atan2(YawY, YawX) * RAD_TO_DEG);
		Roll = NormalizeAxis(-Yaw - (2.f * Atan2(F->x, F->w) * RAD_TO_DEG));
	}
	else if (SingularityTest > SINGULARITY_THRESHOLD)
	{
		Pitch = 90.f;
		Yaw = (Atan2(YawY, YawX) * RAD_TO_DEG);
		Roll = NormalizeAxis(Yaw - (2.f * Atan2(F->x, F->w) * RAD_TO_DEG));
	}
	else
	{
		Pitch = (asin(2.f * SingularityTest) * RAD_TO_DEG);
		Yaw = (Atan2(YawY, YawX) * RAD_TO_DEG);
		Roll = (Atan2(-2.f * (F->w * F->x + F->y * F->z), (1.f - 2.f * ((F->x * F->x) + (F->y * F->y)))) * RAD_TO_DEG);
	}

	frotator RotatorFromQuat = frotator{ Pitch, Yaw, Roll };
	return RotatorFromQuat;
}