

#include "GameEngine.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "GraphicsEngine.h"
#include "D3DHandler.h"

#include <iostream>

using namespace std;
using namespace GameEngineProject;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{


	GameEngine::instance().Initialize();

	GameObject*const obj = GameEngine::instance().GetObjectManager().GetFreeGameObject();
	obj->SetName("hello");
	obj->SetTransform(GameEngine::instance().GetObjectManager().GetFreeTransfrom());
	obj->SetGraphicsComponent(GameEngine::instance().GetObjectManager().GetFreeGraphicsComponent());
	vector<wchar_t*> vector;
	vector.push_back(L"Data/Texture/stone01.tga");
	vector.push_back(L"Data/Texture/bump01.tga");
	D3DHandler*const D3Dhandler = GameEngine::instance().GetGraphicsEngine().GetD3DHandler();
	obj->GetGraphicsComponent()->Initialize(D3Dhandler->GetDevice(), D3Dhandler->GetDeviceContext(), vector,"Data/Model/cube2.txt", BUMP_SHADER);
	obj->GetTransform()->SetPosition(0,0,0);
	Scene* scene1 = new Scene();
	scene1->AddObject(obj);
	GameEngine::instance().GetSceneManager().AddScene(scene1);

	GameEngine::instance().Awake();
	GameEngine::instance().Start();
	GameEngine::instance().Run();
	return 0;
}