#pragma once

// TODO : LOAD/SAVE
// TODO : TIME




#include <vector>
#include <string>




namespace GameEngineProject
{

	class GameObject;
	class PhysicsEngine;
	class GraphicsEngine;
	class InputEngine;
	class Scene;
	class SceneManager;
	class ObjectManager;
	class Timer;

	class GameEngine
	{

	public:

		void Initialize();
		void Awake();
		void Start();
		void Run();
		void Pause();
		void Unpause();
		void Restart();
		void Quit();


	private:
		void UpdateInput();
		void UpdateLogic();
		void UpdatePhysics();
		void Render(float);

	public:
		~GameEngine();
		static GameEngine& instance()
		{
			static GameEngine *instance = new GameEngine();
			return *instance;
		}
		const SceneManager & GetSceneManager();
		const GraphicsEngine & GetGraphicsEngine();
		const PhysicsEngine & GetPhysicsEngine();
		const InputEngine & GetInputEngine();
		const ObjectManager & GetObjectManager();


	private:
		bool _quit;
		bool _pause;
		Timer* _timer;
		SceneManager* _sceneManager;
		ObjectManager* _objectManager;
		GraphicsEngine* _graphicsEngine;
		PhysicsEngine* _physicsEngine;
		InputEngine* _inputsEngine;

	private:
		GameEngine();
		GameEngine(GameEngine const&) = delete;
		void operator=(GameEngine const&) = delete;
	};

}
