#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::DynamicArray<int> arr;
	arr.Add(4);
	arr.Add(1);
	arr.Add(3);
	arr.Add(2);

	alg::Searcher<int>::SetSearchStrategy(new alg::LinearSearch<int>());

	std::cout << alg::Searcher<int>::Search(1, &arr) << std::endl;
	std::cout << alg::Searcher<int>::Search(5, &arr) << std::endl;

	alg::Searcher<int>::SetSearchStrategy(new alg::BinarySearch<int>());

	std::cout << alg::Searcher<int>::Search(1, &arr) << std::endl;

	alg::Sorter<int>::SetSortStrategy(new alg::BubbleSort<int>());
	alg::Sorter<int>::Sort(&arr);

	std::cout << alg::Searcher<int>::Search(1, &arr) << std::endl;
	std::cout << alg::Searcher<int>::Search(5, &arr) << std::endl;

	return 0;
}