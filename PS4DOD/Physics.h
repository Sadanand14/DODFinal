#pragma once

#include "EntityDOD.h"

namespace Gameplay
{
	using namespace std;
	using namespace EntityDOD;
	
	class PhysicsSystem
	{
		vector<Phys*> m_AsteroidArr;
		vector<Entity*> m_BulletArr;

		void CheckForCollisions();
		void UpdatePosition();

		void DeactivateBullet(unsigned int index);
		void DeactivateAsteroid(unsigned int index);
		void SplitAsteroid(unsigned int index);

	public:
		PhysicsSystem(vector<Entity*>&  asteroidArr, vector<Entity*>&  bulletArr);
		~PhysicsSystem();

		inline void SetAsteroids(vector<Entity*> value) { m_AsteroidArr = value; }
		inline void SetBullets(vector<Entity*> value) { m_BulletArr = value; }

		void Update();
	};

	float CalculateDistance(vec3 position1, vec3 position2);
}