#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::DynamicArray<int> arr;
	arr.Add(5);
	arr.Add(2);
	arr.Add(1);
	arr.Add(4);
	arr.Add(3);

	alg::Sorter<int>::SetSortStrategy(new alg::InsertionSort<int>());
	alg::Sorter<int>::Sort(&arr);

	for (auto it = arr.CreateIterator(); !it->IsAtEnd(); it->Next())
	{
		std::cout << **it << " ";
	}

	return 0;
}