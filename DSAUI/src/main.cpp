#include "dsa_pch.h"
#include "DSACore.h"

#include "Application/Application.h"

#include "Application/CacheManager/CacheManager.h"

int main()
{
	/*Application app;

	app.Run();*/

	CacheManager<int> cache(5);

	cache.Cache("one", 1);
	cache.Cache("two", 2);
	cache.Cache("tre", 3);
	cache.Cache("for", 4);
	cache.Cache("fiv", 5);

	std::vector<std::string> keys = { "one", "two", "tre", "for", "fiv", "six" };

	for (auto key = keys.begin(); key != keys.end(); key++)
	{
		if (cache.Get(*key) != nullptr)
			printf("%s => %d\n", key->c_str(), *cache.Get(*key));
	}

	cache.Cache("six", 6);

	for (auto key = keys.rbegin(); key != keys.rend(); key++)
	{
		if (cache.Get(*key) != nullptr)
			printf("%s => %d\n", key->c_str(), *cache.Get(*key));
	}

	cache.Cache("sev", 7);
	keys.push_back("sev");

	for (auto key = keys.begin(); key != keys.end(); key++)
	{
		if (cache.Get(*key) != nullptr)
			printf("%s => %d\n", key->c_str(), *cache.Get(*key));
	}

	cache.Cache("sev", 9);

	return 0;
}