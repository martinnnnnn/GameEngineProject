#pragma once

#include "factoriable.h"

namespace GameEngineProject
{
	class Component
	{
	public:
		Component() {}
		virtual ~Component() {}
		//virtual bool operator==(const Factoriable &) = 0;
		//virtual void Swap(const Factoriable &) = 0;
		//virtual void Reset() = 0;
	};
}

