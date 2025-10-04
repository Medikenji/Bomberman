#pragma once

class Entity;

class Collision
{
public:
	// Functions
	static bool RecToRec(float4 _rec1, float4 _rec2);
	static bool PointToRec(float2 _point, float4 _rec);
};

