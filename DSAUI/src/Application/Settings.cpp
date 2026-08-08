#include "../dsa_pch.h"

#include "Settings.h"

#include "Logger/Logger.h"

const std::string Settings::SETTINGS_FILENAME = "settings.json";

SettingsData Settings::LoadSettings()
{
    return Settings::readSettings();
}

void Settings::SaveSettings(SettingsData data)
{
	Settings::writeSettings(data);
}

void Settings::RestoreDefaultSettings()
{
    Settings::writeSettings(SettingsData());
}

SettingsData Settings::readSettings()
{
    SettingsData ret;

	std::ifstream file;
	file.open(SETTINGS_FILENAME);

	if (file.is_open())
	{
		using json = nlohmann::json;

		json settings = json::parse(file);

		if (!settings["resolution"]["x"].is_null() && !settings["resolution"]["y"].is_null())
		{
			ret.resolution.x = (float)settings["resolution"]["x"];
			ret.resolution.y = (float)settings["resolution"]["y"];
		}

		if (!settings["isVsync"].is_null())
		{
			ret.isVsync = settings["isVsync"];
		}

		if (!settings["language"].is_null())
		{
			ret.language = settings["language"];
		}

		LOG_GUI_DEBUG("Settings loaded succesfully");
	}
	else
	{
		LOG_GUI_WARN("Couldn't open settings file, loading default");
	}

	file.close();
	return ret;
}

void Settings::writeSettings(SettingsData data)
{
    std::ofstream file(SETTINGS_FILENAME);

	if (!file.is_open())
	{
		LOG_GUI_ERROR("Failed to write settings file");
		return;
	}
	else
	{
		using json = nlohmann::json;

		SettingsData defaultData = SettingsData();

		json out;
		out["resolution"]["x"] = (int)data.resolution.x; // not necessary to cast to int, looks nicer
		out["resolution"]["y"] = (int)data.resolution.y;
		out["isVsync"] = data.isVsync;
		out["language"] = data.language;

		file.clear();
		file << out.dump(4);

		LOG_GUI_DEBUG("Settings restored to default succesfully");
	}

	file.close();
}
