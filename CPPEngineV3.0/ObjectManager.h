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
#include <boost/shared_array.hpp>

namespace GameEngineProject
{

	class ObjectManager
	{
	public:
		ObjectManager();
		~ObjectManager();

		GameObject * const GetFreeGameObject();
		bool ReturnGameObject(GameObject *);
		boost::shared_array<GameObject> GetAllGameObject(int &);

		Transform * const GetFreeTransfrom();
		bool ReturnTransform(Transform *);
		boost::shared_array<Transform> GetAllTransform(int &);

		GraphicsComponent * const GetFreeGraphicsComponent();
		bool ReturnTransform(GraphicsComponent *);
		boost::shared_array<GraphicsComponent> GetAllGraphicsComponent(int &);

		PhysicsComponent * const GetFreePhysicsComponent();
		bool ReturnPhysicsComponent(PhysicsComponent *);
		boost::shared_array<PhysicsComponent> GetAllPhysicsComponent(int &);

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