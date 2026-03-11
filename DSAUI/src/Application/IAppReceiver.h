#pragma once

// Observer pattern btw
class IAppReceiver
{
public:
	virtual void ChangeMenu(std::string id) = 0;
	virtual void Close() = 0;
	// TODO: add more requests, for example request for tokens, to isolate cache managers inside app
};