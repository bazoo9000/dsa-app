#pragma once

#include "../Widget/Panel.h"

using json = nlohmann::json;

class LearnParser
{
public:
	static Panel* CreateLearnPanel(std::string learnTabName);

private:
	static json readJSON(std::string jsonFileName);
	static Panel* parseJSON(json jsonData, Panel* panel);
	static void setText(Panel* panel, const json& data, int index);
	static void setCanvas(Panel* panel, const json& data, int index);
};