#include "precomp.h"
#include "Collision.h"
#include "Entity.h"

bool Collision::RecToRec(float4 rec1, float4 rec2)
{
	float r1x = rec1.x;
	float r1w = rec1.w;
	float r1y = rec1.y;
	float r1h = rec1.z;
	float r2x = rec2.x;
	float r2w = rec2.w;
	float r2y = rec2.y;
	float r2h = rec2.z;
	if (r1x + r1w >= r2x &&
		r1x <= r2x + r2w &&
		r1y + r1h >= r2y &&
		r1y <= r2y + r2h) {
		return true;
	}
	return false;
}

bool Collision::PointToRec(float2 point, float4 rec)
{
	float px = point.x;
	float py = point.y;
	float rx = rec.x;
	float rw = rec.w;
	float ry = rec.y;
	float rh = rec.z;
	if (px >= rx &&
		px <= rx + rw &&
		py >= ry &&
		py <= ry + rh) {
		return true;
	}
	return false;
}