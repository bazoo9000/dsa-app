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

	Canvas* canvas = new Canvas("canvas");
	canvas->MoveTo({ 100.0f, 200.0f });
	canvas->ScaleTo({ 450.0f, 450.0f });
	canvas->SetBgColor(IM_COL32(125, 255, 125, 255));

	Circle* circle = new Circle({ 100, 100 }, 50.0f, 5.0f);
	Circle* circle1 = new Circle({ 200, 111 }, 31.0f);

	Line* line = new Line(circle->GetOrigin(), circle1->GetOrigin(), 2.0f);

	canvas->AddDrawableShape(circle);
	canvas->AddDrawableShape(circle1);
	canvas->AddDrawableShape(line);

	circle1->SetColor(IM_COL32(125, 50, 25, 255));

	std::vector<Widget*> widgets = { but, title, opt, canvas };
	m_MainPanel = new Panel("panel_main", widgets);
	m_MainPanel->ScaleTo({ 400.0f, 400.0f });
	m_MainPanel->MoveTo({ 10.0f, 20.0f });
}

void MainMenu::RunMenu()
{
	// nimic
}
