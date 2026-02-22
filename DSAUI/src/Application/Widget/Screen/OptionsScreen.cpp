#include "../../../dsa_pch.h"

#include "OptionsScreen.h"

OptionsScreen::OptionsScreen(std::string id)
	: Screen(id)
{
}

OptionsScreen::~OptionsScreen()
{
}

void OptionsScreen::InitScreen(CacheManager<std::string>& textCache, CacheManager<Widget*>& widgetCache)
{
	Button* but = new Button("but_back", *textCache.Get("GUI.BACK"));
	but->SetCallback(
		[]()
		{
			LOG_GUI_DEBUG("Closing");
			Screen::signalCloseApp();
		}
	);
	but->MoveTo({ 100.0f, 100.0f });
	but->ScaleTo({ 50.0f, 20.0f });

	TextLabel* title = new TextLabel("title", *textCache.Get("GUI.OPTIONS"), FONT_H1);
	title->MoveTo({ 520.0f, 10.0f });
	title->ScaleTo({ 300.0f, 300.0f });

	std::vector<Widget*> widgets1 = { but, title };
	m_MainPanel = new Panel("panel_options", widgets1);
}
