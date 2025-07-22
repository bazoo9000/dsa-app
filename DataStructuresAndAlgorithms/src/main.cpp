#include "Includes.h"

struct Test
{
	int a;
	int b;

	bool operator==(const Test& other) const
	{
		return a == other.a && b == other.b;
	}
};

namespace ds
{
	template<>
	struct HashFunction<Test>
	{
		uint32_t operator()(const Test& key) const
		{
			return static_cast<uint32_t>(key.a + key.b + key.a * key.b);
		}
	};
}

int main(int argc, char* argv[])
{
	ds::HashMap<int, int> map(10);

	map.Insert(1, 100);
	map.Insert(2, 200);
	map.Insert(2, 201);
	map.Insert(11, 100);
	map.Insert(51, 151);
	map.Insert(13, 300);

	auto vals = map.GetValues();
	for (auto it = vals.CreateIterator(); !it->IsAtEnd(); it->Next())
	{
		std::cout << it->GetCurrent() << " ";
	}
	std::cout << std::endl;

	auto keys = map.GetKeys();
	for (auto it = keys.CreateIterator(); !it->IsAtEnd(); it->Next())
	{
		std::cout << it->GetCurrent() << " ";
	}
	std::cout << std::endl;

	ds::HashMap<const char*, int> map1(10);
	map1.Insert("one", 1);

	ds::HashMap<Test, int> map2(10);
	map2.Insert({ 1, 2 }, 100);

	return 0;
}