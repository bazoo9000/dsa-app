#pragma once

#include "../IAppReceiver.h"

#include "imgui.h"

class MenuAppSignaler
{
public:
    MenuAppSignaler() = default;
    ~MenuAppSignaler() = default;

public:
    static void SetAppRef(IAppReceiver* app);
    static void SignalChangeMenu(std::string id);
	static void SignalCloseApp();
	static std::unordered_map<std::string, std::string> SignalRequestTokens(std::vector<std::string> tokens);
	static std::string SignalRequestToken(std::string token);
	static ImVec2 SignalGetWindowSize();

private:
    static void checkAppRef();

private:
    static IAppReceiver* s_App;
};
