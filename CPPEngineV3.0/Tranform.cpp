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

void Transform::operator=(const Transform & transform)
{

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

}

void Transform::SetPosition(const Vector::vec3f & vec)
{

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
