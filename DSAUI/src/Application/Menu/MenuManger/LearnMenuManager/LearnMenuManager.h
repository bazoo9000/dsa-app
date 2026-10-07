#pragma once

#include "../../Animator/Animator.h"

#include "../../../Widget/Panel.h"
#include "../../../Widget/Canvas.h"
#include "Application/Menu/Animator/SortAnimator.h"

using json = nlohmann::json;

class LearnMenuManager
{
public:
	static Panel* CreateLearnPanel(std::string learnTabName);
	static std::map<std::string, std::string> GetAllTitles();
	static std::vector<uint32_t> CreateVector(uint32_t max, bool shuffle = false);

public:
	static void BeginCanvasAnimation(Canvas* canvas);
	static void UpdateCanvasAnimation();
	static bool IsCanvasAnimationInProgress();

private:
	// TODO: maybe a vector of animators will work ok here, since if there are multiple canvases which can be animated will be a problem
	static Animator* s_CanvasAnimator; // will leave it as pointer, since Animator will be a base class

private:
	static json readJSON(std::string jsonFileName);
	static Panel* parseJSON(json jsonData, Panel* panel);
	static void setText(Panel* panel, const json& data, int index);
	static void setCanvas(Panel* panel, const json& data, int index);

private:
	static std::string s_LearnPath;
};
