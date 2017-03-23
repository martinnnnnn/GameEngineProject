#pragma once


#include "Factoriable.h"

#include <string>

namespace GameEngineProject
{
	class Script : public Factoriable
	{
	public:
		Script() {}
		virtual ~Script() = 0;
		virtual bool operator==(const Factoriable &) = 0;
		virtual bool operator==(const std::string &) = 0;
		virtual void Swap(const Factoriable &) = 0;
		virtual void Reset() = 0;
		virtual void Awake() = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;

	private:

		std::string _name;
	};

}
