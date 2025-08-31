#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::DynamicArray<int> arr;
	arr.Add(1);
	arr.Add(2);
	arr.Add(3);
	arr.Add(4);
	arr.Add(5);

	alg::Searcher<int>::SetSearchStrategy(new alg::BinarySearch<int>());
	int idx1 = alg::Searcher<int>::Search(4, &arr);
	int idx2 = alg::Searcher<int>::Search(6, &arr);

	std::cout << "Index of 4: " << idx1 << std::endl;
	std::cout << "Index of 6: " << (idx2 == NOT_FOUND ? "Not found" : "Found") << std::endl;

	return 0;
}