#pragma once
#include "Menu.h"

class OptionsMenu : public Menu
{
public:
	OptionsMenu() = default;
	OptionsMenu(std::string id);
	virtual ~OptionsMenu();

public:
	virtual void InitMenu(CacheManager<std::string>& textCache, CacheManager<Widget*>& widgetCache) override;
	virtual void RunMenu() override;
};