#include "CameraHandler.h"

#include "GameEngine.h"
#include "InputEngine.h"
#include "Timer.h"

using namespace GameEngineProject;
using namespace DirectX;

CameraHandler::CameraHandler()
{
	_positionX = 0.0f;
	_positionY = 0.0f;
	_positionZ = 0.0f;

	_rotationX = 0.0f;
	_rotationY = 0.0f;
	_rotationZ = 0.0f;

	_rotationY = 0.0f;
	_leftTurnSpeed = 0.0f;
	_rightTurnSpeed = 0.0f;
}


CameraHandler::CameraHandler(const CameraHandler& other)
{
}


CameraHandler::~CameraHandler()
{
}

void GameEngineProject::CameraHandler::HandlerInput()
{
	bool keydown = false;
	float time = GameEngine::instance().GetTimer()->GetTime();
	keydown = GameEngine::instance().GetInputEngine()->IsLeftArrowPressed();
	if (keydown)
	{
		_leftTurnSpeed += time * 0.01f;

		if (_leftTurnSpeed > (time * 0.15f))
		{
			_leftTurnSpeed = time * 0.15f;
		}
	}
	else
	{
		_leftTurnSpeed -= time* 0.005f;

		if (_leftTurnSpeed < 0.0f)
		{
			_leftTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	_rotationY -= _leftTurnSpeed;
	if (_rotationY < 0.0f)
	{
		_rotationY += 360.0f;
	}

	keydown = GameEngine::instance().GetInputEngine()->IsLeftArrowPressed();
	if (keydown)
	{
		_rightTurnSpeed += time * 0.01f;

		if (_rightTurnSpeed >(time * 0.15f))
		{
			_rightTurnSpeed = time * 0.15f;
		}
	}
	else
	{
		_rightTurnSpeed -= time* 0.005f;

		if (_rightTurnSpeed < 0.0f)
		{
			_rightTurnSpeed = 0.0f;
		}
	}

	// Update the rotation using the turning speed.
	_rotationY += _rightTurnSpeed;
	if (_rotationY > 360.0f)
	{
		_rotationY -= 360.0f;
	}

	SetRotation(0.0f, _rotationY, 0.0f);
}

void CameraHandler::SetPosition(float x, float y, float z)
{
	_positionX = x;
	_positionY = y;
	_positionZ = z;
	return;
}


void CameraHandler::SetRotation(float x, float y, float z)
{
	_rotationX = x;
	_rotationY = y;
	_rotationZ = z;
	return;
}


XMFLOAT3 CameraHandler::GetPosition()
{
	return XMFLOAT3(_positionX, _positionY, _positionZ);
}


XMFLOAT3 CameraHandler::GetRotation()
{
	return XMFLOAT3(_rotationX, _rotationY, _rotationZ);
}


void CameraHandler::Render()
{
	XMFLOAT3 up, position, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Load it into a XMVECTOR structure.
	upVector = XMLoadFloat3(&up);

	// Setup the position of the camera in the world.
	position.x = _positionX;
	position.y = _positionY;
	position.z = _positionZ;

	// Load it into a XMVECTOR structure.
	positionVector = XMLoadFloat3(&position);

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Load it into a XMVECTOR structure.
	lookAtVector = XMLoadFloat3(&lookAt);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = _rotationX * 0.0174532925f;
	yaw = _rotationY * 0.0174532925f;
	roll = _rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// Finally create the view matrix from the three updated vectors.
	_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;
}


void CameraHandler::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = _viewMatrix;
	return;
}