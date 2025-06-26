#include "DataStructures/DynamicArray.h"
#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::DynamicArray<int> arr(5);
	arr.Add(1);
	arr.Add(2);
	arr.Add(3);
	arr.Add(4);
	arr.Add(5);

	auto it = arr.CreateIterator();
	for (auto it2 = (*it + 3); !it2->IsAtEnd(); it2->Next())
	{
		std::cout << it2->GetCurrent() << " ";
	}
	std::cout << std::endl;
	for (; !it->IsAtEnd(); it->Next())
	{
		std::cout << it->GetCurrent() << " ";
	}
	std::cout << std::endl;

	return 0;
}