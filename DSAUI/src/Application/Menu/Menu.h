#pragma once

#include "MenuAppSignaler.h"
#include "../Widget/Panel.h"

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

public:
	std::string GetId();

protected:
	void setAllWidgets(std::vector<Widget*> widgets);

protected:
	std::string m_Id = "";
	Panel* m_MainPanel = nullptr;
};
