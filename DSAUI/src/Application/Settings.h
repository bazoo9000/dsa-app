#pragma once

#include <string> // remove this, and add clangd file already
#include "imgui.h"

struct SettingsData
{
	ImVec2 resolution = { 1280.0f, 720.0f };
	bool isVsync = true;
	std::string language = "ro-RO";
};

// TODO: make hot reloading, to change settings after pressing save
class Settings
{
public:
	Settings() = default;
	~Settings() = default;

public:
	static SettingsData LoadSettings();
	static void SaveSettings(SettingsData data);
	static void RestoreDefaultSettings();

private:
    static SettingsData readSettings();
    static void writeSettings(SettingsData data);

private:
	static const std::string SETTINGS_FILENAME;
};
