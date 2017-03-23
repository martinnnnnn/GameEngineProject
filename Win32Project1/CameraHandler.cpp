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

	_leftTurnSpeed = 0.0f;
	_rightTurnSpeed = 0.0f;

}


CameraHandler::CameraHandler(const CameraHandler& other)
{
	_positionX = other._positionX;
	_positionY = other._positionY;
	_positionZ = other._positionZ;

	_rotationX = other._rotationX;
	_rotationY = other._rotationY;
	_rotationZ = other._rotationZ;

	_leftTurnSpeed = other._leftTurnSpeed;
	_rightTurnSpeed = other._rightTurnSpeed;
	_viewMatrix = other._viewMatrix;
}


CameraHandler::~CameraHandler()
{
}

void CameraHandler::HandleInput()
{
	//InputEngine inputs = GameEngine::instance().GetInputEngine();
	//
	//int deltaX, deltaY;
	//inputs.GetMouseDelta(deltaX, deltaY);

	//float lookRightRads = deltaX * CAMERA_ANGULAR_SPEED_DEG * DEG_TO_RAD;
	//float lookUpRads = deltaY * CAMERA_ANGULAR_SPEED_DEG * DEG_TO_RAD;


	//// Limit the aim vector in such a way that the 'up' vector never drops below the horizon:
	//static const float zenithMinDeclination = DEG_TO_RAD * MIN_UPWARDS_TILT_DEG;
	//static const float zenithMaxDeclination = DEG_TO_RAD * (180.0f - MIN_UPWARDS_TILT_DEG);

	//const float currentDeclination = std::acosf(camera.aim_.y_);  ///< declination from vertical y-axis
	//const float requestedDeclination = currentDeclination - lookUpRads;

	//// Clamp the up/down rotation to at most the min/max zenith:
	//if (requestedDeclination < zenithMinDeclination)
	//	lookUpRads = currentDeclination - zenithMinDeclination;
	//else if (requestedDeclination > zenithMaxDeclination)
	//	lookUpRads = currentDeclination - zenithMaxDeclination;

	//// Rotate both the "aim" vector and the "up" vector ccw by 
	//// lookUpRads radians within their common plane -- which should 
	//// also contain the y-axis:  (i.e. no diagonal tilt allowed!)
	//camera.aim_.rotateAboutAxis(camera.right_, lookUpRads);
	//camera.up_.rotateAboutAxis(camera.right_, lookUpRads);
	//ASSERT_ORTHONORMAL(camera.aim_, camera.up_, camera.right_);

	//// Rotate both the "aim" and the "up" vector ccw about the vertical y-axis:
	//// (again, this keeps the y-axis in their common plane, and disallows diagonal tilt)
	//camera.aim_.rotateAboutAxis(Y_AXIS, -lookRightRads);
	//camera.up_.rotateAboutAxis(Y_AXIS, -lookRightRads);
	//camera.updateRightAxis();


	bool keydown = false;
	float time = GameEngine::instance().GetTimer().GetTime();
	keydown = GameEngine::instance().GetInputEngine().IsLeftArrowPressed();
	if (keydown)
	{
		_leftTurnSpeed += time * 0.00001f;

		if (_leftTurnSpeed > (time * 0.0002f))
		{
			_leftTurnSpeed = time * 0.0002f;
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

	_rotationY -= _leftTurnSpeed;
	if (_rotationY < 0.0f)
	{
		_rotationY += 360.0f;
	}

	keydown = GameEngine::instance().GetInputEngine().IsRightArrowPressed();
	if (keydown)
	{
		_rightTurnSpeed += time * 0.00001f;

		if (_rightTurnSpeed >(time * 0.0002f))
		{
			_rightTurnSpeed = time * 0.0002f;
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