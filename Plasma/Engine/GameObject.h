// By @ByCubed7 on Twitter

#pragma once

#include "Object.h"
#include "Vector.h"

#include <list>
#include <set>

namespace Engine 
{
	// Forward declaration
	class Scene;
	class Component;


	class GameObject : public Object
	{
	public:
		Engine::Scene* scene;

		Vector2 position;
		float rotation;
		Vector2 scale;

		GameObject* SetPosition(Vector2 value);
		GameObject* SetRotation(float value);
		GameObject* SetScale(Vector2 value);

		Vector2& GetPosition();
		float&   GetRotation();
		Vector2& GetScale();

		std::set<Component*> components;

		// Tags
		std::set<std::string> tags;
		void AddTag(std::string tag);
		void RemoveTag(std::string tag);
		bool HasTag(std::string tag);

		Component* AddComponent(Component* component);
		Component* GetComponent(std::string componentName);
		bool HasComponent(std::string componentName);
		void RemoveComponent(Component* component);

		template<class T> T* Get();
		template<class T> T* Add();

		bool isSolid;
		bool destroyed;

		// Constructors
		GameObject(Engine::Scene* scene);

		// Operator Overrides
		operator bool();
	};



	template<class T>
	inline T* GameObject::Get()
	{
		for (Component* component : components)
		{
			T* casted = dynamic_cast<T*>(component);
			if (casted != nullptr)
				return casted;
		}

		return nullptr;
	}

	template<class T>
	inline T* GameObject::Add()
	{
		T* newComponent = new T(this, typeid(T).name());
		return newComponent;
	}
}