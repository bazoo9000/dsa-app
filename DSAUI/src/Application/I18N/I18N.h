#pragma once

using json = nlohmann::json;

class I18N
{
public:
	I18N(const std::string& locale);
	~I18N();

	I18N(const I18N&) = delete;
	I18N& operator=(const I18N&) = delete;

public:
	std::unordered_map<std::string, std::string> GetTexts(std::vector<std::string> tokens);
	std::string GetText(std::string token);
	std::string GetCurrentLocale();

private:
	void validateLocale(std::string locale);
	json readLocaleFile(std::string localeFileName);
	std::vector<std::string> getMissingTokens(json textMap);

private:
	std::string m_Locale;
};
