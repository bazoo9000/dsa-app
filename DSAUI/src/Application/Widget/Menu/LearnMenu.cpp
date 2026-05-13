#include "../../../dsa_pch.h"

#include "LearnMenu.h"

#include "../Button.h"
#include "../CustomWidget.h"
#include "../TreeNode.h"
#include "../TextLabel.h"
#include "../TextBox.h"
#include "../Tab.h"
#include "../Canvas.h"

#include "../Shape/DrawableCircle.h";

#include "../../LearnParser/LearnParser.h"

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
	auto tokens = signalRequestTokens({
		"GUI.BACK", "GUI.OPTIONS"
		});

    TextBox* tbox2 = new TextBox("textbox_2", "GUI.LINKEDLIST_PARAGRAPH_TEST");
    tbox2->ScaleTo({ 0.0f, 500.0f });
    tbox2->SetAutoPositioning(true);
    TextBox* tbox3 = new TextBox("textbox_3", "GUI.BINARYTREE_PARAGRAPH_TEST");
    tbox3->ScaleTo({ 0.0f, 500.0f });
    tbox3->SetAutoPositioning(true);
    TextBox* tbox4 = new TextBox("textbox_4", "GUI.HASHMAP_PARAGRAPH_TEST");
    tbox4->ScaleTo({ 0.0f, 500.0f });
    tbox4->SetAutoPositioning(true);
    Tab* tab = new Tab("tab_test");

    tab->AddTabItem(LearnParser::CreateLearnPanel("learn_array"), "GUI.ARRAY_TITLE");
    tab->AddTabItem(tbox2, "GUI.LINKEDLIST_TITLE");
    tab->AddTabItem(tbox3, "GUI.BINARYTREE_TITLE");
    tab->AddTabItem(tbox4, "GUI.HASHMAP_TITLE");

    CustomWidget* custom1 = new CustomWidget("custom_header_select");
    custom1->AddCustomScript([tab]()
        {
            if (ImGui::TreeNode("GUI.DATA_STRUCTURES"))
            {
                auto tabKeys = tab->GetAllKeys();
                for (auto& key : tabKeys)
                {
                    // this may look ugly but it works :)
                    bool selected = tab->GetTabItemSelected(key);
                    ImGui::Selectable(tab->GetTabItemName(key).c_str(), &selected);
                    tab->SetTabItemSelected(key, selected);
                }

                ImGui::TreePop();
            }
        }
    );

    ImVec2 screenSize = signalGetWindowSize();
    float fifthScreenX = (int)screenSize.x / 5; // at a fith of screen

    Button* but = new Button("but_back", tokens["GUI.BACK"]);
    but->SetCallback(
        []()
        {
            Menu::signalChangeMenu("menu_main");
        }
    );
    but->MoveTo({ 10.0f, screenSize.y - 35.0f });
    but->ScaleTo({ 50.0f, 20.0f });

    Panel* leftPanel = new Panel("panel_left");
    leftPanel->ScaleTo({ fifthScreenX, screenSize.y });
    leftPanel->MoveTo({ 0.0f, 0.0f });
    leftPanel->AddWidget(custom1);
    leftPanel->AddWidget(but);
    
    Panel* rightPanel = new Panel("panel_right");
    rightPanel->ScaleTo({ screenSize.x - fifthScreenX, screenSize.y });
    rightPanel->MoveTo({ fifthScreenX, 0.0f });
    rightPanel->AddWidget(tab);

    TextLabel* label1 = new TextLabel("text_test_1", "Label1");
    label1->SetAutoPositioning(true);
    TextLabel* label2 = new TextLabel("text_test_2", "Label2");
    label2->SetAutoPositioning(true);
    TreeNode* node = new TreeNode("treenode_test", "Tree Title");
    node->AddWidget(label1);
    node->AddWidget(label2);
    node->SetAutoPositioning(true);

    leftPanel->AddWidget(node);

    setAllWidgets({ leftPanel, rightPanel });

    // TODO: add tooltip decorator
}

void LearnMenu::RunMenu()
{
    // TODO: Make positions relative to screen, and update as the screen updates
    // instead of this
    ImVec2 screenSize = signalGetWindowSize();
    float fifthScreenX = (int)screenSize.x / 5; // at a fith of screen

    Panel* p1 = (Panel*)m_MainPanel->GetWidget("panel_left");
    p1->ScaleTo({ fifthScreenX, screenSize.y });
    p1->MoveTo({ 0.0f, 0.0f });

    Panel* p2 = (Panel*)m_MainPanel->GetWidget("panel_right");
    p2->ScaleTo({ screenSize.x - fifthScreenX, screenSize.y });
    p2->MoveTo({ fifthScreenX, 0.0f });

    m_MainPanel->ScaleTo(screenSize);
}
