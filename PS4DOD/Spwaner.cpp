#include "Spawner.h"
#include <cstdlib>

namespace Gameplay 
{
	Spawner::Spawner(std::vector<Entity* >& asteroidArr, Entity* entity) :m_asteroidArr(asteroidArr), m_player(entity), m_timer(0.0f)
	{
		
	}

	Spawner::~Spawner() 
	{
		
	}
	
	void Spawner::Spawn(float dt) 
	{
		m_timer += dt;
		if (m_timer> spawnTime) 
		{
			m_timer -= spawnTime;

			glm::vec3 spawnCentre = m_playerPosition + m_playerFront*spawnDistance;
			for (unsigned int i = 0; i < spwanCount; i++) 
			{
				unsigned int randomX = (rand() % 100) - 50;
				unsigned int randomY = (rand() % 100) - 50;

				glm::vec3 asteroidPos =  (m_playerPosition + (m_playerRight * (randomX * 0.1f))) + (m_playerUp * (randomY * 0.1f));
				
			}
		}
		
	}
}