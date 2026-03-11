#pragma once

#include "IAppReceiver.h"

#include "Window/Window.h"
#include "I18N/I18N.h"
#include "I18N/I18NFactory.h"

#include "Widget/Widget.h"
#include "Widget/Menu/Menu.h"

#include "CacheManager/CacheManager.h"

class Application : public IAppReceiver
{
public:
	Application();
	~Application();

public:
	void Run();
	virtual void ChangeMenu(std::string id) override;
	virtual void Close() override;

private:
	void initMenus();
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

	Menu* m_CrtMenu;
	std::unordered_map<std::string, Menu*> m_Menus; // id -> menu

	CacheManager<std::string> m_TextCache;
	CacheManager<Widget*> m_WidgetCache;
};