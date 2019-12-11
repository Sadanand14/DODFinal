#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include <glm/glm.hpp>

namespace EntitySpace
{
	using namespace glm;
	enum class Status { Active, Inactive };

	struct RenderComponent
	{

	};

	struct PhysicsComponent
	{
		float m_bodySphereRadius;
		glm::vec3 m_velocity;

		PhysicsComponent() : m_bodySphereRadius(5.0f), m_velocity(0.0f,0.0f,0.0f) 
		{}

		PhysicsComponent(float size) :m_bodySphereRadius(size), m_velocity(0.0f, 0.0f, 0.0f) 
		{}

		PhysicsComponent(vec3 velocity, float size):m_velocity(velocity), m_bodySphereRadius(size) 
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
	};


	class Entity
	{
	private:
		PhysicsComponent* m_phyC;
		RenderComponent* m_renC;
		Transform* m_transform;
		Status m_status;

	public:

		Entity(): m_status(Status::Inactive), m_renC(nullptr)
		{
			m_phyC = new PhysicsComponent();
			m_transform = new Transform();
		}

		Entity(float size) : m_status(Status::Active), m_renC(nullptr)
		{
			m_phyC = new PhysicsComponent(size);
			m_transform = new Transform();
		}

		Entity(vec3 pos, vec3 velocity, float size) : m_status(Status::Active), m_renC(nullptr)
		{
			m_phyC = new PhysicsComponent(velocity, size);
			m_transform = new Transform(pos);
		}

		~Entity()
		{
			if (m_phyC != nullptr) delete m_phyC;
			if (m_renC != nullptr) delete m_renC;
			delete m_transform;
		};

		inline Status& GetStatus() { return m_status; }
		inline void SetStatus(Status value) { m_status = value; }

		inline Transform* GetTransform() { return m_transform; }

		template<typename T>
		inline T* GetComponent();

		template<typename F>
		inline void AddComponent();
	};

	template<>
	inline void Entity::AddComponent<RenderComponent>()
	{
		if (m_renC != nullptr)
		{
			std::cout << "Render component already exists on the entity" << "\n";
			return;
		}

		m_renC = new RenderComponent();
	}

	template<>
	inline void Entity::AddComponent<PhysicsComponent>()
	{
		if (m_renC != nullptr)
		{
			std::cout << "Physics component already exists on the entity" << "\n";
			return;
		}

		m_phyC = new PhysicsComponent();
	}

	template<>
	inline RenderComponent* Entity::GetComponent<RenderComponent>()
	{
		return m_renC;
	}

	template<>
	inline PhysicsComponent* Entity::GetComponent<PhysicsComponent>()
	{
		return m_phyC;
	}

}