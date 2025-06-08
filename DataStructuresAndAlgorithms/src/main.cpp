#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::DynamicArray<int> arr(5);
	arr.Add(3);
	arr.Add(5);
	arr.Add(2);
	arr.Add(4);
	arr.Add(1);

	for (auto it = arr.CreateIterator(); !it->IsAtEnd(); it->Next())
	{
		std::cout << it->GetCurrent() << " ";
	}

	alg::Searcher<int>::SetSearchStrategy(new alg::BinarySearch<int>());
	alg::Searcher<int>::Search(3, &arr);
	return 0;
}