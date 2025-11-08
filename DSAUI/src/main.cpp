#include "dsa_pch.h"
#include "DSACore.h"

#include "I18N/I18NFactory.h"

int main(int argc, char* argv[])
{
	I18N* i18n = I18NFactory::GetI18N("ro-RO");
	LOG_GUI_TRACE(i18n->GetText("GUI.BACK").c_str());

	i18n = I18NFactory::GetI18N("en-US");
	LOG_GUI_TRACE(i18n->GetText("GUI.BACK").c_str());

	i18n = I18NFactory::GetI18N("ro-RO");
	LOG_GUI_TRACE(i18n->GetText("GUI.BACK").c_str());

	std::cin.get();

	return 0;
}