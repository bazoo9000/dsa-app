#include "Includes.h"
#include "Logger/Logger.h"

int main(int argc, char* argv[])
{
	LOG_TRACE("%d", 34);
	LOG_DEBUG("%d", 5);
	LOG_INFO("%d", 33);
	LOG_WARN("%d", 54);
	LOG_ERROR("%d", 84);
	LOG_FATAL("%d, %d", 94, 34);
	return 0;
}