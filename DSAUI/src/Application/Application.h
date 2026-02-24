#pragma once

#include "IAppReceiver.h"

#include "Window/Window.h"
#include "I18N/I18N.h"
#include "I18N/I18NFactory.h"

#include "Widget/Widget.h"
#include "Widget/Screen/Screen.h"

#include "CacheManager/CacheManager.h"

class Application : public IAppReceiver
{
public:
	Application();
	~Application();

public:
	void Run();
	virtual void ChangeScreen(std::string id) override;
	virtual void Close() override;

private:
	void initScreens();
	void initImGUI(const char* glslVersion);
	void initGLAD();
	void destroyImGUI();

private:
	inline void imguiCreateFrame();
	inline void render(GLFWwindow* window, ImVec2 windowSize);

private:
	bool m_ShouldClose = false;
	Window* m_Window = nullptr;
	I18N* m_I18N = nullptr;

	Screen* m_CrtScreen;
	std::unordered_map<std::string, Screen*> m_Screens; // id -> screen

	CacheManager<std::string> m_TextCache;
	CacheManager<Widget*> m_WidgetCache;
};