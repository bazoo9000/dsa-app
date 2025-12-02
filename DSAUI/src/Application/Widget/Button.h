#pragma once

#include "../../dsa_pch.h"
#include "Widget.h"

class Button : public Widget
{
public:
	Button(std::string id, std::string label);
	~Button();

public:
	virtual inline void Draw() override;

public:
	template<typename Func, typename... Params>
	void SetCallback(Func&& func, Params&&... params)
	{
		m_Callback = std::bind(std::forward<Func>(func), std::forward<Params>(params)...);
	}

private:
	std::function<void()> m_Callback;
	std::string m_Label;
};
