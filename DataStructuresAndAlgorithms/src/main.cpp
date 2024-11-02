#include "Includes.h"
using namespace std;

int main(int argc, char* argv[])
{
	ds::LinkedList<int> l;

	l.Append(1);
	l.Append(2);
	l.Append(4);
	l.InsertAt(3, 2);

	std::cout << l.GetElementAt(2) << " " << l.GetFirst() << " " << l.GetLast();
	l.Print();
	//ds::Graph<int> graph(ds::GraphRepresentOption::LIST);
	
	return 0;
}