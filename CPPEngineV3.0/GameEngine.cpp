#include "GameEngine.h"


#include "SceneManager.h"
#include "Timer.h"
#include "InputEngine.h"
#include "GraphicsEngine.h"

using namespace GameEngineProject;

GameEngine::GameEngine() :
	_quit(false),
	_timer(),
	_sceneManager(),
	_objectManager(),
	_graphicsEngine(),
	_physicsEngine(),
	_inputsEngine()
{

}

GameEngine::~GameEngine()
{

}

void GameEngine::Initialize()
{
	_timer->Initialize();
}


void GameEngine::Awake()
{
	_sceneManager->Awake();
}

void GameEngine::Start()
{
	_sceneManager->Start();
}

void GameEngine::Run()
{
	const int TICKS_PER_SECOND = 25;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 5;

	MSG msg;
	bool result;
	_timer->Frame();

	DWORD next_game_tick = GetTickCount();
	int loops;
	float interpolation;
	
	bool game_is_running = true;
	while (game_is_running) {


		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			game_is_running = false;
		}
		else
		{
			loops = 0;
			while (GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP) {
				UpdateInput();
				UpdateLogic();

				next_game_tick += SKIP_TICKS;
				loops++;
			}

			interpolation = float(GetTickCount() + SKIP_TICKS - next_game_tick)
				/ float(SKIP_TICKS);
			result = Render(interpolation);
			if (!result)
			{
				_graphicsEngine->PostWinMessage(L"Frame Processing Failed");
				game_is_running = false;
			}
		}
		if (_inputsEngine->IsEscapePressed() == true)
		{
			game_is_running = false;
		}
	}
}


void GameEngine::Pause()
{
	_pause = true;
}

void GameEngine::Unpause()
{
	_pause = false;
}

void GameEngine::Restart()
{

}

void GameEngine::Quit()
{
	_quit = true;
}

LRESULT CALLBACK GameEngine::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

SceneManager * const GameEngine::GetSceneManager()
{
	return _sceneManager;
}

GraphicsEngine * const GameEngine::GetGraphicsEngine()
{
	return _graphicsEngine;
}

PhysicsEngine * const GameEngine::GetPhysicsEngine()
{
	return _physicsEngine;
}

InputEngine * const GameEngine::GetInputEngine()
{
	return _inputsEngine;
}

ObjectManager * const GameEngine::GetObjectManager()
{
	return _objectManager;
}

Timer * const GameEngineProject::GameEngine::GetTimer()
{
	return _timer;
}


void GameEngine::UpdateInput()
{

}

void GameEngine::UpdateLogic()
{
	_sceneManager->Update();
}

void GameEngine::UpdatePhysics()
{

}

bool GameEngine::Render(float interpolation)
{

}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
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