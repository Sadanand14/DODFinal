#pragma once

#include "EntityDOD.h"
#include "SpawnerDOD.h"
namespace Gameplay
{
	using namespace std;
	using namespace EntityDOD;

	class PhysicsDODSystem
	{
		vector<PhysicsComponent> * m_AsteroidArr, * m_BulletArr;
		SpawnerDOD* m_spawner;

	public:
		PhysicsDODSystem(vector<PhysicsComponent>* asteroidArr, vector<PhysicsComponent>* bulletArr, SpawnerDOD* spawner);
		~PhysicsDODSystem();

		inline void SetAsteroids(vector<PhysicsComponent>* value) { m_AsteroidArr = value; }
		inline void SetBullets(vector<PhysicsComponent>* value) { m_BulletArr = value; }

		void Update(float dt);
	};

	float CalculateDistance(vec3 position1, vec3 position2);
}