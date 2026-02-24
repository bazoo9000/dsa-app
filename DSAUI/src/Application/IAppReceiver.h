#pragma once

// Observer pattern btw
class IAppReceiver
{
public:
	virtual void ChangeScreen(std::string id) = 0;
	virtual void Close() = 0;
};