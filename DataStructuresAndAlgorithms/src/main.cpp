#include "DataStructures/DynamicArray.h"
#include "Includes.h"
using namespace std;

int main(int argc, char* argv[])
{
	ds::DynamicArray<int> arr;

	arr.Add(1);
	arr.Add(2);
	arr.Add(3);
	arr.Add(4);
	std::cout << arr[3] << std::endl;	

	arr.Print();

	//ds::Graph<int> graph(ds::GraphRepresentOption::LIST);
	
	return 0;
}