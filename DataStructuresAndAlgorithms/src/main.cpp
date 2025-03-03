#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::CircularLinkedList<int> list;
	list.Append(1);
	list.Append(2);
	list.Append(3);
	list.Append(4);

	list.Prepend(0);

	list.Print();

	list.DeleteFirst();
	list.DeleteAt(3);
	list.Delete(1);

	return 0;
}