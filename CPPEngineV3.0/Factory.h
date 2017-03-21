#pragma once

#include "Factoriable.h"
#include <type_traits>
#include <boost\shared_array.hpp>

namespace GameEngineProject
{

	template <typename T, int size>
	class Factory
	{
		static_assert(std::is_base_of<Factoriable, T>::value, "T must be derived from Factoriable");
		static_assert(size > 0, "size must be > 0");

	public:
		T* const GetNew()
		{
			T* newT = nullptr;
			if (_current < size)
			{
				newT = &(_items[_current]);
				++_current;
			}
			return newT;
		}

		bool Free(T* const t)
		{
			for (int i = 0; i < _current)
			{
				if (_items[i] == *t)
				{
					_items[i].Reset();
					_items[i].Swap(_items[_current - 1]);
					--_current;
					return true;
				}
			}
			return false;
		}

		bool IsEmpty()
		{
			return (_current >= size);
		}

		boost::shared_array<T> GetAll(int & length)
		{
			length = _current;
			boost::shared_array<T> usedItems(new t[_current]);
			for (int i = 0; i < _current; ++i)
			{
				usedItems[i] = _items[i];
			}
			return usedItems;
		}

	private:
		int _current;
		T _items[size];
	};


}












