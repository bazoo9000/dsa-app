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

	ds::BinaryTree<int> tree;
	tree.Insert(5);
	tree.Insert(3);
	tree.Insert(7);

	for (auto it = tree.CreateIterator(); !it->IsAtEnd(); it->Next())
	{
		std::cout << it->GetCurrent() << " ";
	}

	return 0;
}