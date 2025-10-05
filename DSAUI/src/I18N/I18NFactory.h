#pragma once

#include "../dsa_pch.h"

#include "I18N.h"

class I18NFactory
{
public:
	static I18N* GetI18N(std::string locale);

private:
	static std::map<std::string, I18N*> m_I18NInstances; // locale -> instance
	static std::string m_CurrentLocale;
};