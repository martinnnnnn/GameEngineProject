#pragma once

// TODO : LOAD/SAVE
// TODO : TIME




#include <vector>
#include <string>
#include <Windows.h>



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
	class FpsCounter;
	class CpuCounter;

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

		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	private:
		void UpdateInput();
		void UpdateLogic();
		void UpdatePhysics();
		bool Render(float);

	public:
		~GameEngine();
		static GameEngine& instance()
		{
			static GameEngine *instance = new GameEngine();
			return *instance;
		}
		SceneManager & GetSceneManager();
		GraphicsEngine & GetGraphicsEngine();
		PhysicsEngine & GetPhysicsEngine();
		InputEngine & GetInputEngine();
		ObjectManager & GetObjectManager();
		Timer & GetTimer();
		FpsCounter & GetFpsCounter();
		CpuCounter & GetCpuCounter();

	private:
		bool _quit;
		bool _pause;
		Timer* _timer;
		FpsCounter* _fpsCounter;
		CpuCounter* _cpuCounter;
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

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
	{
		switch (umessage)
		{
			// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return GameEngine::instance().MessageHandler(hwnd, umessage, wparam, lparam);
		}
		}
	}


}
