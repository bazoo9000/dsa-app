#pragma once
#include "Screen.h"

// This is the main screen
class MainScreen : public Screen
{
public:
	MainScreen() = default;
	MainScreen(std::string id);
	virtual ~MainScreen();

public:
	virtual void InitScreen(CacheManager<std::string>& textCache, CacheManager<Widget*>& widgetCache) override;
};