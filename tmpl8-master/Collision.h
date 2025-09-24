#pragma once

class Entity;

class Collision
{
public:
	// Functions
	static bool RecToRec(float4 rec1, float4 rec2);
	static bool PointToRec(float2 point, float4 rec);
};

