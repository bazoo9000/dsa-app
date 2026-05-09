#pragma once

#include "Menu.h"

class LearnMenu : public Menu
{
public:
	LearnMenu(std::string id);
	~LearnMenu();

public:
	virtual void InitMenu() override;
	virtual void RunMenu() override;

private:
	// TODO: move this somewhere else, for now its ok here
	Panel* parseLearnJSON(std::string learnTabName);

private:
	std::unordered_map<std::string, Panel*> m_LearnPanels;
};