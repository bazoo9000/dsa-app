#pragma once

#include "../Widget.h"
#include "../Panel.h"
#include "../Button.h"
#include "../BasicText.h"
#include "../TextLabel.h"
#include "../TextBox.h"
#include "../ComboBox.h"

#include "../../IAppReceiver.h"
#include "../../CacheManager/CacheManager.h"

class Screen
{
public:
	Screen() = default;
	Screen(std::string id);
	virtual ~Screen();

public:
	void Draw();

public:
	// TODO: decide if to have a default init as a reminder
	virtual void InitScreen(CacheManager<std::string>& textCache, CacheManager<Widget*>& widgetCache) = 0;
	static void SetApp(IAppReceiver* app);

public:
	std::string GetId();

protected:
	static void signalChangeScreen(std::string id);
	static void signalCloseApp();
	// TODO: maybe add a request method for tokens

protected:
	std::string m_Id = "";
	Panel* m_MainPanel = nullptr;
	static IAppReceiver* m_App;
	// TODO: maybe add the cachemanagers here instead in app
};