#pragma once
#include "Menu.h"

// This is the main screen
class MainMenu : public Menu
{
public:
	MainMenu() = default;
	MainMenu(std::string id);
	virtual ~MainMenu();

public:
	virtual void InitMenu() override;
	virtual void RunMenu() override;
};