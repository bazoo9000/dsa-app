#pragma once

#include "../../dsa_pch.h"

#include "I18N.h"

class I18NFactory
{
public:
	static I18N* GetI18N(std::string locale);
	static std::string GetLocale() { return m_CurrentLocale; }

private:
	static std::map<std::string, I18N*> m_I18NInstances; // locale -> instance
	static std::string m_CurrentLocale;
};