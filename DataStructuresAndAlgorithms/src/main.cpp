#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::DynamicArray<int> arr;
	arr.Add(4);
	arr.Add(1);
	arr.Add(3);
	arr.Add(2);

	arr.Print();

	alg::Sorter<int>::SetSortStrategy(new alg::InsertionSort<int>());
	alg::Sorter<int>::SetSortStrategy(new alg::SelectionSort<int>());
	alg::Sorter<int>::SetSortStrategy(new alg::BubbleSort<int>());
	alg::Sorter<int>::Sort(&arr);

	arr.Print();

	return 0;
}