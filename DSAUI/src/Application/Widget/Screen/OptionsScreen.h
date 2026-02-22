#pragma once
#include "Screen.h"

class OptionsScreen : public Screen
{
public:
	OptionsScreen() = default;
	OptionsScreen(std::string id);
	virtual ~OptionsScreen();

public:
	virtual void InitScreen(CacheManager<std::string>& textCache, CacheManager<Widget*>& widgetCache) override;
};