#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::BinaryTree<int> tree;
	tree.Insert(1);
	tree.Insert(2);
	tree.Insert(3);
	tree.Insert(4);
	tree.Insert(5);

	for (auto it = tree.CreateInorderIterator(); !it->IsAtEnd(); it->Next())
	{
		std::cout << it->GetCurrent() << " ";
	}

	printf("\n");

	for (auto it = tree.CreateInorderReverseIterator(); !it->IsAtBegin(); it->Prev())
	{
		std::cout << it->GetCurrent() << " ";
	}

	printf("\n");

	for (auto it = tree.CreatePostorderIterator(); !it->IsAtEnd(); it->Next())
	{
		std::cout << it->GetCurrent() << " ";
	}

	printf("\n");

	for (auto it = tree.CreatePostorderReverseIterator(); !it->IsAtBegin(); it->Prev())
	{
		std::cout << it->GetCurrent() << " ";
	}

	printf("\n");

	for (auto it = tree.CreateLevelorderIterator(); !it->IsAtEnd(); it->Next())
	{
		std::cout << it->GetCurrent() << " ";
	}

	printf("\n");

	for (auto it = tree.CreateLevelorderReverseIterator(); !it->IsAtBegin(); it->Prev())
	{
		std::cout << it->GetCurrent() << " ";
	}

	return 0;
}