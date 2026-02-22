#include "../../dsa_pch.h"

#include "I18NFactory.h"
#include "Logger/Logger.h"

std::unordered_map<std::string, I18N*> I18NFactory::m_I18NInstances = std::unordered_map<std::string, I18N*>();
std::string I18NFactory::m_CurrentLocale = "";

I18N* I18NFactory::GetI18N(std::string locale)
{
	m_CurrentLocale = locale;

	if (m_I18NInstances.find(locale) == m_I18NInstances.end() || m_I18NInstances[locale] == nullptr)
	{
		LOG_GUI_DEBUG("Created new locale %s", locale.c_str());
		m_I18NInstances[locale] = new I18N(locale);
	}

	return m_I18NInstances[locale];
}