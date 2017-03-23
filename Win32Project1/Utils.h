#pragma once

#include <string>
#include <strstream>
#include <sstream>

namespace GameEngineProject
{

	namespace Utils
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

		template<class T>
		std::string ToString(const T& val)
		{
			std::stringstream strm;
			strm << val;
			return strm.str();
		}
	}
}