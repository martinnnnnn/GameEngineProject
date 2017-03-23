#include "Tranform.h"


using namespace GameEngineProject;

Transform::Transform()
{

}

Transform::Transform(const Transform & transform)
{

}

Transform::~Transform()
{

}

const Transform & Transform::operator=(const Transform & transform)
{
	_position = transform._position;
	_rotation = transform._rotation;
	_scale = transform._scale;

	return *this;
}

bool Transform::operator==(const Transform & transform)
{
	return false;
}

void Transform::Swap(const Transform & transform)
{

}

void Transform::Reset()
{
	_position.Reset();
	_rotation.Reset();
	_scale.x = 1;
	_scale.y = 1;
	_scale.z = 1;
}

void Transform::SetPosition(float x, float y, float z)
{
	_position = Vector::vec3f(x,y,y);
}

void Transform::SetRotation(const Vector::vec3f & vec)
{

}

void Transform::SetScale(const Vector::vec3f & vec)
{

}

const Vector::vec3f & Transform::Position()
{
	return _position;
}

const Vector::vec3f & Transform::Rotation()
{
	return _rotation;
}

const Vector::vec3f & Transform::Scale()
{
	return _scale;
}
