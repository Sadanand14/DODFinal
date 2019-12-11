#include "Physics.h"
#include <cassert>
namespace Gameplay
{
	PhysicsSystem::PhysicsSystem(vector <Entity*>& asteroidArr, vector <Entity*>& bulletArr) : m_AsteroidArr(asteroidArr), m_BulletArr(bulletArr)
	{

	}

	PhysicsSystem::~PhysicsSystem()
	{

	}

	void PhysicsSystem::Update()
	{
		CheckForCollisions();
		UpdatePosition();
	}

	void PhysicsSystem::UpdatePosition()
	{
		static vec3 velocity;
		static vec3 position;
		for (unsigned int i = 0; i < m_AsteroidArr.size(); ++i)
		{
			if (m_AsteroidArr[i]->GetStatus() == Status::Inactive)
				continue;

			velocity = m_AsteroidArr[i]->GetComponent<PhysicsComponent>()->m_velocity;
			position = m_AsteroidArr[i]->GetTransform()->GetPosition();

			position += velocity;
		}

		for (unsigned int i = 0; i < m_BulletArr.size(); ++i)
		{
			if (m_BulletArr[i]->GetStatus() == Status::Inactive)
				continue;

			velocity = m_AsteroidArr[i]->GetComponent<PhysicsComponent>()->m_velocity;
			position = m_AsteroidArr[i]->GetTransform()->GetPosition();

			position += velocity;
		}
		cout << "stop";
	}

	void PhysicsSystem::CheckForCollisions()
	{
		for (unsigned int i = 0; i < m_AsteroidArr.size(); ++i)
		{
			if (m_AsteroidArr[i]->GetStatus() == Status::Inactive)
				continue;

			static Transform* asteroidTransform;
			asteroidTransform = m_AsteroidArr[i]->GetTransform();

			static float asteroidSize;
			asteroidSize = m_AsteroidArr[i]->GetComponent<PhysicsComponent>()->m_bodySphereRadius;

			for (unsigned int j = 0; j < m_BulletArr.size(); ++j)
			{
				if (m_BulletArr[j]->GetStatus() == Status::Inactive)
					continue;

				static Transform* bulletTransform;
				bulletTransform = m_BulletArr[j]->GetTransform();

				static float bulletSize;
				bulletSize = m_BulletArr[j]->GetComponent<PhysicsComponent>()->m_bodySphereRadius;

				if (CalculateDistance(asteroidTransform->GetPosition(), bulletTransform->GetPosition()) < (asteroidSize + bulletSize))
				{
					cout << "Collision Detected!\n";
					if (m_AsteroidArr[i]->GetComponent<PhysicsComponent>()->m_bodySphereRadius > 5.0f) 
					{
						SplitAsteroid(i);
					}
					m_AsteroidArr[i]->SetStatus(Status::Inactive);
					m_BulletArr[j]->SetStatus(Status::Inactive);
				}
			}
		}
	}

	void PhysicsSystem::SplitAsteroid(unsigned int index) 
	{
		PhysicsComponent* temp = m_AsteroidArr[index]->GetComponent<PhysicsComponent>();
		assert(temp->m_bodySphereRadius > 5.0f);

		vec3 position = m_AsteroidArr[index]->GetTransform()->GetPosition();
		vec3 originalVel = temp->m_velocity;
		float speed = sqrt(originalVel.x * originalVel.x + originalVel.y * originalVel.y + originalVel.z * originalVel.z);
		vec3 normVel = normalize(originalVel);
		vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);
		vec3 right = normalize(cross(normVel, worldUp));
		vec3 orthoUp = normalize(cross(right, normVel));

		vec3 spawnVel[4] = {orthoUp, -orthoUp, -right, right};

		unsigned int spawnCounter = 0, lastSpawnIndex = 0;

		for (unsigned int i = 0; i < 4; ++i) 
		{
			for (unsigned int j = lastSpawnIndex; j < m_AsteroidArr.size(); i++) 
			{
				if (m_AsteroidArr[j]->GetStatus() == Status::Inactive) 
				{
					m_AsteroidArr[j]->SetStatus(Status::Active);
					m_AsteroidArr[j]->GetComponent<PhysicsComponent>()->m_bodySphereRadius =3.0f;
					m_AsteroidArr[j]->GetComponent<PhysicsComponent>()->m_velocity = speed * normalize(normVel + spawnVel[spawnCounter]);
					m_AsteroidArr[j]->GetTransform()->SetPosition(position);
					//TODO:: change Rendering Data
					spawnCounter++;
					lastSpawnIndex = j;
					break;
				}
			}
		}

		for (spawnCounter; spawnCounter < 4; ++spawnCounter) 
		{
			Entity* newEntity = new Entity(3.0f);
			newEntity->GetTransform()->SetPosition(position);
			newEntity->GetComponent<PhysicsComponent>()->m_velocity = speed * normalize(normVel + spawnVel[spawnCounter]);
			m_AsteroidArr.push_back(newEntity);
		}
	}

	void PhysicsSystem::DeactivateAsteroid(unsigned int index) 
	{
		m_BulletArr[index]->SetStatus(Status::Inactive);
	}

	void PhysicsSystem::DeactivateBullet(unsigned int index)
	{
		m_BulletArr[index]->SetStatus(Status::Inactive);
	}

	float CalculateDistance(vec3 position1, vec3 position2) 
	{
		float x = position1.x - position2.x;
		float y = position1.y - position2.y;
		float z = position1.z - position2.z;

		float result = sqrt( x * x + y * y + z * z);
		return result;
	}
}