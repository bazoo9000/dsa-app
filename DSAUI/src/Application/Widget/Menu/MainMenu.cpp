#include "../../../dsa_pch.h"

#include "MainMenu.h"

MainMenu::MainMenu(std::string id)
	: Menu(id)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::InitMenu(CacheManager<std::string>& textCache, CacheManager<Widget*>& widgetCache)
{
	Button* but = new Button("but_back", *textCache.Get("GUI.BACK"));
	but->SetCallback(
		[]()
		{
			LOG_GUI_DEBUG("Closing");
			Menu::signalCloseApp();
		}
	);
	but->MoveTo({ 100.0f, 100.0f });
	but->ScaleTo({ 50.0f, 20.0f });

	Button* opt = new Button("but_options", *textCache.Get("GUI.OPTIONS"));
	opt->SetCallback(
		[]()
		{
			Menu::signalChangeMenu("menu_options");
		}
	);
	opt->MoveTo({ 100.0f, 130.0f });
	opt->ScaleTo({ 50.0f, 20.0f });

	TextLabel* title = new TextLabel("title", *textCache.Get("GUI.WELCOME"), FONT_H1);
	title->MoveTo({ 520.0f, 10.0f });
	title->ScaleTo({ 300.0f, 300.0f });

	TextLabel* test = new TextLabel("test", *textCache.Get("GUI.NU_EXISTA"));
	test->MoveTo({ 100.0f, 200.0f });

	std::vector<Widget*> widgets = { but, title, opt, test };
	m_MainPanel = new Panel("panel_main", widgets);
	m_MainPanel->ScaleTo({ 400.0f, 400.0f });
	m_MainPanel->MoveTo({ 10.0f, 20.0f });
}

void MainMenu::RunMenu()
{
	// nimic
}
