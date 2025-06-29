#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::DynamicArray<int> arr(5);
	arr.Add(1);
	arr.Add(2);
	arr.Add(3);
	arr.Add(4);
	arr.Add(5);

	auto it = arr.CreateReverseIterator();
	for (auto it2 = (*it + 3); !it2->IsAtBegin(); (*it2)++)
	{
		std::cout << it2->GetCurrent() << " ";
	}
	std::cout << std::endl;
	for (auto it3 = (*it)++; !it3->IsAtBegin(); it3->Prev())
	{
		std::cout << it3->GetCurrent() << " ";
	}
	it->Reset();
	std::cout << std::endl;
	for (auto it4 = ++(*it); !it4->IsAtBegin(); ++(*it4))
	{
		std::cout << it4->GetCurrent() << " ";
	}
	it->Reset();

	return 0;
}