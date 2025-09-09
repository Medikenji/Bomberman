#include "precomp.h"
#include "World.h"

World::World() {
    m_hardBlocksGenerated = false;
    position.y = 32;
    this->m_grass = new Surface("assets/Grass.png");
    this->InitialiseLevels();
    this->currentLevel = level1;
}

void World::Update(float deltaTime)
{
    DrawMap();
    UpdateChildren(deltaTime);
}

int World::GetCurrentBlock(float x, float y)
{
    int row = (int)((y+blocksize - position.y)/blocksize);
    int column = (int)(((x + blocksize - this->position.x) / blocksize));
    int datapos = (row * currentLevel->mapWidth) + column - currentLevel->mapWidth - 1;
    switch (currentLevel->mapData[datapos])
    {
    case 1:
        //printf("Hardwall \n");
        //return Actor::HARDWALL;
        break;
    case 2:
        //printf("Grass \n");
        //return Actor::GRASS;
        break;
    case 3:
        //printf("Softwall \n");
        //return Actor::SOFTWALL;
        break;
    default:
        //printf("N/A \n");
        return -1;
        break;
    }
}


bool World::DrawMap()
{
    float bx = 0, by = -blocksize;
    bx += this->position.x;
    by += this->position.y;
    for (int i = 0; i < currentLevel->mapSize; i++)
    {
        if (i % currentLevel->mapWidth == 0)
        {
            bx = 0;
            by += blocksize;
        }
        if (currentLevel->mapData[i] == 1 &&  !m_hardBlocksGenerated)
        {
            AddChild(new HardBlock({ bx, by }));
        }
        if (currentLevel->mapData[i] == 2)
        {
            //this->m_grass->CopyTo(mainsurface, bx, by);
            CopyToSurfaces(m_grass, bx, by);
        }
        bx += blocksize;
    }
    m_hardBlocksGenerated = true;
    return true;
}

bool World::InitialiseLevels()
{
	level1 = new Level(25);
    level1->mapData = new UINT8[325] {
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
            1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
            1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
            1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
            1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
            1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
            1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
            1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
            1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
            1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1,
            1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        };
    level1->mapSize = 325;
	return true;
}