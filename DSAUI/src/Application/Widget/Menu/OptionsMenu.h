#pragma once
#include "Menu.h"

#include "../../Settings.h"

class OptionsMenu : public Menu
{
public:
	OptionsMenu() = default;
	OptionsMenu(std::string id);
	virtual ~OptionsMenu();

public:
	virtual void InitMenu() override;
	virtual void RunMenu() override;

private:
	SettingsData m_SettingsData;
};