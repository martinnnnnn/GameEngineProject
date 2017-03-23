#include "ObjectManager.h"

using namespace GameEngineProject;





ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}


GameObject * const ObjectManager::GetFreeGameObject()
{
	return _gameObjectFactory.GetNew();
}

bool ObjectManager::ReturnGameObject(GameObject * obj)
{
	return _gameObjectFactory.Free(obj);
}

boost::shared_array<GameObject> ObjectManager::GetAllGameObject(int & length)
{
	return _gameObjectFactory.GetAll(length);
}


Transform * const ObjectManager::GetFreeTransfrom()
{
	return _transformComponentFactory.GetNew();
}

bool ObjectManager::ReturnTransform(Transform * tranform)
{
	return _transformComponentFactory.Free(tranform);
}

boost::shared_array<Transform> ObjectManager::GetAllTransform(int & length)
{
	return _transformComponentFactory.GetAll(length);
}


GraphicsComponent * const ObjectManager::GetFreeGraphicsComponent()
{
	return _graphicsComponentFactory.GetNew();
}

bool ObjectManager::ReturnTransform(GraphicsComponent * graphics)
{
	return _graphicsComponentFactory.Free(graphics);
}

boost::shared_array<GraphicsComponent> ObjectManager::GetAllGraphicsComponent(int & length)
{
	return _graphicsComponentFactory.GetAll(length);
}


PhysicsComponent * const ObjectManager::GetFreePhysicsComponent()
{
	return _physicsComponentFactory.GetNew();
}

bool ObjectManager::ReturnPhysicsComponent(PhysicsComponent * physics)
{
	return _physicsComponentFactory.Free(physics);
}

boost::shared_array<PhysicsComponent> ObjectManager::GetAllPhysicsComponent(int & length)
{
	return _physicsComponentFactory.GetAll(length);
}
