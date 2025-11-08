#include "../dsa_pch.h"

#include "I18N.h"
#include "Logger/Logger.h"

I18N* I18N::s_Instance = nullptr;

const std::string LOCALE_PATH = "locales/";

I18N::I18N(const std::string& locale)
	: m_Locale(locale)
{
	LoadTextMap(locale);
}

I18N::~I18N()
{
	ClearTextMap();
	m_Locale.clear();
}

std::string I18N::GetCurrentLocale()
{
	return m_Locale;
}

std::string I18N::GetText(std::string token)
{
	try
	{
		return m_TextMap[token].get<std::string>();
	}
	catch (std::exception const& e)
	{
		LOG_GUI_ERROR("Token %s doesn't exist", token.c_str());
		return token;
	}
}

void I18N::LoadTextMap(std::string locale)
{
	m_TextMap = readLocaleFile(locale + ".json");

	auto missingTokens = getMissingTokens(m_TextMap);
	if (!missingTokens.empty())
	{
		std::ostringstream oss;

		oss << "\n";
		for (auto it = missingTokens.begin(); it != missingTokens.end(); it++)
		{
			std::string token = *it;

			overrideToken(token, token); // instead have the token id instead of the word
			oss << token << "\n";
		}

		LOG_GUI_WARN("Missing tokens found:%s", oss.str().c_str());
	}

	LOG_GUI_INFO("Reading locale %s was succesful", m_Locale);
}

void I18N::ClearTextMap()
{
	m_TextMap.clear();
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

void I18N::overrideToken(std::string token, std::string newVal)
{
	m_TextMap[token] = newVal;
}
