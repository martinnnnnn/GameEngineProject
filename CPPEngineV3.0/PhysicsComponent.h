#pragma once


#include "Component.h"


namespace GameEngineProject
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent();
		PhysicsComponent(const PhysicsComponent &);
		virtual ~PhysicsComponent();
		void operator=(const PhysicsComponent  &);

	public:
		virtual bool operator==(const PhysicsComponent  &);
		virtual void Swap(const PhysicsComponent  &);
		virtual void Reset();
	};

}

