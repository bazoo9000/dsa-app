#include "../../dsa_pch.h"

#include "Window.h"
#include "Logger/Logger.h"

static void glfwCustomError(int errorCode, const char* description)
{
	int level = 0; // 0 = info, 1 = warn, 2 = error, 3 = fatal
	switch (errorCode)
	{
	case GLFW_NOT_INITIALIZED:
	case GLFW_OUT_OF_MEMORY:
	case GLFW_API_UNAVAILABLE:
	case GLFW_PLATFORM_ERROR: 
		level = 3; break;

	case GLFW_NO_CURRENT_CONTEXT:
	case GLFW_INVALID_ENUM:
	case GLFW_INVALID_VALUE:
	case GLFW_VERSION_UNAVAILABLE:
		level = 2; break;

	case GLFW_FORMAT_UNAVAILABLE:
		level = 1; break;
	}

	const char* fmt = "(GLFW-%d) %s";
	switch (level)
	{
	case 0: LOG_GUI_INFO(fmt, errorCode, description); break;
	case 1: LOG_GUI_WARN(fmt, errorCode, description); break;
	case 2: LOG_GUI_ERROR(fmt, errorCode, description); break;
	case 3: LOG_GUI_FATAL(fmt, errorCode, description); exit(1);
	}
}

Window::Window(std::string title, int width, int height, bool vsync)
	: m_Title(title), m_Width(width), m_Height(height)
{
	glfwSetErrorCallback(glfwCustomError);
	if (!glfwInit()) { exit(1); }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!m_Window)
	{
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(vsync);

	LOG_GUI_DEBUG("GLFW Window initialized and created succesfully");
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();

	LOG_GUI_DEBUG("GLFW Window DESTROYED succesfully");
}

ImVec2 Window::GetWindowSize()
{
	glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
	return { (float)m_Width, (float)m_Height };
}
