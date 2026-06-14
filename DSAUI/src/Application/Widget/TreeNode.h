#pragma once

#include "WidgetCollector.h"

class TreeNode : public WidgetCollector
{
public:
	TreeNode(std::string id, std::string label);
	TreeNode(std::string id, std::string label, std::vector<Widget*>& widgets);
	~TreeNode();

protected:
	virtual inline void drawWidget() override;

public:
	std::string GetLabel() { return m_Label; }
	void SetLabel(std::string label) { m_Label = label; }

private:
	std::string m_Label = "";
};