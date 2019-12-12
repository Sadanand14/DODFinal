#include "SpawnerDOD.h"

namespace Gameplay
{
	SpawnerDOD::SpawnerDOD(EntityGroup* asteroids, EntityGroup* bullets) : m_Asteroids(asteroids), m_Bullets(bullets)
	{}

	SpawnerDOD::~SpawnerDOD()
	{}

	void SpawnerDOD::SplitAsteroids(vector<Info>& infoArr)
	{
		static unsigned int i, spawnCounter = 0;
		static vec3 position, originalVel, normVel, worldUp, right, orthoUp, spawnVel[4], finalVel;
		static float speed;

		worldUp = vec3(0.0f, 1.0f, 0.0f);

		static vector <Info> entityData;
		if (entityData.capacity() < infoArr.size() * 4) entityData.reserve(infoArr.size() * 4);
		entityData.clear();

		for (i = 0; i < infoArr.size(); ++i)
		{
			position = infoArr[i].m_position;
			originalVel = infoArr[i].m_velocity;
			speed = sqrt(originalVel.x * originalVel.x + originalVel.y * originalVel.y + originalVel.z * originalVel.z);
			normVel = normalize(originalVel);
			right = normalize(cross(normVel, worldUp));
			orthoUp = normalize(cross(right, normVel));

			spawnVel[0] = orthoUp;
			spawnVel[1] = -orthoUp;
			spawnVel[2] = -right;
			spawnVel[3] = right;

			for (spawnCounter = 0; spawnCounter < 4; ++spawnCounter)
			{
				finalVel = speed * normalize(normVel + spawnVel[spawnCounter]);
				entityData.push_back(Info(position, finalVel,3.0f));
			}
		};

		m_Asteroids->AddEntities(entityData);
	}

	void SpawnerDOD::DestroyAsteroids(std::vector<unsigned int>& destroyedEntities)
	{
		m_Asteroids->DeactivateEntities(destroyedEntities);
	}

	void SpawnerDOD::DestroyBullets(std::vector<unsigned int>& destroyedEntities)
	{
		m_Bullets->DeactivateEntities(destroyedEntities);
	}

	void SpawnerDOD::SpawnAsteroids() 
	{
		
	}
}