#pragma once

#include <unordered_map>
#include <memory>
#include <iostream>

namespace
{
	template <typename T>
	std::uintptr_t get_unique_type_id()
	{
		static const int placeholder;
		return reinterpret_cast<std::uintptr_t>(&placeholder);
	}

	struct base_type {};

	template <typename T>
	struct derived_type : public base_type
	{
		T value;
	};
}

namespace ay
{
	class lazy_tuple;
}

namespace std
{
	template <typename T>
	T& get(ay::lazy_tuple& container);
}

namespace ay
{
	class lazy_tuple
	{
	public:

		template <typename T>
		friend T& std::get(lazy_tuple&);

		/* TODO
		
		lazy_tuple<T...>(T...)
		lazy_tuple<T...>(std::tuple<T...>)
		insert<T>(T&&)
		emplace<T...>(T&&...)
		contains<T>()
		get<T>()
		size()
		empty()
		clear()
		swap(lazy_tuple&)
		merge(lazy_tuple&)

		*/

	private:
		std::unordered_map<std::uintptr_t, std::unique_ptr<base_type>> m_storage;
	};
}

template <typename T>
T& std::get(ay::lazy_tuple& tuple)
{
	auto id = get_unique_type_id<T>();

	auto found = tuple.m_storage.find(id);
	if (found == tuple.m_storage.end())
	{
		found = tuple.m_storage.try_emplace(id, std::make_unique<derived_type<T>>()).first;
	}

	return static_cast<derived_type<T>*>(found->second.get())->value;
}

