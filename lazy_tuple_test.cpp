#include "lazy_tuple.h"
#include <cassert>

int main()
{
	ay::lazy_tuple x;
	std::get<int>(x) = 10;

	assert(10 == std::get<int>(x));

	std::get<int>(x) = 20;

	assert(20 == std::get<int>(x));

	auto& v = std::get<std::vector<float>>(x);

	v.push_back(100.f);

	assert(100.f == std::get<std::vector<float>>(x)[0]);
}