#include "../../dsa_pch.h"

#include "MenuAppSignaler.h"

#include "Logger/Logger.h"

IAppReceiver* MenuAppSignaler::s_App = nullptr;

void MenuAppSignaler::SetAppRef(IAppReceiver* app)
{
	s_App = app;
}

void MenuAppSignaler::SignalChangeMenu(std::string id)
{
    MenuAppSignaler::checkAppRef();
	s_App->ChangeMenu(id);
}

void MenuAppSignaler::SignalCloseApp()
{
    MenuAppSignaler::checkAppRef();
	s_App->Close();
}

std::unordered_map<std::string, std::string> MenuAppSignaler::SignalRequestTokens(std::vector<std::string> tokens)
{
    MenuAppSignaler::checkAppRef();
	return s_App->RequestTokens(tokens);
}

std::string MenuAppSignaler::SignalRequestToken(std::string token)
{
    MenuAppSignaler::checkAppRef();
	return s_App->RequestToken(token);
}

ImVec2 MenuAppSignaler::SignalGetWindowSize()
{
    MenuAppSignaler::checkAppRef();
	return s_App->GetWindowSize();
}

void MenuAppSignaler::checkAppRef()
{
    if (!s_App)
    {
        LOG_GUI_FATAL("Application reference is null");
        exit(1);
    }
}
