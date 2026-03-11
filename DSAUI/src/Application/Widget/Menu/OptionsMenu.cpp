#include "../../../dsa_pch.h"

#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(std::string id)
	: Menu(id)
{
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::InitMenu(CacheManager<std::string>& textCache, CacheManager<Widget*>& widgetCache)
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

	TextLabel* title = new TextLabel("title", *textCache.Get("GUI.OPTIONS"), FONT_H1);
	title->MoveTo({ 520.0f, 10.0f });
	title->ScaleTo({ 300.0f, 300.0f });

	std::vector<std::string> items = { "ceva", "altceva", "complet altceva" };
	RadioButton* radio = new RadioButton("radio_test", items);
	radio->MoveTo({ 100.0f, 300.0f });

	std::string str = ("Ai selectat " + radio->GetSelected());
	TextLabel* select = new TextLabel("text_select", str, FONT_H4);
	select->MoveTo({ 100.0f, 250.0f });

	std::vector<Widget*> widgets1 = { but, title, radio, select };
	m_MainPanel = new Panel("panel_options", widgets1);
}

void OptionsMenu::RunMenu()
{
	// im gonna get executed for writing it like this
	RadioButton* radio = (RadioButton*)m_MainPanel->GetWidget("radio_test");
	std::string str = ("Ai selectat " + radio->GetSelected());
	
	TextLabel* text = (TextLabel*)m_MainPanel->GetWidget("text_select");
	text->ModifyText(str);
}
