#include "Includes.h"
using namespace std;

int main(int argc, char* argv[])
{
	ds::LinkedList<int> l;

	l.Append(1);
	l.Append(2);

	l.Print();

	//ds::Graph<int> graph(ds::GraphRepresentOption::LIST);
	
	return 0;
}