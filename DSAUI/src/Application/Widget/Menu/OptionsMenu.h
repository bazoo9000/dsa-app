#pragma once
#include "Menu.h"

class OptionsMenu : public Menu
{
public:
	OptionsMenu() = default;
	OptionsMenu(std::string id);
	virtual ~OptionsMenu();

public:
	virtual void InitMenu() override;
	virtual void RunMenu() override;
};