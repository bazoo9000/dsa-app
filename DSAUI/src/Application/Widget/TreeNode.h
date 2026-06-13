#pragma once

#include "Widget.h"

class TreeNode : public Widget
{
public:
	TreeNode(std::string id, std::string label);
	TreeNode(std::string id, std::string label, std::vector<Widget*>& widgets);
	~TreeNode();

protected:
	virtual inline void drawWidget() override;

public:
	// TODO: add an interface for having the power to do hierarhical rendering
	void AddWidget(Widget* widget);
	Widget* GetWidget(std::string id);
	void RemoveWidget(std::string id);
	std::string GetLabel() { return m_Label; }
	void SetLabel(std::string label) { m_Label = label; }

private:
	void addChild(std::string id, Widget* widget);

private:
	std::unordered_map<std::string, std::list<Widget*>::iterator> m_ChildrenMap; // for fast search
	std::list<Widget*> m_ChildrenList; // for ordering
	std::string m_Label = "";
};