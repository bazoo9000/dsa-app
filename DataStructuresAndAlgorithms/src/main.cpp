#include "Includes.h"
using namespace std;

int main(int argc, char* argv[])
{
	ds::Queue<int> q;
	q.Enqueue(1);
	q.Enqueue(2);
	q.Enqueue(3);

	ds::Stack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);

	q.Print();
	s.Print();
	//ds::Graph<int> graph(ds::GraphRepresentOption::LIST);
	
	return 0;
}