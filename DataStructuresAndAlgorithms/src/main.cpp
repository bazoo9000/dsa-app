#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::Stack<int> s1;

	s1.Push(1);
	s1.Push(2);
	s1.Push(3);

	std::cout << s1.GetTop();

	ds::Stack<int> s2;
	s2 = s1;

	std::cout << s2.GetTop();

	ds::Stack<int> s3;
	s3 = std::move(s2);

	std::cout << s3.GetTop();

	s3.Print();
	s2.Print();

	//ds::Graph<int> graph(ds::GraphRepresentOption::LIST);
	
	return 0;
}