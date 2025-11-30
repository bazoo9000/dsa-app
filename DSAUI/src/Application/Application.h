#pragma once

#include "Window/Window.h"
#include "I18N/I18N.h"
#include "I18N/I18NFactory.h"
#include "Widget/Widget.h"

class Application
{
public:
	Application();
	~Application();

public:
	void Run();

private:
	void initImGUI(const char* glslVersion);
	void initGLAD();
	void destroyImGUI();

private:
	inline void imguiCreateFrame();
	inline void render(GLFWwindow* window, ImVec2 windowSize);

private:
	Window* m_Window = nullptr;
	I18N* m_I18N = nullptr;
	std::map<std::string, Widget*> m_Cache;
};