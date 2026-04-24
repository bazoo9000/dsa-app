#include "../../../dsa_pch.h"

#include "MainMenu.h"

#include "../Button.h"
#include "../TextLabel.h"
#include "../Canvas.h"

#include "../Shape/DrawableLine.h"
#include "../Shape/InteractableCircle.h"

#include "Logger/Logger.h"

MainMenu::MainMenu(std::string id)
	: Menu(id)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::InitMenu()
{
	auto tokens = signalRequestTokens({
		"GUI.BACK", "GUI.OPTIONS", "GUI.WELCOME"
		});

	Button* but = new Button("but_back", tokens["GUI.BACK"]);
	but->SetCallback(
		[]()
		{
			LOG_GUI_DEBUG("Closing");
			Menu::signalCloseApp();
		}
	);
	but->MoveTo({ 100.0f, 100.0f });
	but->ScaleTo({ 50.0f, 20.0f });

	Button* opt = new Button("but_options", tokens["GUI.OPTIONS"]);
	opt->SetCallback(
		[]()
		{
			Menu::signalChangeMenu("menu_options");
		}
	);
	opt->MoveTo({ 100.0f, 130.0f });
	opt->ScaleTo({ 50.0f, 20.0f });

	TextLabel* title = new TextLabel("title", tokens["GUI.WELCOME"], FONT_H1);
	title->MoveTo({ 520.0f, 10.0f });
	title->ScaleTo({ 300.0f, 300.0f });

	Canvas* canvas = new Canvas("canvas");
	canvas->MoveTo({ 100.0f, 200.0f });
	canvas->ScaleTo({ 450.0f, 450.0f });
	canvas->SetBgColor(IM_COL32(125, 255, 125, 255));

	// TODO: rethink how to set both global and local origin, this looks horrible
	InteractableCircle* circle = new InteractableCircle({ 100.0f, 100.0f }, 50.0f);
	InteractableCircle* circle1 = new InteractableCircle({ 200.0f, 111.0f }, 31.0f);

	DrawableLine* line = new DrawableLine(
		circle->GetOrigin(),
		circle1->GetOrigin(),
		2.0f
	);


	// The black circle
	{
		circle->SetOnNothingCallback([circle]()
			{
				circle->SetFilled(false);
			}
		);

		circle->SetOnHoverCallback([circle]()
			{
				circle->SetFilled(true);
			}
		);

		circle->SetOnClickCallback([circle, line]()
			{
				ImGuiIO& io = ImGui::GetIO();
				ImVec2 pos = io.MousePos - circle->GetGlobalOrigin();
				circle->SetOrigin(pos);

				line->SetOrigin(pos);
			}
		);

		circle->SetOnHoldCallback([circle, line]()
			{
				ImGuiIO& io = ImGui::GetIO();
				ImVec2 pos = io.MousePos - circle->GetGlobalOrigin();
				circle->SetOrigin(pos);

				line->SetOrigin(pos);
			}
		);
	}

	// The brown circle
	{
		circle1->SetOnNothingCallback([circle1]()
			{
				circle1->SetFilled(false);
			}
		);

		circle1->SetOnHoverCallback([circle1]()
			{
				circle1->SetFilled(true);
			}
		);

		circle1->SetOnClickCallback([circle1, line]()
			{
				ImGuiIO& io = ImGui::GetIO();
				ImVec2 pos = io.MousePos - circle1->GetGlobalOrigin();
				circle1->SetOrigin(pos);

				line->SetEnd(pos);
			}
		);

		circle1->SetOnHoldCallback([circle1, line]()
			{
				ImGuiIO& io = ImGui::GetIO();
				ImVec2 pos = io.MousePos - circle1->GetGlobalOrigin();
				circle1->SetOrigin(pos);
				
				line->SetEnd(pos);
			}
		);
	}

	canvas->AddDrawableShape(circle1);
	canvas->AddDrawableShape(circle);
	canvas->AddDrawableShape(line);

	circle1->SetColor(IM_COL32(125, 50, 25, 255));

	std::vector<Widget*> widgets = { but, title, opt, canvas };
	m_MainPanel = new Panel("panel_main", widgets);
	m_MainPanel->ScaleTo({ 400.0f, 400.0f });
	m_MainPanel->MoveTo({ 10.0f, 20.0f });
}

void MainMenu::RunMenu()
{
	Canvas* canvas = (Canvas*)m_MainPanel->GetWidget("canvas");
	canvas->DoInteractions();
}
