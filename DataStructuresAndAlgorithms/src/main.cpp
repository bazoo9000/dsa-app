#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::BinarySearchTree<int> tree;

	tree.Insert(3);
	tree.Insert(1);
	tree.Insert(2);
	tree.Insert(4);
	tree.Insert(5);

	for(auto it = tree.CreateLevelorderIterator(); !it->IsAtEnd(); it->Next())
	{
		std::cout << it->GetCurrent() << " ";
	}

	std::cout << std::endl;

	return 0;
}