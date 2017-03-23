#pragma once


#define WIN32_LEAN_AND_MEAN

#include <windows.h>

namespace GameEngineProject
{

	class D3DHandler;
	class CameraHandler;
	class ShaderManager;
	class LightManager;

	const bool FULL_SCREEN = true;
	const bool VSYNC_ENABLED = true;
	const float SCREEN_DEPTH = 1000.0f;
	const float SCREEN_NEAR = 0.1f;

	class GraphicsEngine
	{

	public:
		GraphicsEngine();
		GraphicsEngine(const GraphicsEngine &);
		~GraphicsEngine();

		bool Initialize();
		void Shutdown();
		void Update();
		bool Render(float);

		void PostWinMessage(WCHAR*);

	private:
		void InitializeWindows(int&, int&);
		void ShutdownWindows();

	private:
		LPCWSTR m_applicationName;
		HINSTANCE m_hinstance;
		HWND m_hwnd;

		D3DHandler* m_Direct3D;
		ShaderManager* m_ShaderManager;
		LightManager* m_Light;

		CameraHandler* m_Camera;
	};

}
