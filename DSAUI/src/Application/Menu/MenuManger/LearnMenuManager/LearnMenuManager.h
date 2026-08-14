#pragma once

#include "../../../Widget/Panel.h"

using json = nlohmann::json;

class LearnMenuManager
{
public:
	static Panel* CreateLearnPanel(std::string learnTabName);
	static std::map<std::string, std::string> GetAllTitles();

private:
	static json readJSON(std::string jsonFileName);
	static Panel* parseJSON(json jsonData, Panel* panel);
	static void setText(Panel* panel, const json& data, int index);
	static void setCanvas(Panel* panel, const json& data, int index);
	static std::vector<uint32_t> createVector(uint32_t max, bool shuffle = false);

private:
	static std::string s_LearnPath;
};