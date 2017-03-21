#pragma once

// TODO : MESSAGING

#include "Utils.h"
#include "Factoriable.h"

#include <string>
#include <vector>


namespace GameEngineProject
{
	class Component;
	class Script;
	class PhysicsComponent;
	class GraphicsComponent;
	class Transform;

	class GameObject : public Factoriable
	{
	public:
		explicit GameObject();
		virtual ~GameObject();


	public:
		void Awake();
		void Start();
		void Update();
		void Shutdown();


	public:
		int GetId() const;
		void SetId(int);
		const std::string & GetName();
		void SetName(const std::string &);
		Tag GetTag();
		void SetTag(Tag);
		bool CompareTag(const Tag &);
		bool AddScript(Script * const);
		bool RemoveScript(Script * const);
		bool RemoveScript(const std::string &);
		void ClearScripts();
		Transform * const GetTransform();
		GraphicsComponent * const GetGraphicsComponent();
		PhysicsComponent * const GetPhysicsComponent();
		void SetTransform(Transform * const);
		void SetGraphicsComponent(GraphicsComponent * const);
		void SetPhysicsComponent(PhysicsComponent * const);


	public:
		virtual bool operator==(const GameObject &);
		virtual bool operator==(const Factoriable &);
		virtual void Swap(const GameObject &);
		virtual void Swap(const Factoriable &);
		virtual void Reset();
		GameObject(const GameObject &);


	private:
		int _id;
		std::string _name;
		Tag _tag;
		bool _shotdown;
		std::vector<Script *> _scripts;
		Transform * _transform;
		GraphicsComponent * _graphics;
		PhysicsComponent * _physics;

		

	private:
		const GameObject & operator=(const GameObject &) = delete;

		//std::vector<Component *> _components;
		//bool AddComponent(Component * const);
		//bool RemoveComponent(Component * const);
		//void ClearComponents();

	};


}
