#include "precomp.h"
#include "Collision.h"
#include "Entity.h"


bool Collision::RecToRec(float4 _rec1, float4 _rec2)
{
	float r1x = _rec1.x;
	float r1w = _rec1.w;
	float r1y = _rec1.y;
	float r1h = _rec1.z;
	float r2x = _rec2.x;
	float r2w = _rec2.w;
	float r2y = _rec2.y;
	float r2h = _rec2.z;
	if (r1x + r1w >= r2x &&
		r1x <= r2x + r2w &&
		r1y + r1h >= r2y &&
		r1y <= r2y + r2h) {
		return true;
	}
	return false;
}

bool Collision::PointToRec(float2 _point, float4 _rec)
{
	float px = _point.x;
	float py = _point.y;
	float rx = _rec.x;
	float rw = _rec.w;
	float ry = _rec.y;
	float rh = _rec.z;
	if (px >= rx &&
		px <= rx + rw &&
		py >= ry &&
		py <= ry + rh) {
		return true;
	}
	return false;
}