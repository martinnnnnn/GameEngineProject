#pragma once

#include <string>

namespace GameEngineProject
{

	typedef std::string Tag;


	class Utils
	{
	public:


		inline static const int GetHash(const std::string className)
		{
			unsigned long hash = 5381;
			int c;
			const char* name = className.c_str();
			while (c = *name++) {
				hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
			}

			return (int)hash;
		}
	};
}