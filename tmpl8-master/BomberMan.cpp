#include "precomp.h"
#include "BomberMan.h"

BomberMan::BomberMan() {
	sprite = new Sprite(new Surface("assets/Bomberman.png"), 19);
	m_animationState = 0;
	m_animationTimer = 0;
	m_animationSwitch = true;
	position.x = 16;
	position.y = 48;
}

void BomberMan::Update(float deltaTime)
{
	this->m_animationTimer -= deltaTime;
	float v_x = 0, v_y = 0;
	if (GetAsyncKeyState(VK_UP)) v_y += -45 * deltaTime;
	if (GetAsyncKeyState(VK_DOWN)) v_y += 45 * deltaTime;
	if (GetAsyncKeyState(VK_LEFT)) v_x += -45 * deltaTime;
	if (GetAsyncKeyState(VK_RIGHT)) v_x += 45 * deltaTime;
	position.x += v_x;
	position.y += v_y;
	this->SetAnimation(v_x, v_y);
	DrawToSurfaces(sprite, position.x, position.y);
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
		this->m_animationSwitch =! this->m_animationSwitch;
	}

	return true;
}