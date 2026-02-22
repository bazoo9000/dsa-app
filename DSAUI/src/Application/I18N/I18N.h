#pragma once

#include "../../dsa_pch.h"

using json = nlohmann::json;
// TODO: remove this and convert to hashmap, im stupid
using TV = std::pair<std::string, std::string>; // token/value pair

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
	std::vector<TV> GetTexts(std::vector<std::string> tokens);
	TV GetText(std::string token);
	std::string GetCurrentLocale();
	
private:
	void validateLocale(std::string locale);
	json readLocaleFile(std::string localeFileName);
	std::vector<std::string> getMissingTokens(json textMap);

private:
	std::string m_Locale;
};