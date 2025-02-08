#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::DoublyLinkedList<int> list;

	list.Append(1);
	list.Append(2);
	list.Prepend(3);
	list.Prepend(4);
	list.Prepend(5);

	list.InsertAt(6, 5);

	for (int i = 0; i < list.GetSize(); i++)
	{
		std::cout << list.GetElementAt(i) << " ";
	}
	std::cout << std::endl;

	list.Print();

	/*list.Delete(5);
	list.Delete(6);
	list.Delete(3);
	list.Print();*/

	list.DeleteAt(5);
	list.DeleteAt(0);
	list.DeleteAt(2);

	list.Print();

	ds::DoublyLinkedList<int> list2;
	list2 = list;

	list.Print();
	list2.Print();

	ds::DoublyLinkedList<int> list3;
	list3 = std::move(list);

	list.Print();
	list3.Print();

	return 0;
}