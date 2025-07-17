#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::BinaryTree<int> tree;
	tree.Insert(1);
	tree.Insert(2);
	tree.Insert(3);
	tree.Insert(4);
	tree.Insert(5);

	for (auto it = tree.CreateIterator(); !it->IsAtEnd(); it->Next())
	{
		std::cout << *(*it) << " ";
	}

	tree.Delete(1);

	for (auto it = tree.CreateIterator(); !it->IsAtEnd(); it->Next())
	{
		std::cout << *(*it) << " ";
	}

	tree.Delete(2);
	tree.Delete(3);
	tree.Delete(4);
	tree.Delete(6);
	tree.Delete(5);
	tree.Delete(7);

	// SEPARATOR //

	ds::BinarySearchTree<int> bst;
	bst.Insert(2);
	bst.Insert(2);
	bst.Insert(5);
	bst.Insert(1);
	bst.Insert(3);
	bst.Insert(4);

	for (auto it = bst.CreateIterator(); !it->IsAtEnd(); it->Next())
	{
		std::cout << *(*it) << " ";
	}

	bst.Delete(2);

	for (auto it = bst.CreateIterator(); !it->IsAtEnd(); it->Next())
	{
		std::cout << *(*it) << " ";
	}

	bst.Delete(1);
	bst.Delete(2);
	bst.Delete(3);
	bst.Delete(4);
	bst.Delete(6);
	bst.Delete(5);
	bst.Delete(7);

	return 0;
}