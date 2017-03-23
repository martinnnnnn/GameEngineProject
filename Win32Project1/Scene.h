#pragma once

// TODO MESSAGE SYSTEM


#include "Utils.h"

#include <string>
#include <vector>


using namespace GameEngineProject::Utils;

namespace GameEngineProject
{
	class GameObject;
	class Component;

	typedef enum
	{
		RUN,
		PAUSE,
		STOP
	} SceneState;



	class Scene
	{
	public:

		Scene();
		~Scene();

		void Awake();
		void Start();
		void Update();
		void Pause();
		// asks the scene to stop, meaning it will be shutdown at the beginning of next frame
		void Stop();
		// does the actual shutdown of the scene
		void Shutdown();
		void Clear();


	public:
		const std::string& GetName();
		void SetName(const std::string&);

	public:
		void AddObject(GameObject*);
		bool RemoveGameObject(GameObject*);
		bool RemoveGameObject(const std::string&);
		bool RemoveGameObjects(const Tag&);
		std::vector<GameObject*>& GetObjects();
		std::vector<GameObject*>& FindObjects(const Tag&);
		std::vector<GameObject*>& FindObjects(Component const * const);
		bool FindObject(GameObject const * const);
		GameObject* FindObject(const std::string&);


	private:

		SceneState _state;
		std::string _name;
		std::vector<GameObject*> _gameObjects;
	};
}



