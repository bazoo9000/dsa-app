#pragma once

#include "../../../Settings.h"

#include "../../../Widget/Panel.h"

using json = nlohmann::json;

class OptionsMenuManager
{
public:
    static Panel* GetOptionsPanel();

private:
    static ImVec2 strToVec(const std::string& str);
    static std::string vecToStr(const ImVec2& vec);
    static int getComboIndex(const std::vector<std::string>& haystack, std::string needle);
    static std::vector<std::string> getAllLocaleFileNames();

private:
    static SettingsData s_Data;
    static std::vector<std::string> s_Resolutions;
    static std::string s_LangPath;
};
