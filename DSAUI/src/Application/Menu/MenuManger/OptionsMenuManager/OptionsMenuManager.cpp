#include "../../../../dsa_pch.h"

#include "OptionsMenuManager.h"

#include "../../MenuAppSignaler.h"

#include "../../../Widget/TextLabel.h"
#include "../../../Widget/ComboBox.h"
#include "../../../Widget/Checkbox.h"
#include "../../../Widget/Button.h"

#include "Logger/Logger.h"

#define LOCALE_PATH "locales/"

SettingsData OptionsMenuManager::s_Data = SettingsData();
std::vector<std::string> OptionsMenuManager::s_Resolutions = { "800x600", "1280x720", "1600x900" };

Panel* OptionsMenuManager::GetOptionsPanel()
{
    // TODO: add a tool tip to each setting

    auto tokens = MenuAppSignaler::SignalRequestTokens(
        { "GUI.RESOLUTION", "GUI.SAVE", "GUI.LANGUAGE", "GUI.DEFAULT" }
    );

    // maybe this can be done better, for now its ok
    OptionsMenuManager::s_Data = Settings::LoadSettings();

    TextLabel* warnText = new TextLabel("text_warning", "*Application needs to restart to apply settings");
	warnText->MoveTo({ 300.0f, 450.0f });
	warnText->Hide();

	// Resolution
	TextLabel* resText = new TextLabel("text_res", tokens["GUI.RESOLUTION"], FONT_H4);
	resText->MoveTo({ 0.0f, 0.0f });

	ComboBox* comboRes = new ComboBox("combo_resolution", s_Resolutions);
	comboRes->MoveTo({ resText->GetTransform().position.x, resText->GetTransform().position.y + 35.0f });
	comboRes->ScaleTo({ 100.0f, 0.0f });
	comboRes->SetSelectedIndex(OptionsMenuManager::getComboIndex(s_Resolutions, vecToStr(OptionsMenuManager::s_Data.resolution)));

	// VSYNC
	CheckBox* checkVsync = new CheckBox("checkbox_vsync", "Vsync", OptionsMenuManager::s_Data.isVsync);
	checkVsync->MoveTo({ 0.0f, 100.0f });

	// Lang
	TextLabel* langText = new TextLabel("text_lang", tokens["GUI.LANGUAGE"], FONT_H4);
	langText->MoveTo({ 0.0f, 200.0f });

	auto locales = OptionsMenuManager::getAllLocaleFileNames();
	ComboBox* comboLang = new ComboBox("combo_language", locales);
	comboLang->MoveTo({ langText->GetTransform().position.x, langText->GetTransform().position.y + 35.0f });
	comboLang->ScaleTo({ 100.0f, 0.0f });
	comboLang->SetSelectedIndex(OptionsMenuManager::getComboIndex(locales, OptionsMenuManager::s_Data.language));

	Button* saveBut = new Button("button_save", tokens["GUI.SAVE"]);
	saveBut->SetCallback(
		[comboLang, checkVsync, comboRes, warnText]()
		{
			OptionsMenuManager::s_Data.language = comboLang->GetSelected();
			OptionsMenuManager::s_Data.isVsync = checkVsync->GetValue();
			OptionsMenuManager::s_Data.resolution = OptionsMenuManager::strToVec(comboRes->GetSelected());

			Settings::SaveSettings(OptionsMenuManager::s_Data);

			warnText->Show();
		}
	);
	saveBut->MoveTo({ 0.0f, 300.0f });
	saveBut->ScaleTo({ 50.0f, 20.0f });

	Button* defaultBut = new Button("button_default", tokens["GUI.DEFAULT"]);
	defaultBut->SetCallback(
		[comboLang, checkVsync, comboRes, warnText]()
		{
		    Settings::RestoreDefaultSettings();
			OptionsMenuManager::s_Data = Settings::LoadSettings();

			comboLang->SetSelectedIndex(OptionsMenuManager::getComboIndex(OptionsMenuManager::getAllLocaleFileNames(), OptionsMenuManager::s_Data.language));
			checkVsync->SetValue(OptionsMenuManager::s_Data.isVsync);
			comboRes->SetSelectedIndex(OptionsMenuManager::getComboIndex(s_Resolutions, OptionsMenuManager::vecToStr(OptionsMenuManager::s_Data.resolution)));

       		warnText->Show();
		}
	);
	defaultBut->MoveTo({ 100.0f, 300.0f });
	defaultBut->ScaleTo({ 50.0f, 20.0f });

	std::vector<Widget*> widgets = { warnText, resText, comboRes, checkVsync, langText, comboLang, saveBut, defaultBut };
	Panel* ret = new Panel("panel_options", widgets);
    return ret;
}

ImVec2 OptionsMenuManager::strToVec(const std::string& str)
{
    std::istringstream iss(str);
	std::string x;
	std::string y;
	std::getline(iss, x, 'x');
	std::getline(iss, y, 'x');

	return { std::stof(x), std::stof(y) };
}

std::string OptionsMenuManager::vecToStr(const ImVec2& vec)
{
	return std::to_string((int)vec.x) + "x" + std::to_string((int)vec.y);
}

int OptionsMenuManager::getComboIndex(const std::vector<std::string>& haystack, std::string needle)
{
    for (int i = 0; i < haystack.size(); i++)
	{
	    if (haystack[i] == needle)
	    {
			return i;
	    }
	}

    LOG_GUI_WARN("Couldn't find needle %s", needle);
	return 0;
}

std::vector<std::string> OptionsMenuManager::getAllLocaleFileNames()
{
    std::vector<std::string> ret;

    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator(LOCALE_PATH))
    {
        std::string locale = entry.path().stem().string();
        ret.push_back(locale);
    }

    return ret;
}
