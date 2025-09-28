#include "DSACore.h"

int main(int argc, char* argv[])
{
	LOG_TRACE("This is a trace");
	LOG_DEBUG("This is a debug");
	LOG_INFO("This is an info");
	LOG_WARN("This is a warn");
	LOG_ERROR("This is an errpr");
	LOG_FATAL("This is a fatal");

	LOG_GUI_TRACE("This is a GUI trace");
	LOG_GUI_DEBUG("This is a GUI debug");
	LOG_GUI_INFO("This is an GUI info");
	LOG_GUI_WARN("This is a GUI warn");
	LOG_GUI_ERROR("This is an GUI errpr");
	LOG_GUI_FATAL("This is a GUI fatal");

	return 0;
}