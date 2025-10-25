#include "precomp.h"
#include "BomberMan.h"
#include "World.h"
#include "Collision.h"
#include "SceneManager.h"
#include "AudioManager.h"

BomberMan::BomberMan(int _bomberId) {
	m_bomberId = _bomberId;
	drawnOnTopLayer = 1;
	AddSprite(new Sprite(new Surface("assets/Bomberman.png"), 19));
	m_animationState = 0;
	m_bombRadius = 1;
	m_animationTimer = 0;
	m_animationSwitch = 1;
	m_placedBombs = 0;
	m_maxPlacedBombs = 1;
	m_speed = START_SPEED;
	scale = 15;
}


BomberMan::~BomberMan()
{
	delete m_sprite;
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
	m_container->SetCameraX(m_bomberId, (int)(-position.x + RNDRWIDTH / EntityContainer::GetSurfaceAmount() / 2 - scale.x / 2));
	m_container->DrawToSurfaces(m_sprite, position, this);
	if (m_isDead)
		GoDie();
}


void BomberMan::DeletePlayers()
{
	for (int i = 0; i < m_playerAmount; i++)
	{
		m_players[i]->DeleteMask();
		delete m_players[i];
	}
	delete[] m_players;
}


void BomberMan::SetCurrentWorld(World* _currentWorld)
{
	for (int i = 0; i < m_playerAmount; i++)
	{
		m_players[i]->m_currentWorld = _currentWorld;
	}
}


void BomberMan::SetPlayers(BomberMan** _players, int _playerAmount)
{
	if (m_players != nullptr) {
		return;
	}
	m_playerAmount = _playerAmount;
	m_players = _players;
}


void BomberMan::BombAmount(bool _add_or_subtract)
{
	if (_add_or_subtract)
		m_placedBombs++;
	else
		m_placedBombs--;
}


bool BomberMan::AddBombRadius()
{
	if (m_bombRadius >= MAX_BOMB_RADIUS)
	{
		return 0;
	}
	m_bombRadius++;
	return 1;
}


bool BomberMan::AddSpeed()
{
	if (m_speed == START_SPEED)
	{
		m_speed *= 1.25f;
		return 1;
	}
	return 0;
}


void BomberMan::TileCollision()
{
	float2 temp = { position.x + scale.x / 2, position.y + scale.y / 2 };
	uint2 intGridPos = m_currentWorld->GetGridPos(temp);
	uint_fast8_t gridPos[2] = { (uint_fast8_t)intGridPos.x, (uint_fast8_t)intGridPos.y };
	uint_fast8_t l = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] - 1 , gridPos[1] });
	//uint_fast8_t tl = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] - 1, gridPos[1] - 1 });
	uint_fast8_t t = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] , gridPos[1] - 1 });
	//uint_fast8_t tr = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] + 1, gridPos[1] - 1 });
	uint_fast8_t r = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] + 1, gridPos[1] });
	//uint_fast8_t br = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] + 1, gridPos[1] + 1 });
	uint_fast8_t b = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] , gridPos[1] + 1 });
	//uint_fast8_t bl = m_currentWorld->GetCurrentBlockFromGrid({ gridPos[0] - 1, gridPos[1] + 1 });

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
		threshold = pixelPosition.x + World::BLOCKSIZE - 1;
		if (position.x + scale.x > threshold)
		{
			position.x = threshold - scale.x;
		}
	}

	// check bottom
	if (b != World::Block::GRASS)
	{
		threshold = pixelPosition.y + World::BLOCKSIZE - 1;
		if (position.y + scale.y > threshold)
		{
			position.y = threshold - scale.y;
		}
	}
}


void BomberMan::SetAnimation(float _velocityX, float _velocityY)
{
	int state = 0;

	if (_velocityX == 0 && _velocityY == 0)
		return;

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
		Animate(6);
		break;
	case 1:
		Animate(0);
		break;
	case 2:
		Animate(9);
		break;
	case 3:
		Animate(3);
		break;
	}
};


void BomberMan::Animate(uint_fast8_t _startFrame)
{
	m_currentFrame = _startFrame + m_animationState;
	if (m_animationTimer > 0)
	{
		return;
	}

	m_animationTimer = 0.05f;

	if (m_animationSwitch)
	{
		m_animationState++;
	}
	else
	{
		m_animationState--;
	}

	if (m_animationState < 1 || m_animationState > 1)
	{
		m_animationSwitch = !m_animationSwitch;
	}

}


void BomberMan::Input(float deltaTime, float* _velocityX, float* _velocityY)
{
	if (m_bomberId == 0)
	{
		if (m_placedBombs < m_maxPlacedBombs)
			if (GetAsyncKeyState(GLFW_KEY_E)) m_currentWorld->PlaceBomb(position + (scale.x / 2), this);
		if (GetAsyncKeyState(VK_UP)) *_velocityY += -m_speed * deltaTime;
		if (GetAsyncKeyState(VK_DOWN)) *_velocityY += m_speed * deltaTime;
		if (GetAsyncKeyState(VK_LEFT)) *_velocityX += -m_speed * deltaTime;
		if (GetAsyncKeyState(VK_RIGHT)) *_velocityX += m_speed * deltaTime;
	}
	if (m_bomberId == 1)
	{
		if (GetAsyncKeyState(GLFW_KEY_RIGHT_SHIFT)) m_currentWorld->PlaceBomb(position + (scale.x / 2), this);
		if (GetAsyncKeyState(GLFW_KEY_W)) *_velocityY += -m_speed * deltaTime;
		if (GetAsyncKeyState(GLFW_KEY_S)) *_velocityY += m_speed * deltaTime;
		if (GetAsyncKeyState(GLFW_KEY_A)) *_velocityX += -m_speed * deltaTime;
		if (GetAsyncKeyState(GLFW_KEY_D)) *_velocityX += m_speed * deltaTime;
	}
}


void BomberMan::GoDie()
{
	m_speed = 0;
	AudioManager::GetAudioManager()->StopAudio(Audio::MainTheme, 2000);
	if (m_currentFrame < 11)
	{
		m_currentFrame = 11;
	}
	if (m_animationTimer > 0)
	{
		return;
	}
	m_animationTimer = 0.25f;
	if (++m_currentFrame == 19) {
		m_container->GetSceneManager()->ChangeScene(15);
		return;
	}
}