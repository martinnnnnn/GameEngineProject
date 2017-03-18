#include "GameEngine.h"


#include "SceneManager.h"
#include "Timer.h"


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
	
	_timer->Frame();

	DWORD next_game_tick = GetTickCount();
	int loops;
	float interpolation;

	bool game_is_running = true;
	while (game_is_running) {

		loops = 0;
		while (GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP) {
			UpdateInput();
			UpdateLogic();

			next_game_tick += SKIP_TICKS;
			loops++;
		}

		interpolation = float(GetTickCount() + SKIP_TICKS - next_game_tick)
			/ float(SKIP_TICKS);
		Render(interpolation);
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

const SceneManager & GameEngine::GetSceneManager()
{
	return *_sceneManager;
}

const GraphicsEngine & GameEngine::GetGraphicsEngine()
{
	return *_graphicsEngine;
}

const PhysicsEngine & GameEngine::GetPhysicsEngine()
{
	return *_physicsEngine;
}

const InputEngine &GameEngine::GetInputEngine()
{
	return *_inputsEngine;
}

const ObjectManager & GameEngine::GetObjectManager()
{
	return *_objectManager;
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

void GameEngine::Render(float interpolation)
{

}