#pragma once

#include "EntityDOD.h"
namespace Gameplay
{
	using namespace std;
	using namespace EntityDOD;

	class PhysicsSystem
	{
		vector<PhysicsComponent*> m_AsteroidArr;
		vector<PhysicsComponent*> m_BulletArr;

		void CheckForCollisions();
		void UpdatePosition();

		void DeactivateBullet(unsigned int index);
		void DeactivateAsteroid(unsigned int index);
		void SplitAsteroid(unsigned int index);

	public:
		PhysicsSystem(vector<PhysicsComponent*>& asteroidArr, vector<PhysicsComponent*>& bulletArr);
		~PhysicsSystem();

		inline void SetAsteroids(vector<PhysicsComponent*> value) { m_AsteroidArr = value; }
		inline void SetBullets(vector<PhysicsComponent*> value) { m_BulletArr = value; }

		void Update();
	};

	float CalculateDistance(vec3 position1, vec3 position2);
}