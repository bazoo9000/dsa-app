#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::Array<int, 5> d1;
	ds::BinarySearchTree<int> d2;
	ds::BinaryTree<int> d3;
	ds::CircularLinkedList<int> d4;
	ds::DoublyLinkedList<int> d5;
	ds::DynamicArray<int> d6(5);
	ds::DynamicMatrix<int> d7(0, 5, 5);
	ds::HashMap<char, int> d8;
	ds::LinkedList<int> d9;
	ds::Matrix<int, 5, 5> d10(0);
	ds::Queue<int> d11;
	ds::Stack<int> d12;

	d1.DebugDetails();
	d2.DebugDetails();
	d3.DebugDetails();
	d4.DebugDetails();
	d5.DebugDetails();
	d6.DebugDetails();
	d7.DebugDetails();
	d8.DebugDetails();
	d9.DebugDetails();
	d10.DebugDetails();
	d11.DebugDetails();
	d12.DebugDetails();

	return 0;
}