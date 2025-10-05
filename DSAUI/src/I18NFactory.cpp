#include "dsa_pch.h"
#include "I18NFactory.h"
#include "Logger/Logger.h"

std::map<std::string, I18N*> I18NFactory::m_I18NInstances = std::map<std::string, I18N*>();
std::string I18NFactory::m_CurrentLocale = "";

I18N* I18NFactory::GetI18N(std::string locale)
{
	if (m_CurrentLocale != "")
	{
		LOG_GUI_DEBUG("Locale %s has been cleared", m_CurrentLocale.c_str());
		m_I18NInstances[m_CurrentLocale]->ClearTextMap();
	}

	m_CurrentLocale = locale;
	if (m_I18NInstances.find(locale) == m_I18NInstances.end() || m_I18NInstances[locale] == nullptr)
	{
		LOG_GUI_DEBUG("Created new locale %s", locale.c_str());
		m_I18NInstances[locale] = new I18N(locale);
	}
	else
	{
		LOG_GUI_DEBUG("Locale %s has been reloaded", locale.c_str());
		m_I18NInstances[locale]->LoadTextMap(locale);
	}

	return m_I18NInstances[locale];
}