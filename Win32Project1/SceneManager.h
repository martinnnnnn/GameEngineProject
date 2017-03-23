#pragma once

// TODO MESSAGE SYSTEM
// TODO SORTING SYSTEM


#include <vector>
#include "boost\shared_ptr.hpp"

namespace GameEngineProject
{
	class Scene;
	class GameObject;

	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

	public:
		void Awake();
		void Start();
		void Update();
		void Pause();
		void Stop();
		void Shutdown();
		void Clear();

	public:
		void AddScene(Scene*);
		bool RemoveScene(const std::string&);
		const std::vector<Scene*>& GetScenes();
		Scene* GetScene(const std::string&);
		Scene* FindObject(GameObject*);
		Scene* FindObject(const std::string&);
		boost::shared_ptr<std::vector<GameObject*>> GetGameObjects();




	private:

		std::vector<Scene*> _scenes;
	};

}

