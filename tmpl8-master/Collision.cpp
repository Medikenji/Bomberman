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
	int aleft, aright, abottom, atop;
	int bleft, bright, bbottom, btop;
	int left, right, bottom, top;
	int columns, rows;

	aleft = (int)_entity1->position.x; aright = aleft + _entity1->GetMaskProportions().x - 1;
	abottom = (int)_entity1->position.y; atop = abottom + _entity1->GetMaskProportions().y - 1;

	bleft = (int)_entity2->position.x; bright = bleft + _entity2->GetMaskProportions().x - 1;
	bbottom = (int)_entity2->position.y; btop = bbottom + _entity2->GetMaskProportions().y - 1;

	if (aleft > bright || aright < bleft || abottom > btop || atop < bbottom)
		return false;

	left = std::max(aleft, bleft);
	right = std::min(aright, bright);
	bottom = std::max(abottom, bbottom);
	top = std::min(atop, btop);
	columns = right - left + 1;
	rows = top - bottom + 1;

	aleft = left - aleft;
	abottom = bottom - abottom;

	bleft = left - bleft;
	bbottom = bottom - bbottom;

	bool* maskA = _entity1->GetMask();
	bool* maskB = _entity2->GetMask();

	for (int y = 0; y < rows; ++y) {
		for (int x = 0; x < columns; ++x) {
			if (maskA[(aleft + x) + (abottom + y) * _entity1->GetMaskProportions().x] &&
				maskB[(bleft + x) + (bbottom + y) * _entity2->GetMaskProportions().x])
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