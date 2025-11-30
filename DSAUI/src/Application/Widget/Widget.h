#pragma once

#include "../../dsa_pch.h"
#include "../Transform.h"
#include "../I18N/I18NFactory.h"
#include "../I18N/I18N.h"

class Widget
{
public:
	Widget() = default;
	virtual ~Widget() = default;

public:
	virtual inline void Draw() = 0;

protected:
	// std::vector<Widget*> m_Children; // Panel only
	Transform m_Transform; // relative pos/scale/rot
	std::string m_Id = "##";
};