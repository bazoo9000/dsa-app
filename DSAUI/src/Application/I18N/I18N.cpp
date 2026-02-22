#include "../../dsa_pch.h"

#include "I18N.h"
#include "Logger/Logger.h"

static const std::string LOCALE_PATH = "locales/";

I18N::I18N(const std::string& locale)
	: m_Locale(locale)
{
	validateLocale(locale);
}

I18N::~I18N()
{
	m_Locale.clear();
}

std::vector<TV> I18N::GetTexts(std::vector<std::string> tokens)
{
	json textMap = readLocaleFile(m_Locale + ".json");

	std::vector<TV> ret;
	ret.reserve(tokens.size());

	for (auto tok : tokens)
	{
		if (textMap.find(tok) != textMap.end())
		{
			ret.push_back({ tok, textMap[tok] });
		}
		else
		{
			LOG_GUI_ERROR("Token %s doesn't exist", tok.c_str());
			ret.push_back({ tok, tok });
		}
	}

	return ret;
}

TV I18N::GetText(std::string token)
{
	return GetTexts({ token })[0];
}

std::string I18N::GetCurrentLocale()
{
	return m_Locale;
}

void I18N::validateLocale(std::string locale)
{
	json textMap = readLocaleFile(locale + ".json");

	auto missingTokens = getMissingTokens(textMap);
	if (!missingTokens.empty())
	{
		std::ostringstream oss;

		oss << "\n";
		for (auto it = missingTokens.begin(); it != missingTokens.end(); it++)
		{
			oss << *it << "\n";
		}

		LOG_GUI_WARN("Missing tokens found:\n%s", oss.str().c_str());
	}

	LOG_GUI_INFO("Reading locale %s was succesful", locale);
}

json I18N::readLocaleFile(std::string localeFileName)
{
	json textMap;

	std::string path = LOCALE_PATH + localeFileName.c_str();
	std::ifstream fin;

	fin.open(path.c_str());

	if (fin.fail())
	{
		LOG_GUI_FATAL("Failed to open locale file %s doesn't exist", localeFileName.c_str());
		exit(1);
	}

	LOG_GUI_DEBUG("Locale file %s succesfully opened", localeFileName.c_str());

	textMap = json::parse(fin);
	fin.close();

	return textMap;
}

std::vector<std::string> I18N::getMissingTokens(json textMap)
{
	std::vector<std::string> missingTokens = {};
	for (auto it = VALID_TOKENS.begin(); it != VALID_TOKENS.end(); it++)
	{
		if (!textMap.contains(*it))
		{
			missingTokens.push_back(*it);
		}
	}

	return missingTokens;
}
