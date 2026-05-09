#pragma once

#include "../../IAppReceiver.h"
#include "../Panel.h"

class Menu
{
public:
	Menu() = default;
	Menu(std::string id);
	virtual ~Menu();

public:
	void Draw();

public:
	// TODO: decide if to have a default init as a reminder
	virtual void InitMenu() = 0;
	virtual void RunMenu() = 0;
	static void SetApp(IAppReceiver* app);

public:
	std::string GetId();

protected:
	void setAllWidgets(std::vector<Widget*> widgets);

protected:
	static void signalChangeMenu(std::string id);
	static void signalCloseApp();
	static std::unordered_map<std::string, std::string> signalRequestTokens(std::vector<std::string> tokens);
	static ImVec2 signalGetWindowSize();

protected:
	std::string m_Id = "";
	Panel* m_MainPanel = nullptr;
	static IAppReceiver* m_App;
};