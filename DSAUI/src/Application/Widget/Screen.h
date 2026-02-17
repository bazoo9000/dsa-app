#pragma once

#include "../../dsa_pch.h"

#include "Panel.h"
#include "../IAppReceiver.h"

class Screen
{
public:
	Screen() = default;
	Screen(std::string id, Panel* panel);
	~Screen();

public:
	void Draw();

public:
	static void SetApp(IAppReceiver* app);
	static void SignalChangeScreen(std::string id);
	static void SignalCloseApp();

public:
	std::string GetId();

private:
	std::string m_Id;
	Panel* m_MainPanel;
	static IAppReceiver* m_App;
};