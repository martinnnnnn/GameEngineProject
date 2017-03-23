

#include "GameEngine.h"

#include <iostream>

using namespace std;
using namespace GameEngineProject;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	bool result;


	GameEngine::instance().Initialize();

	return 0;
}