#include "precomp.h"
#include "BomberMan.h"
#include "World.h"
#include "Collision.h"
#include "SceneManager.h"

BomberMan::BomberMan(int _bomberId) {
	m_bomberId = _bomberId;
	isLiving = true;
	sprite = new Sprite(new Surface("assets/Bomberman.png"), 19);
	m_animationState = 0;
	m_animationTimer = 0;
	m_animationSwitch = true;
	position.x = 16;
	position.y = 48;
	// artificial width and height
	scale.x = 16;
	scale.y = 16;
}


void BomberMan::Initialize()
{
	m_currentWorld = static_cast<World*>(container->GetEntityById(0));
}


void BomberMan::Update(float _deltaTime)
{
	m_animationTimer -= _deltaTime;
	float v_x = 0, v_y = 0;
	Input(_deltaTime, &v_x, &v_y);
	position.x += v_x;
	position.y += v_y;
	TileCollision();
	SetAnimation(v_x, v_y);
	container->SetCameraX(m_bomberId, (int)( - position.x + RNDRWIDTH / EntityContainer::GetSurfaceAmount() / 2 - scale.x / 2));
	container->DrawToSurfaces(sprite, position);
}


void BomberMan::SetPlayers(BomberMan** _players, int _playerAmount)
{
	if (m_players != nullptr) {
		return;
	}
	m_playerAmount = _playerAmount;
	m_players = _players; 
}

bool BomberMan::TileCollision()
{
	float2 temp = { position.x + scale.x / 2, position.y + scale.y / 2 };
	uint2 intGridPos = m_currentWorld->GetGridPos(temp);
	UINT8 gridPos[2] = {(UINT8)intGridPos.x, (UINT8)intGridPos.y};
	UINT8 l = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] - 1 , gridPos[1] });
	//UINT8 tl = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] - 1, gridPos[1] - 1 });
	UINT8 t = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] , gridPos[1] - 1 });
	//UINT8 tr = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] + 1, gridPos[1] - 1 });
	UINT8 r = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] + 1, gridPos[1] });
	//UINT8 br = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] + 1, gridPos[1] + 1 });
	UINT8 b = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] , gridPos[1] + 1 });
	//UINT8 bl = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] - 1, gridPos[1] + 1 });

	float threshold;
	float4 playerRectangle = { position.x + 1, position.y + 1, scale.x - 1, scale.y - 1 };
	float2 pixelPosition = m_currentWorld->GetPixelPosFromGrid({ gridPos[0], gridPos[1] });

	// check left
	if (l != World::Block::GRASS)
	{
		threshold = pixelPosition.x;
		if (position.x < threshold)
		{
			position.x = threshold;
		}
	};

	// check top
	if (t != World::Block::GRASS)
	{
		threshold = pixelPosition.y;
		if (position.y < threshold)
		{
			position.y = threshold;
		}
	};

	// check right
	if (r != World::Block::GRASS)
	{
		threshold = pixelPosition.x + World::BLOCKSIZE;
		if (position.x + scale.x > threshold)
		{
			position.x = threshold - scale.x;
		}
	}

	// check bottom
	if (b != World::Block::GRASS)
	{
		threshold = pixelPosition.y + World::BLOCKSIZE;
		if (position.y + scale.y > threshold)
		{
			position.y = threshold - scale.y;
		}
	}
	return true;
}


bool BomberMan::SetAnimation(float _velocityX, float _velocityY)
{
	int state = 0;

	if (_velocityX == 0 && _velocityY == 0)
		return true;

	if (_velocityX > 0)
		state = 0;
	if (_velocityX < 0)
		state = 1;
	if (_velocityY > 0)
		state = 2;
	if (_velocityY < 0)
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


bool BomberMan::Animate(int _startFrame)
{
	this->sprite->SetFrame(_startFrame + m_animationState);
	if (m_animationTimer > 0)
	{
		return true;
	}

	this->m_animationTimer = 0.05f;

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


bool BomberMan::Input(float deltaTime, float* _velocityX, float* _velocityY)
{
	if (m_bomberId == 0)
	{
		if (GetAsyncKeyState(GLFW_KEY_Z)) m_currentWorld->PlaceBomb(position+(scale.x/2));
		if (GetAsyncKeyState(VK_UP)) *_velocityY += -45 * deltaTime;
		if (GetAsyncKeyState(VK_DOWN)) *_velocityY += 45 * deltaTime;
		if (GetAsyncKeyState(VK_LEFT)) *_velocityX += -45 * deltaTime;
		if (GetAsyncKeyState(VK_RIGHT)) *_velocityX += 45 * deltaTime;
	}
	if (m_bomberId == 1)
	{
		if (GetAsyncKeyState(GLFW_KEY_W)) *_velocityY += -45 * deltaTime;
		if (GetAsyncKeyState(GLFW_KEY_S)) *_velocityY += 45 * deltaTime;
		if (GetAsyncKeyState(GLFW_KEY_A)) *_velocityX += -45 * deltaTime;
		if (GetAsyncKeyState(GLFW_KEY_D)) *_velocityX += 45 * deltaTime;
	}
	return true;
}

void BomberMan::Die()
{
	container->GetSceneManager()->ChangeScene(15);
	container->DeleteEntity(this);
}