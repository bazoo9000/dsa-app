#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::BinaryTree<int> tree;

	tree.Insert(1);
	tree.Insert(2);
	tree.Insert(3);
	tree.Insert(4);
	tree.Insert(5);

	// tree.Print(ds::BinaryTree<int>::PrintOrderType::PREORDER);
	// tree.Print(ds::BinaryTree<int>::PrintOrderType::INORDER);
	// tree.Print(ds::BinaryTree<int>::PrintOrderType::POSTORDER);
	// tree.Print(ds::BinaryTree<int>::PrintOrderType::LEVELORDER);

	tree.Print();
	
	for(auto it = tree.CreateLevelorderIterator(); !it->IsAtEnd(); it->Next())
	{
		std::cout << it->GetCurrent() << " ";
	}

	std::cout << std::endl;

	return 0;
}