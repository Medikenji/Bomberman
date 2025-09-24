#include "precomp.h"
#include "BomberMan.h"
#include "World.h"
#include "Collision.h"

int BomberMan::m_nextBomberId = 0;

BomberMan::BomberMan() {
	isLiving = true;
	sprite = new Sprite(new Surface("assets/Bomberman.png"), 19);
	m_animationState = 0;
	m_animationTimer = 0;
	m_animationSwitch = true;
	m_bomberId = m_nextBomberId++;
	position.x = 16;
	position.y = 48;
	// artificial width and height
	scale.x = 16;
	scale.y = 16;
}


void BomberMan::Initialise()
{
	m_currentWorld = static_cast<World*>(GetEntityById(0));
}


void BomberMan::Update(float deltaTime)
{
	m_animationTimer -= deltaTime;
	float v_x = 0, v_y = 0;
	Input(deltaTime, &v_x, &v_y);
	position.x += v_x;
	position.y += v_y;
	TileCollision();
	SetAnimation(v_x, v_y);
	Entity::SetCameraX(m_bomberId, -position.x + RNDRWIDTH / SURFACEAMOUNT / 2 - scale.x / 2);
	DrawToSurfaces(sprite, position.x, position.y);
}


bool BomberMan::TileCollision()
{
	float2 temp = { position.x + scale.x / 2, position.y + scale.y / 2 };
	UINT8* gridPos = m_currentWorld->GetGridPos(temp);
	UINT8 l = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] - 1 , gridPos[1] });
	UINT8 tl = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] - 1, gridPos[1] - 1 });
	UINT8 t = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] , gridPos[1] - 1 });
	UINT8 tr = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] + 1, gridPos[1] - 1 });
	UINT8 r = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] + 1, gridPos[1] });
	UINT8 br = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] + 1, gridPos[1] + 1 });
	UINT8 b = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] , gridPos[1] + 1 });
	UINT8 bl = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] - 1, gridPos[1] + 1 });

	float threshold;
	float4 playerRectangle = { position.x + 1, position.y + 1, scale.x - 1, scale.y - 1 };
	float4 rectangle;
	float2 pixelPosition = m_currentWorld->GetPixelPosFromGrid({ gridPos[0], gridPos[1] });

	// check left
	if (l != Entity::GRASS)
	{
		threshold = pixelPosition.x;
		if (position.x < threshold)
		{
			position.x = threshold;
		}
	};

	// check top
	if (t != Entity::GRASS)
	{
		threshold = pixelPosition.y;
		if (position.y < threshold)
		{
			position.y = threshold;
		}
	};

	// check right
	if (r != Entity::GRASS)
	{
		threshold = pixelPosition.x + World::BLOCKSIZE;
		if (position.x + scale.x > threshold)
		{
			position.x = threshold - scale.x;
		}
	}

	// check bottom
	if (b != Entity::GRASS)
	{
		threshold = pixelPosition.y + World::BLOCKSIZE;
		if (position.y + scale.y > threshold)
		{
			position.y = threshold - scale.y;
		}
	}
	return true;
}


bool BomberMan::SetAnimation(float vx, float vy)
{
	int state = 0;

	if (vx == 0 && vy == 0)
		return true;

	if (vx > 0)
		state = 0;
	if (vx < 0)
		state = 1;
	if (vy > 0)
		state = 2;
	if (vy < 0)
		state = 3;

	switch (state)
	{
	case 0:
		this->Animate(6);
		break;
	case 1:
		this->Animate(0);
		break;
	case 2:
		this->Animate(9);
		break;
	case 3:
		this->Animate(3);
		break;
	}

	return true;
};


bool BomberMan::Animate(int startFrame)
{
	this->sprite->SetFrame(startFrame + m_animationState);
	if (m_animationTimer > 0)
	{
		return true;
	}

	this->m_animationTimer = 0.05;

	if (this->m_animationSwitch)
	{
		this->m_animationState++;
	}
	else
	{
		this->m_animationState--;
	}

	if (this->m_animationState < 1 || this->m_animationState > 1)
	{
		this->m_animationSwitch = !this->m_animationSwitch;
	}

	return true;
}


bool BomberMan::Input(float deltaTime, float* vx, float* vy)
{
	if (m_bomberId == 0)
	{
		if (GetAsyncKeyState(GLFW_KEY_Z)) m_currentWorld->PlaceBomb(position+(scale.x/2));
		if (GetAsyncKeyState(VK_UP)) *vy += -45 * deltaTime;
		if (GetAsyncKeyState(VK_DOWN)) *vy += 45 * deltaTime;
		if (GetAsyncKeyState(VK_LEFT)) *vx += -45 * deltaTime;
		if (GetAsyncKeyState(VK_RIGHT)) *vx += 45 * deltaTime;
	}
	if (m_bomberId == 1)
	{
		if (GetAsyncKeyState(GLFW_KEY_W)) *vy += -45 * deltaTime;
		if (GetAsyncKeyState(GLFW_KEY_S)) *vy += 45 * deltaTime;
		if (GetAsyncKeyState(GLFW_KEY_A)) *vx += -45 * deltaTime;
		if (GetAsyncKeyState(GLFW_KEY_D)) *vx += 45 * deltaTime;
	}
	return true;
}