#pragma once

#include "../../dsa_pch.h"

using json = nlohmann::json;

static const std::vector<std::string> VALID_TOKENS = {
	"GUI.BACK",
	"GUI.CLOSE",
	"GUI.BUTTON",
	"GUI.WELCOME",
	"GUI.OPTIONS"
};

class I18N
{
public:
	I18N(const std::string& locale);
	~I18N();

	I18N(const I18N&) = delete;
	I18N& operator=(const I18N&) = delete;

public:
	std::string GetCurrentLocale();
	std::string GetText(std::string token);
	void LoadTextMap(std::string locale);
	void ClearTextMap();

private:
	json readLocaleFile(std::string localeFileName);
	std::vector<std::string> getMissingTokens(json textMap);
	void overrideToken(std::string token, std::string newVal);

private:
	static I18N* s_Instance;
	std::string m_Locale;
	json m_TextMap; // token -> translated text
};