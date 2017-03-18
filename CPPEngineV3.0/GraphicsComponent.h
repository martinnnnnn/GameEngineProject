#pragma once



#include "Component.h"


namespace GameEngineProject
{
	class GraphicsComponent : public Component
	{
	public:
		GraphicsComponent();
		GraphicsComponent(const GraphicsComponent &);
		virtual ~GraphicsComponent();
		void operator=(const GraphicsComponent &);
		virtual bool operator==(const GraphicsComponent &);
		virtual void Swap(const GraphicsComponent &);
		virtual void Reset();

		
	};

}

