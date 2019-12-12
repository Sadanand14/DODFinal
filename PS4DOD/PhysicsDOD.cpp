#include "PhysicsDOD.h"

namespace Gameplay 
{
	PhysicsDODSystem::PhysicsDODSystem(vector<PhysicsComponent>* asteroidArr, vector<PhysicsComponent>* bulletArr, SpawnerDOD*  spawner)
		: m_AsteroidArr(asteroidArr), m_BulletArr(bulletArr), m_spawner( spawner)
	{}

	PhysicsDODSystem::~PhysicsDODSystem() 
	{}

	void PhysicsDODSystem::Update(float dt)
	{

		////CHECKING FOR COLLISIONS////////////////////////////////////////////////////////////////////////////////////
		
		//initialize variables as statics to avoid reinitializing them every function call
		static vec3 asteroidPos, bulletPos;
		static float asteroidSize = 0.0f, bulletSize = 0.0f, x = 0.0f, y = 0.0f, z = 0.0f, result = 0.0f;

		static vector<unsigned int> destroyedBullets, destroyedAsteroids, splitAsteroids;

		static unsigned int Asize = 0, Bsize = 0, i = 0, j = 0;

		//get updated asteroid/bullet count
		Asize = m_AsteroidArr->size();
		Bsize = m_BulletArr->size();

		//updated capacity
		if (splitAsteroids.capacity() < Asize) splitAsteroids.reserve(Asize/2);
		if (destroyedAsteroids.capacity() < Asize) destroyedAsteroids.reserve(Asize/2);
		if (destroyedBullets.capacity() < Bsize) destroyedBullets.reserve(Bsize/2);

		splitAsteroids.clear();
		destroyedAsteroids.clear();
		destroyedBullets.clear();

		for (i = 0; i < Asize; ++i)
		{
			//dont bother if inactive
			if ((*m_AsteroidArr)[i].m_status == Status::Inactive)
				continue;

			// has to be done outside the nested for to avoid blowing cache
			asteroidPos = (*m_AsteroidArr)[i].m_position;
			asteroidSize = (*m_AsteroidArr)[i].m_bodySphereRadius;

			for (j = 0; j < Bsize; ++j)
			{
				if ((*m_BulletArr)[j].m_status == Status::Inactive)
					continue;

				bulletSize = (*m_BulletArr)[j].m_bodySphereRadius;
				bulletPos = (*m_BulletArr)[j].m_position;

				x = asteroidPos.x - bulletPos.x;
				y = asteroidPos.y - bulletPos.y;
				z = asteroidPos.z - bulletPos.z;
				result = glm::sqrt(x*x + y*y +z*z);

				if(result < (asteroidSize + bulletSize))
				{
					cout << "Collision Detected!\n";
					if (asteroidSize > 5.0f) splitAsteroids.push_back(i);
		
					destroyedAsteroids.push_back(i);
					destroyedBullets.push_back(j);
				}
			}
		}

		//////////////SPLITTING ASTEROIDS//////////////////////////////////////////////////
		
		static vector<Info> splitInfo;
		splitInfo.clear();

		static unsigned int splitSize = 0;
		splitSize = splitAsteroids.size();
		if (splitInfo.capacity() < splitSize) splitInfo.reserve(splitSize);

		for(i = 0; i < splitAsteroids.size(); ++i) 
		{
			PhysicsComponent* temp =  &((*m_AsteroidArr)[splitAsteroids[i]]);
			splitInfo.push_back(Info(temp->m_position, temp->m_velocity, temp->m_bodySphereRadius));
		}

		//if asteroids Destroyed then deactivate their components
		if (destroyedAsteroids.size() > 0) m_spawner->DestroyAsteroids(destroyedAsteroids);

		//if bullets destroyed then deactivate their components
		if (destroyedBullets.size() > 0) m_spawner->DestroyBullets(destroyedBullets);

		//if asteroids need to be created, call spawner method
		if (splitSize > 0)m_spawner->SplitAsteroids(splitInfo);

		//UpdatePositions for the entities
		for (i = 0; i < m_AsteroidArr->size(); ++i) 
		{
			(*m_AsteroidArr)[i].m_position += (*m_AsteroidArr)[i].m_velocity * dt;
		}

		for (i = 0; i < m_BulletArr->size(); ++i) 
		{
			(*m_BulletArr)[i].m_position += (*m_BulletArr)[i].m_velocity * dt;
		}
	}
}