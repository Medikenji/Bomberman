#include "precomp.h"
#include "Collision.h"
#include "Entity.h"

// Made with help from https://www.jeffreythompson.org/collision-detection/table_of_contents.php

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
		return 1;
	}
	return 0;
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
		return 1;
	}
	return 0;
}

// Source: https://www.youtube.com/watch?v=9pnEBa4cy5w, pretty much copy pasted it, the extracting and loading in the mask is my own work
bool Collision::PixelPerfectCollision(Entity* _entity1, Entity* _entity2)
{
	Entity* entityA = _entity1;
	Entity* entityB = _entity2;
	bool* maskA = nullptr;
	bool* maskB = nullptr;
	int aLeft, aRight, aBottom, aTop;
	int bLeft, bRight, bBottom, bTop;
	int left, right, bottom, top;
	int columns, rows;

	aLeft = (int)entityA->position.x; aRight = (int)entityA->position.x + entityA->GetMaskProportions().x - 1;
	aTop = (int)entityA->position.y; aBottom = (int)entityA->position.y + entityA->GetMaskProportions().y - 1;

	bLeft = (int)entityB->position.x; bRight = (int)entityB->position.x + entityB->GetMaskProportions().x - 1;
	bTop = (int)entityB->position.y; bBottom = (int)entityB->position.y + entityB->GetMaskProportions().y - 1;

	if (aLeft > bRight || aRight < bLeft || aBottom < bTop || aTop > bBottom)
		return false;

	maskA = entityA->GetMask();
	maskB = entityB->GetMask();

	left = std::max(aLeft, bLeft);
	right = std::min(aRight, bRight);
	top = std::max(aTop, bTop);
	bottom = std::min(aBottom, bBottom);
	columns = right - left + 1;
	rows = bottom - top + 1;

	aLeft = left - aLeft;
	aBottom = bottom - aBottom;

	bLeft = left - bLeft;
	bBottom = bottom - bBottom;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (maskA[(aLeft + j) + (aBottom + i) * entityA->GetMaskProportions().x] && maskB[(bLeft + j) + (bBottom + i) * entityB->GetMaskProportions().x])
			{
				delete[] maskA;
				delete[] maskB;
				return true;
			}
		}
	}
	delete[] maskA;
	delete[] maskB;
	return false;
}