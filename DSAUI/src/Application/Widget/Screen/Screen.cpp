#include "../../../dsa_pch.h"

#include "Screen.h"
#include "Logger/Logger.h"

IAppReceiver* Screen::m_App = nullptr;

Screen::Screen(std::string id)
	: m_Id(id)
{
}

Screen::~Screen()
{
	m_Id.clear();
}

void Screen::Draw()
{
	m_MainPanel->Draw();
}

void Screen::SetApp(IAppReceiver* app)
{
	m_App = app;
}

void Screen::signalChangeScreen(std::string id)
{
	m_App->ChangeScreen(id);
}

void Screen::signalCloseApp()
{
	m_App->Close();
}

std::string Screen::GetId()
{
	return m_Id;
}