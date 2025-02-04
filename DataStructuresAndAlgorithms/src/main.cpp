#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::Array<int, 5> a;
	a.Add(1);
	a.Add(2);
	a.Add(3);

	for (auto it = a.CreateIterator(); !it->IsAtEnd(); ++(*it))
	{
		//it->Reset();
		**it = 2;
		std::cout << **it << " ";
	}

	return 0;
}