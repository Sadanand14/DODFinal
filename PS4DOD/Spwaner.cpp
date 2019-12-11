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


			m_lastSpawnIndex = 0;
			static bool asteroidSpawned = 0;
			static glm::vec3 asteroidPos, aim, velocity;

			glm::vec3 spawnCentre = m_playerPosition + m_playerFront*spawnDistance;
			for (unsigned int i = 0; i < spwanCount; i++) 
			{
				unsigned int random1 = (rand() % 100) - 50;
				unsigned int random2 = (rand() % 100) - 50;
				unsigned int random3 = (rand() % 100) - 50;
				unsigned int random4 = (rand() % 100) - 50;

				//get asteroid position;
				asteroidPos =  (spawnCentre + (m_playerRight * (random1 * 0.1f))) + (m_playerUp * (random2 * 0.1f));

				//get direction to move
				aim = (m_playerPosition + (m_playerRight * (random3 * 0.05f))) + (m_playerUp * (random4 * 0.05f));

				//get velocity
				velocity = glm::normalize(aim - asteroidPos) * spawnSpeed;

				asteroidSpawned = false;

				for (unsigned int i = m_lastSpawnIndex; i < m_asteroidArr.size(); i++) 
				{
					if (m_asteroidArr[i]->GetStatus() == Status::Inactive) 
					{
						m_asteroidArr[i]->SetStatus(Status::Active);
						m_asteroidArr[i]->GetTransform()->SetPosition(asteroidPos);
						m_asteroidArr[i]->GetComponent<PhysicsComponent>()->m_bodySphereRadius = spawnSize;
						m_asteroidArr[i]->GetComponent<PhysicsComponent>()->m_velocity = velocity;
						asteroidSpawned = true;
						m_lastSpawnIndex = i;
						break;
					}
				}

				if (!asteroidSpawned) 
				{
					Entity* newAsteroid = new Entity(asteroidPos, velocity , spawnSize);
					m_asteroidArr.push_back(newAsteroid);
				}
			}
		}
		
		
	}
}