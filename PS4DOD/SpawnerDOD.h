#pragma once

#include "EntityDOD.h"

namespace Gameplay
{
	using namespace std;
	using namespace EntityDOD;
	using namespace glm;

	class SpawnerDOD
	{
	private:
		EntityGroup* m_Asteroids, *m_Bullets;

		float m_timer;

		const float spawnSize = 6.0f;
		const float spawnSpeed = 2.0f;
		const float spawnTime = 5.0f;
		const float	spawnDistance = 20.0f;
		const float	spawnSquareSide = 10.0f;
		const unsigned int spawnCount = 5;

	public:
		SpawnerDOD(EntityGroup* asteroids, EntityGroup* bullets);
		~SpawnerDOD();

		glm::vec3 m_playerFront, m_playerRight, m_playerUp, m_playerPosition;//must be normalized except for postion

		void SpawnAsteroids();
		void DestroyAsteroids(std::vector<unsigned int>& destroyedEntities);
		void DestroyBullets(std::vector<unsigned int>& destroyedEntities);
		void SplitAsteroids(vector<Info>& infoArr);
	};
}