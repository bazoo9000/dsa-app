#pragma once

#include "Widget.h"

class Button : public Widget
{
public:
	Button(std::string id, std::string label);
	~Button();

protected:
	virtual inline void drawWidget() override;

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
