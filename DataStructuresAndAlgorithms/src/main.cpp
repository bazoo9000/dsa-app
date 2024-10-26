#include "Includes.h"
using namespace std;

int main(int argc, char* argv[])
{
	ds::DynamicArray<int> *da = new ds::DynamicArray<int>();
	da->Add(1);
	da->Add(2);
	da->Add(3);

	ds::DynamicArray<int> da2(std::move(*da));
	delete da;
	da2.Print();

	//ds::Graph<int> graph(ds::GraphRepresentOption::LIST);
	
	return 0;
}