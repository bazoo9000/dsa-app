#include "../../../../dsa_pch.h"

#include "OptionsMenuManager.h"

#include "../../../Widget/TextLabel.h"
#include "../../../Widget/ComboBox.h"
#include "../../../Widget/Checkbox.h"
#include "../../../Widget/Button.h"

SettingsData OptionsMenuManager::s_Data = SettingsData();
std::vector<std::string> OptionsMenuManager::s_Resolutions = { "800x600", "1280x720", "1600x900" };
std::vector<std::string> OptionsMenuManager::s_Languages = { "ro-RO", "en-US" };

Panel* OptionsMenuManager::GetOptionsPanel()
{
    // maybe this can be done better, for now its ok
    OptionsMenuManager::s_Data = Settings::LoadSettings();

    TextLabel* warnText = new TextLabel("text_warning", "*Application needs to restart to apply settings");
	warnText->MoveTo({ 300.0f, 450.0f });
	warnText->Hide();

	// Resolution
	TextLabel* resText = new TextLabel("text_res", "Resolution", FONT_H4);
	resText->MoveTo({ 0.0f, 0.0f });

	ComboBox* comboRes = new ComboBox("combo_resolution", s_Resolutions);
	comboRes->MoveTo({ resText->GetTransform().position.x, resText->GetTransform().position.y + 35.0f });
	comboRes->ScaleTo({ 100.0f, 0.0f });
	comboRes->SetSelectedIndex(OptionsMenuManager::getComboIndex(s_Resolutions, vecToStr(OptionsMenuManager::s_Data.resolution)));

	// VSYNC
	CheckBox* checkVsync = new CheckBox("checkbox_vsync", "Vsync", OptionsMenuManager::s_Data.isVsync);
	checkVsync->MoveTo({ 0.0f, 100.0f });

	// Lang
	TextLabel* langText = new TextLabel("text_lang", "Language", FONT_H4);
	langText->MoveTo({ 0.0f, 200.0f });

	ComboBox* comboLang = new ComboBox("combo_language", s_Languages);
	comboLang->MoveTo({ langText->GetTransform().position.x, langText->GetTransform().position.y + 35.0f });
	comboLang->ScaleTo({ 100.0f, 0.0f });
	comboLang->SetSelectedIndex(OptionsMenuManager::getComboIndex(s_Languages, OptionsMenuManager::s_Data.language));

	Button* saveBut = new Button("button_save", "Save");
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

	Button* defaultBut = new Button("button_default", "Default");
	defaultBut->SetCallback(
		[comboLang, checkVsync, comboRes, warnText]()
		{
		    Settings::RestoreDefaultSettings();
			OptionsMenuManager::s_Data = Settings::LoadSettings();

			comboLang->SetSelectedIndex(OptionsMenuManager::getComboIndex(s_Languages, OptionsMenuManager::s_Data.language));
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

	return 0;
}
