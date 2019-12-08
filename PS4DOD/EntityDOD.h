#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <glm/glm.hpp>

namespace EntityDOD
{

#define MAX_ENTITY_COUNT 5000

	using namespace glm;

	enum class Status { Active, Inactive };

	struct RenderComponent
	{
		Status m_status;
	};

	struct PhysicsComponent
	{
		Status m_status;
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

		Transform(vec3  Pos) : m_position(Pos), m_rotation(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f)
		{}

		Transform() :m_position(0.0f, 0.0f, 0.0f), m_rotation(0.0f, 0.0f, 0.0f), m_scale(1.0f, 1.0f, 1.0f) {}
	};


	class EntityGroup
	{
	private:
		unsigned int entityCount;
		std::vector<PhysicsComponent> physicsComponents;
		std::vector<RenderComponent>  renderComponents;

	public:
		EntityGroup()
		{
			entityCount = 0;
			//physicsComponents.reserve(MAX_ENTITY_COUNT);
			//renderComponents.reserve(MAX_ENTITY_COUNT);
		}
		~EntityGroup()
		{

		};

		inline void AddDefaultEntity()
		{
			if (entityCount == MAX_ENTITY_COUNT) return;

			physicsComponents.push_back = PhysicsComponent();
			renderComponents.push_back = RenderComponent();
			entityCount++;
		}

		inline PhysicsComponent& GetPhysicsComponent(unsigned int index)
		{
			assert(entityCount > index);

			return physicsComponents[index];
		}

		inline RenderComponent& GetRenderComponent(unsigned int index)
		{
			assert(entityCount > index);

			return renderComponents[index];
		}

		inline void DeactivateEntity( unsigned int index) 
		{
			physicsComponents[index].m_status = Status::Inactive;
			renderComponents[index].m_status = Status::Inactive;
		}
	};

}
