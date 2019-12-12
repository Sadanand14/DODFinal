#pragma once

#include "Entity.h"

namespace Gameplay
{
	using namespace std;
	using namespace EntitySpace;
	
	class PhysicsSystem
	{
		vector<Entity*> m_AsteroidArr;
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