#include "../../../dsa_pch.h"

#include "OptionsMenu.h"

#include "MenuManger/OptionsMenuManager/OptionsMenuManager.h"

#include "../Button.h"
#include "../TextLabel.h"

#include "Logger/Logger.h"

OptionsMenu::OptionsMenu(std::string id)
	: Menu(id)
{
}

OptionsMenu::~OptionsMenu()
{
}

void OptionsMenu::InitMenu()
{
	auto tokens = signalRequestTokens({
		"GUI.BACK", "GUI.OPTIONS", "GUI.NOT_EXIST"
		});

	Button* but = new Button("but_back", tokens["GUI.BACK"]);
	but->SetCallback(
		[]()
		{
			Menu::signalChangeMenu("menu_main");
		}
	);
	but->MoveTo({ 100.0f, 100.0f });
	but->ScaleTo({ 50.0f, 20.0f });

	Button* but2 = new Button("but_disable", "Disable");
	but2->SetCallback(
		[but]()
		{
			static bool disabled = false;

			if (disabled)
			{
				but->Enable();
			}
			else
			{
				but->Disable();
			}

			disabled = !disabled;
		}
	);
	but2->MoveTo({ 100.0f, 75.0f });
	but2->ScaleTo({ 50.0f, 20.0f });

	Button* but3 = new Button("but_hide", "Hide");
	but3->SetCallback(
		[but]()
		{
			static bool hidden = false;

			if (hidden)
			{
				but->Show();
			}
			else
			{
				but->Hide();
			}

			hidden = !hidden;
		}
	);
	but3->MoveTo({ 100.0f, 50.0f });
	but3->ScaleTo({ 50.0f, 20.0f });

	TextLabel* title = new TextLabel("title", tokens["GUI.OPTIONS"], FONT_H1);
	title->MoveTo({ 520.0f, 10.0f });
	title->ScaleTo({ 300.0f, 300.0f });

	Panel* optPanel = OptionsMenuManager::GetOptionsPanel();
	optPanel->MoveTo({ 100.0f, 200.0f });
	optPanel->ScaleTo({ 800.0f, 500.0f });
	optPanel->HideBorder();

	setAllWidgets({ title, but, but2, but3, optPanel });
}

void OptionsMenu::RunMenu()
{
}
