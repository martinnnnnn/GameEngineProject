#include "Scene.h"


#include "GameObject.h"



using namespace GameEngineProject;
using namespace std;

Scene::Scene() :
	_state(RUN),
	_name("")
{

}


Scene::~Scene()
{

}


void Scene::Awake()
{
	for (int i = 0; i < _gameObjects.size(); ++i)
	{
		_gameObjects[i]->Awake();
	}
}

void Scene::Start()
{
	for (int i = 0; i < _gameObjects.size(); ++i)
	{
		_gameObjects[i]->Start();
	}
}

void Scene::Update()
{
	for (int i = 0; i < _gameObjects.size(); ++i)
	{
		_gameObjects[i]->Update();
	}
}

void Scene::Pause()
{
	_state = PAUSE;
}

void Scene::Stop()
{
	_state = STOP;
}

void Scene::Shutdown()
{
	for (int i = 0; i < _gameObjects.size(); ++i)
	{
		_gameObjects[i]->Shutdown();
		delete(_gameObjects[i]);
	}
	Clear();
}

void Scene::Clear()
{
	_gameObjects.clear();
}

const string& Scene::GetName()
{
	return _name;
}

void Scene::SetName(const string& name)
{
	_name = name;
}

void Scene::AddObject(GameObject* obj)
{
	_gameObjects.push_back(obj);
}

bool Scene::RemoveGameObject(GameObject* obj)
{
	return false;
}

bool Scene::RemoveGameObject(const string& name)
{
	return false;
}

bool Scene::RemoveGameObjects(const Tag& tag)
{
	return false;
}

vector<GameObject*>& Scene::GetObjects()
{
	return _gameObjects;
}

vector<GameObject*>& Scene::FindObjects(const Tag& tag)
{
	
}

vector<GameObject*>& Scene::FindObjects(Component const * const component)
{

}

bool Scene::FindObject(GameObject const * const obj)
{
	false;
}

GameObject*  Scene::FindObject(const string& name)
{
	for (int i = 0; i < _gameObjects.size(); ++i)
	{
		if (_gameObjects[i]->GetName() == name)
		{
			return _gameObjects[i];
		}
		return nullptr;
	}
}