#include "../../dsa_pch.h"

#include "LearnMenu.h"

#include "../Widget/Button.h"
#include "../Widget/CustomWidget.h"
#include "../Widget/TreeNode.h"
#include "../Widget/TextLabel.h"
#include "../Widget/Tab.h"
#include "../Widget/Tooltip.h"

#include "MenuManger/LearnMenuManager/LearnMenuManager.h"

#include "../Time.h"

#include "Logger/Logger.h"

LearnMenu::LearnMenu(std::string id)
	: Menu(id)
{
}

LearnMenu::~LearnMenu()
{
}

void LearnMenu::InitMenu()
{
	auto tokens = MenuAppSignaler::SignalRequestTokens({
		"GUI.BACK", "GUI.OPTIONS"
		});

    Tab* tab = new Tab("tab_test");

    // TODO: covert the custom widget to TreeNode
    // TODO: add selectable widget decorator, after i fix one giant problem about the decorators
    CustomWidget* custom1 = new CustomWidget("custom_header_select");
    custom1->AddCustomScript([tab]()
        {
            if (ImGui::TreeNode(MenuAppSignaler::SignalRequestToken("GUI.DATA_STRUCTURES").c_str()))
            {
                static auto titles = LearnMenuManager::GetAllTitles();
                static std::unordered_map<std::string, std::string> keys;
                for (auto& title : titles)
                {
                    bool exists = (keys.find(title.first) != keys.end());
                    bool selected = exists && tab->GetTabItemSelected(keys[title.first]);
                    ImGui::Selectable(MenuAppSignaler::SignalRequestToken(title.second).c_str(), &selected);

                    if (!exists && selected)
                    {
                        Panel* panel = LearnMenuManager::CreateLearnPanel(title.first);
                        tab->AddTabItem(panel, MenuAppSignaler::SignalRequestToken(title.second).c_str(), true);
                        keys[title.first] = panel->GetId();
                    }

                    if (exists)
                    {
                        tab->SetTabItemSelected(keys[title.first], selected);
                    }
                }

                ImGui::TreePop();
            }
        }
    );

    ImVec2 screenSize = MenuAppSignaler::SignalGetWindowSize();
    float fifthScreenX = (int)screenSize.x / 5; // at a fith of screen

    Button* but = new Button("but_back", tokens["GUI.BACK"]);
    but->SetCallback([]()
        {
            MenuAppSignaler::SignalChangeMenu("menu_main");
        }
    );
    but->MoveTo({ 10.0f, screenSize.y - 35.0f });
    but->ScaleTo({ 50.0f, 20.0f });

    Tooltip* tooltip = new Tooltip(but, "This is a tooltip");
    tooltip->SetDelay(TooltipDelay::None);

    TextLabel* label1 = new TextLabel("text_test_1", "Label1");
    label1->SetAutoPositioning(true);
    TextLabel* label2 = new TextLabel("text_test_2", "Label2");
    label2->SetAutoPositioning(true);
    TreeNode* node = new TreeNode("treenode_test", "Tree Title");
    node->AddWidget(label1);
    node->AddWidget(label2);
    node->SetAutoPositioning(true);

    Panel* leftPanel = new Panel("panel_left");
    leftPanel->ScaleTo({ fifthScreenX, screenSize.y });
    leftPanel->MoveTo({ 0.0f, 0.0f });
    leftPanel->AddWidget(custom1);
    leftPanel->AddWidget(node);
    leftPanel->AddWidget(tooltip);

    Panel* rightPanel = new Panel("panel_right");
    rightPanel->ScaleTo({ screenSize.x - fifthScreenX, screenSize.y });
    rightPanel->MoveTo({ fifthScreenX, 0.0f });
    rightPanel->AddWidget(tab);

    setAllWidgets({ leftPanel, rightPanel });
}

void LearnMenu::RunMenu()
{
    // TODO: Make positions relative to screen, and update as the screen updates instead of this
    ImVec2 screenSize = MenuAppSignaler::SignalGetWindowSize();
    float fifthScreenX = (int)screenSize.x / 5; // at a fith of screen

    Panel* p1 = (Panel*)m_MainPanel->GetWidget("panel_left");
    p1->ScaleTo({ fifthScreenX, screenSize.y });
    p1->MoveTo({ 0.0f, 0.0f });

    Panel* p2 = (Panel*)m_MainPanel->GetWidget("panel_right");
    p2->ScaleTo({ screenSize.x - fifthScreenX, screenSize.y });
    p2->MoveTo({ fifthScreenX, 0.0f });

    m_MainPanel->ScaleTo(screenSize);

    // canvas animations
    static float delay = 0.005f; // TODO: add a delay slider for user
    static float crt = -1.0f; // TODO: instead use Time.time rather than using Time.deltaTime
    if (LearnMenuManager::IsCanvasAnimationInProgress())
    {
        if (crt <= 0.0f)
        {
            LearnMenuManager::UpdateCanvasAnimation();
            crt = delay;
        }
        else
        {
            crt -= Time::GetDeltaTime();
        }
    }
}
