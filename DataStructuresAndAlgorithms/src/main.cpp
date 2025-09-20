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
	ds::HashMap<int, int> d8(10);
	ds::LinkedList<int> d9;
	ds::Matrix<int, 5, 5> d10(0);
	ds::Queue<int> d11;
	ds::Stack<int> d12;

	d1.Add(1);
	d1.Add(3);
	d1.Add(2);

	d2.Insert(2);
	d2.Insert(3);
	d2.Insert(1);

	d3.Insert(2);
	d3.Insert(3);
	d3.Insert(1);

	d4.Append(1);
	d4.Append(2);
	d4.Append(3);

	d5.Append(2);
	d5.Append(3);
	d5.Append(1);

	d6.Add(1);
	d6.Add(2);
	d6.Add(3);

	d7.Insert(1, 0, 0);
	d7.Insert(2, 1, 1);
	d7.Insert(3, 2, 2);

	d8.Insert(1, 1);
	d8.Insert(11, 2);
	d8.Insert(2, 3);

	d9.Append(2);
	d9.Append(1);
	d9.Append(3);
	
	d10.Insert(3, 0, 0);
	d10.Insert(2, 1, 1);
	d10.Insert(1, 2, 2);

	d11.Enqueue(3);
	d11.Enqueue(2);
	d11.Enqueue(1);

	d12.Push(1);
	d12.Push(2);
	d12.Push(3);

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