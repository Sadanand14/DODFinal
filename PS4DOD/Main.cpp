#include <iostream>
#include "Entity.h"
#include "Physics.h"
#define ENTITYCOUNT 10

int main()
{
	//OOP implementation
	{
		using namespace std;
		using namespace EntitySpace;
		using namespace Gameplay;

		//initialize bullets
		vector<Entity*> bulletList;
		bulletList.reserve(ENTITYCOUNT);
		for (unsigned int i = 0; i < ENTITYCOUNT; ++i) 
		{
			bulletList.push_back(new Entity(0.1f));
		}
		
		//initilize Asteroids
		vector<Entity*> asteroidList;
		asteroidList.reserve(ENTITYCOUNT);
		for (unsigned int i = 0; i < ENTITYCOUNT; ++i)
		{
			asteroidList.push_back(new Entity(6.0f));
		}


		PhysicsSystem* physics = new PhysicsSystem(asteroidList, bulletList);

		static unsigned int counter = 0;
		//GameLoop
		while (true) 
		{
			physics->Update();
			if (counter++ == 100)
				cout << "stop";
		}

		//clean up
		delete physics;
		for(auto & entity: asteroidList) delete entity;
		for(auto & entity: bulletList) delete entity;
	}

}