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
		void operator=(const Transform &);
		virtual bool operator==(const Transform &);
		virtual void Swap(const Transform &);
		virtual void Reset();

	public:
		void SetPosition(const Vector::vec3f &);
		void SetRotation(const Vector::vec3f &);
		void SetScale(const Vector::vec3f &);

		const Vector::vec3f & Position();
		const Vector::vec3f & Rotation();
		const Vector::vec3f & Scale();




	private:

		Vector::vec3f position;
		Vector::vec3f rotation;
		Vector::vec3f scale;
	};

}

