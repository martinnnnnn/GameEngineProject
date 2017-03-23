#pragma once

#include <directxmath.h>


namespace GameEngineProject
{

	class CameraHandler
	{
	public:
		CameraHandler();
		CameraHandler(const CameraHandler&);
		~CameraHandler();

		
		void HandlerInput();
		
		
		void SetPosition(float, float, float);
		void SetRotation(float, float, float);

		DirectX::XMFLOAT3 GetPosition();
		DirectX::XMFLOAT3 GetRotation();

		void Render();
		void GetViewMatrix(DirectX::XMMATRIX&);

	private:
		float _positionX, _positionY, _positionZ;
		float _rotationX, _rotationY, _rotationZ;
		float _leftTurnSpeed, _rightTurnSpeed;
		DirectX::XMMATRIX _viewMatrix;
	};
}

