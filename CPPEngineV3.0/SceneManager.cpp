#include "SceneManager.h"

#include "Scene.h"

using namespace GameEngineProject;
using namespace std;

SceneManager::SceneManager()
{

}


SceneManager::~SceneManager()
{

}

void SceneManager::Awake()
{
	for (int i = 0; i < _scenes.size(); ++i)
	{
		_scenes[i]->Awake();
	}
}

void SceneManager::Start()
{
	for (int i = 0; i < _scenes.size(); ++i)
	{
		_scenes[i]->Start();
	}
}

void SceneManager::Update()
{
	for (int i = 0; i < _scenes.size(); ++i)
	{
		_scenes[i]->Update();
	}
}

void SceneManager::Pause()
{
	for (int i = 0; i < _scenes.size(); ++i)
	{
		_scenes[i]->Pause();
	}
}

void SceneManager::Stop()
{
	for (int i = 0; i < _scenes.size(); ++i)
	{
		_scenes[i]->Stop();
	}
}

void SceneManager::Shutdown()
{
	for (int i = 0; i < _scenes.size(); ++i)
	{
		_scenes[i]->Shutdown();
	}
}

void SceneManager::Clear()
{
	for (int i = 0; i < _scenes.size(); ++i)
	{
		_scenes[i]->Clear();
	}
}

void SceneManager::AddScene(Scene* scene)
{
	_scenes.push_back(scene);
}

bool SceneManager::RemoveScene(const string& name)
{
	for (int i = 0; i < _scenes.size(); ++i)
	{
		if (_scenes[i]->GetName() == name)
		{
			_scenes[i]->Stop();
			return true;
		}
	}
	return false;
}

const vector<Scene*>& SceneManager::GetScenes()
{
	return _scenes;
}

Scene* SceneManager::GetScene(const string& name)
{
	for (int i = 0; i < _scenes.size(); ++i)
	{
		if (_scenes[i]->GetName() == name)
		{
			return _scenes[i];
		}
	}
	return nullptr;
}

Scene* SceneManager::FindObject(GameObject* obj)
{
	return nullptr;
}

Scene* SceneManager::FindObject(const string& name)
{
	return nullptr;
}

