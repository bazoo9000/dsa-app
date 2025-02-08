#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::DynamicArray<int> arr(5);

	arr.Add(2);
	arr.Add(3);
	arr.Add(5);
	arr.Add(1);
	arr.Add(4);

	arr.Print();

	alg::Sorter<int>::SetSortStrategy(new alg::SelectionSort<int>());
	alg::Sorter<int>::Sort(&arr);

	arr.Print();

	alg::Sorter<int>::Sort(&arr, [](int a, int b)->bool { return a > b; });

	arr.Print();

	return 0;
}