#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <glm/glm.hpp>

namespace EntityDOD
{

#define MAX_ENTITY_COUNT 5000


	enum class Status { Active, Inactive };
	using namespace glm;

	struct Info
	{
		vec3 m_position;
		vec3 m_velocity;
		float m_size;

		Info(vec3 position, vec3 velocity, float size) : m_position(position), m_velocity(velocity), m_size(size)
		{}
	};

	struct Transform
	{
	private:
		vec3 m_position;
		vec3 m_rotation;
		vec3 m_scale;

	public:

		inline const vec3& GetPosition() { return m_position; }
		inline const vec3& GetRotation() { return m_rotation; }
		inline const vec3& GetScale() { return m_scale; }

		inline void SetPosition(vec3 value) { m_position = value; }

		Transform(vec3 Pos) : m_position(Pos), m_rotation(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f)
		{}

		Transform() :m_position(0.0f, 0.0f, 0.0f), m_rotation(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f)
		{}

		//Transform& operator=(const Transform& otherTransform);
	};

	/*Transform& Transform::operator=(const Transform& otherTransform)
	{
		m_position = otherTransform.m_position;
		m_rotation = otherTransform.m_rotation;
		m_scale = otherTransform.m_scale;
		return *this;
	}*/

	struct RenderComponent
	{
		Status m_status;
		Transform m_transform;
	};

	struct PhysicsComponent
	{
		float m_bodySphereRadius;
		glm::vec3 m_velocity;
		Status m_status;
		vec3 m_position;

		PhysicsComponent() : m_bodySphereRadius(5.0f), m_velocity(0.0f, 0.0f, 0.0f)
		{}

		PhysicsComponent(float size) :m_bodySphereRadius(size), m_velocity(0.0f, 0.0f, 0.0f)
		{}

		PhysicsComponent(vec3 pos, vec3 velocity, float size) :m_velocity(velocity), m_bodySphereRadius(size), m_position(pos)
		{}
	};


	class EntityGroup
	{
	private:
		unsigned int m_entityCount;
		std::vector<PhysicsComponent> m_physicsComponents;
		std::vector<RenderComponent>  m_renderComponents;

	public:
		EntityGroup() :m_entityCount(0)
		{
			//physicsComponents.reserve(MAX_ENTITY_COUNT);
			//renderComponents.reserve(MAX_ENTITY_COUNT);
		}
		~EntityGroup()
		{

		};

		inline void AddEntities(std::vector<Info>& const infoArr)
		{
			static unsigned int lastSpawnIndex, entitiesAssigned;
			static bool breakLoop;

			breakLoop = false;
			entitiesAssigned = 0;
			lastSpawnIndex = 0;

			//run only if any entities exist inside
			if (m_entityCount > 0)
			{
				for (unsigned int i = 0; i < infoArr.size(); i++)
				{
					for (unsigned int j = lastSpawnIndex; i < m_entityCount; i++)
					{
						//if all elements were checked dont continue the loop
						if (j == m_entityCount - 1) breakLoop = true;

						//check for any rendercomponent/physics component status
						if (m_physicsComponents[j].m_status == Status::Inactive)
						{
							m_physicsComponents[j].m_status = Status::Active;
							m_physicsComponents[j].m_position = infoArr[i].m_position;
							m_physicsComponents[j].m_velocity = infoArr[i].m_velocity;
							m_physicsComponents[j].m_bodySphereRadius = infoArr[i].m_size;


							m_renderComponents[j].m_status = Status::Active;
							//TODO:: change Rendering Data if needed

							entitiesAssigned++;
							lastSpawnIndex = j + 1;
							break;
						}
					}
					if (breakLoop) break;
				}
			}

			static unsigned int requiredCapacity;

			requiredCapacity = m_entityCount + infoArr.size() - entitiesAssigned;

			if (requiredCapacity > m_physicsComponents.capacity())
			{
				m_physicsComponents.reserve(requiredCapacity); m_renderComponents.reserve(requiredCapacity);
			}

			//create new entities to for the remaining enitites
			for (unsigned int i = entitiesAssigned; i < infoArr.size(); ++i)
			{
				AddEntity(infoArr[i].m_position, infoArr[i].m_velocity, infoArr[i].m_size);
			}
		}

		inline void AddEntity(vec3 pos, vec3 velocity, float size)
		{
			if (m_entityCount == MAX_ENTITY_COUNT) return;

			//one time initialization of static template for components
			static PhysicsComponent PC = PhysicsComponent();
			static RenderComponent RC = RenderComponent();

			//feed values into the template
			PC.m_position = pos;
			PC.m_status = Status::Active;
			PC.m_bodySphereRadius = size;
			PC.m_velocity = velocity;

			//TODO: assign RenderComponentData before pushing

			//copy values on template onto newly constructed entity
			m_physicsComponents.push_back(PC);
			m_renderComponents.push_back(RC);
			m_entityCount++;
		}

		inline void AddDefaultEntity()
		{
			if (m_entityCount == MAX_ENTITY_COUNT) return;
			m_physicsComponents.push_back(PhysicsComponent());
			m_renderComponents.push_back(RenderComponent());
			m_entityCount++;
		}

		inline std::vector<PhysicsComponent>& GetPhysComponentArray() { return m_physicsComponents; }
		inline std::vector<RenderComponent>& GetRendComponentArray() { return m_renderComponents; }

		inline void DeactivateEntities(std::vector<unsigned int>& destroyedEntities) 
		{
			for (unsigned int i = 0; i < destroyedEntities.size(); ++i) 
			{
				m_physicsComponents[destroyedEntities[i]].m_status = Status::Inactive;
				m_renderComponents[destroyedEntities[i]].m_status = Status::Inactive;
			}
		}

		/*inline PhysicsComponent& GetPhysicsComponent(unsigned int index)
		{
			assert(m_entityCount > index);

			return m_physicsComponents[index];
		}

		inline RenderComponent& GetRenderComponent(unsigned int index)
		{
			assert(m_entityCount > index);

			return m_renderComponents[index];
		}*/

		inline void DeactivateEntity(unsigned int index)
		{
			m_physicsComponents[index].m_status = Status::Inactive;
			m_renderComponents[index].m_status = Status::Inactive;
		}
	};

}
