#include "GameEngine.h"


#include "SceneManager.h"
#include "Timer.h"
#include "InputEngine.h"
#include "GraphicsEngine.h"
#include "ObjectManager.h"
#include "FpsCounter.h"
#include "CpuCounter.h"

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
	_inputsEngine = new InputEngine;
	if (!_inputsEngine)
	{
		return;
	}


	_graphicsEngine = new GraphicsEngine;
	if (!_graphicsEngine)
	{
		return;
	}
	_graphicsEngine->Initialize();
	_timer = new Timer;
	if (!_timer)
	{
		return;
	}
	_timer->Initialize();
	_objectManager = new ObjectManager;
	if (!_objectManager)
	{
		return;
	}
	_sceneManager = new SceneManager;
	if (!_sceneManager)
	{
		return;
	}

	_fpsCounter = new FpsCounter;
	if (!_fpsCounter)
	{
		return;
	}
	_fpsCounter->Initialize();

	_cpuCounter = new CpuCounter;
	if (!_cpuCounter)
	{
		return;
	}
	_cpuCounter->Initialize();
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
	const int TICKS_PER_SECOND = 30;
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
			while (GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP)
			{
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

void GameEngine::UpdateInput()
{
	_inputsEngine->Update();
}

void GameEngine::UpdateLogic()
{
	_fpsCounter->Update();
	_cpuCounter->Update();
	_sceneManager->Update();
}

void GameEngine::UpdatePhysics()
{

}

bool GameEngine::Render(float interpolation)
{
	
	_graphicsEngine->Update();
	return _graphicsEngine->Render(interpolation);
}

SceneManager & GameEngine::GetSceneManager()
{
	return *_sceneManager;
}

GraphicsEngine & GameEngine::GetGraphicsEngine()
{
	return *_graphicsEngine;
}

PhysicsEngine & GameEngine::GetPhysicsEngine()
{
	return *_physicsEngine;
}

InputEngine & GameEngine::GetInputEngine()
{
	return *_inputsEngine;
}

ObjectManager & GameEngine::GetObjectManager()
{
	return *_objectManager;
}

Timer & const GameEngineProject::GameEngine::GetTimer()
{
	return *_timer;
}

FpsCounter & GameEngineProject::GameEngine::GetFpsCounter()
{
	return *_fpsCounter;
}

CpuCounter & GameEngineProject::GameEngine::GetCpuCounter()
{
	return *_cpuCounter;
}


