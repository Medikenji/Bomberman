#include "precomp.h"
#include "Interactable.h"
#include "Collision.h"
#include "BomberMan.h"
#include "SceneManager.h"
#include "World.h"

Interactable::Interactable(float2 _blockPosition, BlockContent _content)
{
	position = _blockPosition;
	scale = 15;
	m_content = _content;
	switch (m_content)
	{
	case BlockContent::EXIT:
		m_surface = new Surface("assets/Exit.png");
		break;
	case BlockContent::PW_SKATE:
		m_surface = new Surface("assets/Skate.png");
		break;
	case BlockContent::PW_FIRE:
		m_surface = new Surface("assets/Fire.png");
		break;
	default:
		printf("Wrong interactable content given");
		break;
	}
}


Interactable::~Interactable()
{
	delete m_surface;
}


void Interactable::Initialize()
{
	m_currentWorld = SceneManager::GetCurrentWorld();
}


void Interactable::Update(float)
{
	m_container->CopyToSurfaces(m_surface, position);
	Function();
}


void Interactable::Function()
{
	for (int i = 0; i < BomberMan::GetPlayerAmount(); i++)
	{
		BomberMan* player = BomberMan::GetPlayers()[i];
		if (Collision::RecToRec(GetRectangle(), player->GetRectangle()))
			switch (m_content)
			{
			case BlockContent::EXIT:
				Exit();
				break;
			case BlockContent::PW_SKATE:
				Skate(player);
				break;
			case BlockContent::PW_FIRE:
				Fire(player);
				break;
			default:
				printf("Wrong interactable content given");
				break;
			}
	}
}


void Interactable::Exit()
{
	if (m_currentWorld->AllowNextLevel())
	{
		m_container->GetSceneManager()->NextScene();
	}
}


void Interactable::Skate(BomberMan* _player)
{
	if (_player->AddSpeed())
	{
		m_container->DeleteEntity(this);
	}
}


void Interactable::Fire(BomberMan* _player)
{
	if (_player->AddBombRadius())
	{
		m_container->DeleteEntity(this);
	}
}