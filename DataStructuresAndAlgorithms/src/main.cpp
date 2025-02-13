#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::DoublyLinkedList<int> list;
	list.Append(1);
	list.Append(2);
	list.Append(3);
	list.Prepend(0);

	printf("%d\n", list.GetElementAt(0));

	list.DeleteAt(0);

	list.Print();
	return 0;
}