#pragma once
#include<vector>
#include "Entity.h"

namespace Gameplay
{

#define SPAWN_DISTANCE 20.0f;
#define SPAWN_SQUARE_SIDE 10.0f;
#define SPAWN_RATE 5.0f;
#define SPAWN_COUNT 5;

	using namespace EntitySpace;
	class Spawner
	{
	private:
		std::vector<Entity* > m_asteroidArr;
		Entity* m_player;
		
		glm::vec3 m_playerFront, m_playerRight, m_playerUp, m_playerPosition;//must be normalized except for postion
		float m_timer;

		const float spwanSpeed = 2.0f;
		const float spawnTime = 5.0f;
		const float	spawnDistance = 20.0f;
		const float	spawnSquareSide = 10.0f;
		const unsigned int spwanCount = 5; 

	public:
		Spawner(std::vector<Entity* >& asteroidArr, Entity* entity);
		~Spawner();
		void Spawn(float dt);
	};
}