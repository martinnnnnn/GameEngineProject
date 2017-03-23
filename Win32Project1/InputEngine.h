#pragma once

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>



namespace GameEngineProject
{

	class InputEngine
	{
	public:
		InputEngine();
		InputEngine(const InputEngine&);
		~InputEngine();

		bool Initialize(HINSTANCE, HWND, int, int);
		void Shutdown();
		bool Update();

		bool IsEscapePressed();
		bool IsRightArrowPressed();
		bool IsLeftArrowPressed();
		bool IsUpArrowPressed();
		bool IsDownArrowPressed();
		void GetMouseLocation(int&, int&);
		void GetMouseDelta(int&, int&);
	private:
		bool ReadKeyboard();
		bool ReadMouse();
		void ProcessInput();

	private:
		IDirectInput8* _directInput;
		IDirectInputDevice8* _keyboard;
		IDirectInputDevice8* _mouse;
		unsigned char _keyboardState[256];
		DIMOUSESTATE _mouseState;

		int _screenWidth, _screenHeight;
		int _mouseX, _mouseY;
		int _mouseDeltaX, _mouseDeltaY;
	};
}

