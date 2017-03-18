#pragma once

// TODO : read number of object from file
// TODO : Fle reading system

#include "Utils.h"
#include "Factory.h"
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "Tranform.h"
#include "Script.h"

#include <vector>

namespace GameEngineProject
{

	typedef enum
	{
		GAMEOBJECT,
		COMPONENT,
		SCRIPT
	} ObjectType;



	class ObjectManager
	{
	public:
		ObjectManager();
		~ObjectManager();

		GameObject * const GetFreeGameObject();
		bool ReturnGameObject(GameObject *);
		GameObject * GetAllGameObject(int & length);

		Transform * const GetFreeTransfrom();
		bool ReturnTransform(Transform *);
		Transform * GetAllTransform(int & length);

		GraphicsComponent * const GetFreeGraphicsComponent();
		bool ReturnTransform(GraphicsComponent *);
		GraphicsComponent * GetAllGraphicsComponent(int & length);

		PhysicsComponent * const GetFreePhysicsComponent();
		bool ReturnPhysicsComponent(PhysicsComponent *);
		PhysicsComponent * GetAllPhysicsComponent(int & length);

	private:
		Factory<GameObject, 100000> _gameObjectFactory;
		Factory<Transform, 100000> _transformComponentFactory;
		Factory<GraphicsComponent, 100000> _graphicsComponentFactory;
		Factory<PhysicsComponent, 100000> _physicsComponentFactory;

		
	};

}




	//public:
	//	bool Init();
	//	bool InitGameObjects(int size);
	//	void ClearGameObjects();

	//	GameObject * const GetFree();
	//	bool Return(GameObject *);

	//	bool InitPrefab(const std::string & path, int size);
	//	GameObject* GetPrefab(const std::string & name);
	//	bool ClearPrefab(const std::string & name);


	//private:

	//	bool ReturnPrefab(const std::string &, GameObject * const);



	//private:
	//	std::vector<Tag> _tags;
	//	std::vector<GameObject*> _gameObjects;
	//	std::unordered_set<std::string, std::vector<GameObject*>> _gameObjectPrefabs;