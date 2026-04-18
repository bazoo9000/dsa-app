#pragma once

#include "imgui.h"

class Shape
{
public:
	Shape() = default;
	virtual ~Shape() = default;

public:
	ImVec2 GetGlobalOrigin() { return m_GlobalOrigin; }
	void SetGlobalOrigin(ImVec2 global) { m_GlobalOrigin = global; }
	ImVec2 GetOrigin() { return m_Origin; }
	void SetOrigin(ImVec2 origin) { m_Origin = origin; }
	ImVec2 GetFinalOriginPositon() { return m_GlobalOrigin + m_Origin; }

protected:
	// Global position of origin point, used for placing in gui
	ImVec2 m_GlobalOrigin = { 0, 0 };
	// Local position of origin point, used as a reference where its located related to Canvas position
	ImVec2 m_Origin = { 0, 0 };
};