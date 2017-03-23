#include "GraphicsEngine.h"


#include "GameEngine.h"
#include "GameObject.h"
#include "ObjectManager.h"
#include "D3DHandler.h"
#include "CameraHandler.h"
#include "ObjectManager.h"
#include "Tranform.h"
#include "GraphicsComponent.h"
#include "ShaderManager.h"
#include "LightManager.h"
#include "TextHandler.h"
#include "InputEngine.h"
#include "FpsCounter.h"
#include "CpuCounter.h"
#include "InputEngine.h"
#include "Timer.h"

#include <boost/shared_array.hpp>
#include <boost/range.hpp>
#include <vector>
#include <string>

using namespace GameEngineProject;
using namespace std;

GraphicsEngine::GraphicsEngine()
{
	m_Direct3D = 0;
	m_Camera = 0;
	m_Light = 0;
	m_ShaderManager = 0;
	m_Text = 0;
}


GraphicsEngine::GraphicsEngine(const GraphicsEngine& other)
{
}


GraphicsEngine::~GraphicsEngine()
{
}

bool GraphicsEngine::Initialize()
{
	int screenWidth, screenHeight;
	bool result;


	screenWidth = 0;
	screenHeight = 0;

	InitializeWindows(screenWidth, screenHeight);

	m_Direct3D = new D3DHandler;
	if (!m_Direct3D)
	{
		return false;
	}
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, m_hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	GameEngine::instance().GetInputEngine().Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight);


	m_Camera = new CameraHandler;
	if (!m_Camera)
	{
		return false;
	}
	m_Camera->Render();

	m_Light = new LightManager;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.05f, 0.05f, 0.05f, 1.f);
	m_Light->SetDiffuseColor(1.f, 1.f, 1.f, 1.f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	m_ShaderManager = new ShaderManager();
	if (!m_ShaderManager)
	{
		return false;
	}
	result = m_ShaderManager->Initialize(m_Direct3D->GetDevice(), m_hwnd);
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
		return false;
	}

	XMMATRIX viewMatrix;
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);


	// Create the text object.
	m_Text = new TextHandler;
	if (!m_Text)
	{
		return false;
	}
	result = m_Text->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), m_hwnd, screenWidth, screenHeight, viewMatrix);
	if (!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsEngine::Shutdown()
{
	
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	ShutdownWindows();

	return;
}

void GraphicsEngine::Update()
{
	bool result;

	m_Camera->SetPosition(0.0f, 0.0f, -5.0);
	m_Camera->HandleInput();

	int mouseX, mouseY;
	GameEngine::instance().GetInputEngine().GetMouseLocation(mouseX, mouseY);
	// Set the location of the mouse.
	result = m_Text->SetMousePosition(mouseX, mouseY, m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return;
	}

	// Set the frames per second.
	result = m_Text->SetFps(GameEngine::instance().GetFpsCounter().GetFps(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return;
	}

	// Set the cpu usage.
	result = m_Text->SetCpu(GameEngine::instance().GetCpuCounter().GetCpuPercentage(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return;
	}
	
	std::string txt ("R:" + to_string(GameEngine::instance().GetTimer().GetTime()));
	
	result = m_Text->SetText(txt.c_str(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		return;
	}
}

D3DHandler * const GameEngineProject::GraphicsEngine::GetD3DHandler()
{
	return m_Direct3D;
}

void GameEngineProject::GraphicsEngine::PostWinMessage(WCHAR * message)
{
	MessageBox(m_hwnd, message, L"Error", MB_OK);
}

bool GraphicsEngine::Render(float interpolation)
{
	
	bool result;
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;


	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_Camera->Render();

	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	m_Direct3D->TurnOnAlphaBlending();
	result = m_Text->Render(m_Direct3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	m_Direct3D->TurnOffAlphaBlending();

	int length = 0;
	boost::shared_array<GameObject> _object = GameEngine::instance().GetObjectManager().GetAllGameObject(length);

	for (int i = 0; i < length; ++i)
	{
		Transform* transform = _object[i].GetTransform();
		GraphicsComponent* graphics = _object[i].GetGraphicsComponent();

		Vector::vec3f pos = transform->Position();
		graphics->Render(m_Direct3D->GetDeviceContext());
		worldMatrix = XMMatrixTranslation(pos.x, pos.y, pos.z);

		switch (graphics->GetShaderType())
		{
		case (LIGHT_SHADER):
			result = m_ShaderManager->RenderLightShader(m_Direct3D->GetDeviceContext(), graphics->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				graphics->GetTextures()[0], m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
			break;
		case (BUMP_SHADER):
			result = m_ShaderManager->RenderBumpMapShader(m_Direct3D->GetDeviceContext(), graphics->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				graphics->GetTextures()[0], graphics->GetTextures()[1], m_Light->GetDirection(), m_Light->GetDiffuseColor());
			break;
		}

		if (!result)
		{
			return false;
		}
	}
	m_Direct3D->EndScene();

	return true;
}



void GraphicsEngine::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"Engine";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(false);

	return;
}

void GraphicsEngine::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.

	return;
}

