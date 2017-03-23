#pragma once

#include "Vector.h"
#include "Component.h"

namespace GameEngineProject
{
	class Transform : public Component
	{

	public:
		Transform();
		Transform(const Transform &);
		virtual ~Transform();
		const Transform & operator=(const Transform &);
		virtual bool operator==(const Transform &);
		virtual void Swap(const Transform &);
		virtual void Reset();

	public:
		void SetPosition(float,float,float);
		void SetRotation(const Vector::vec3f &);
		void SetScale(const Vector::vec3f &);

		const Vector::vec3f & Position();
		const Vector::vec3f & Rotation();
		const Vector::vec3f & Scale();




	private:

		Vector::vec3f _position;
		Vector::vec3f _rotation;
		Vector::vec3f _scale;
	};

}

