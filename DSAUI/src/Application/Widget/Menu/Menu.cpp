#include "../../../dsa_pch.h"

#include "Menu.h"
#include "Logger/Logger.h"

IAppReceiver* Menu::m_App = nullptr;

Menu::Menu(std::string id)
	: m_Id(id)
{
}

Menu::~Menu()
{
	m_Id.clear();
}

void Menu::Draw()
{
	m_MainPanel->Draw();
	RunMenu();
}

void Menu::SetApp(IAppReceiver* app)
{
	m_App = app;
}

void Menu::signalChangeMenu(std::string id)
{
	m_App->ChangeMenu(id);
}

void Menu::signalCloseApp()
{
	m_App->Close();
}

std::unordered_map<std::string, std::string> Menu::signalRequestTokens(std::vector<std::string> tokens)
{
	return m_App->RequestTokens(tokens);
}

std::string Menu::GetId()
{
	return m_Id;
}