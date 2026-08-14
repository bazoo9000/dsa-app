#pragma once

// Observer pattern btw
class IAppReceiver
{
public:
	virtual void ChangeMenu(std::string id) = 0;
	virtual void Close() = 0;
	virtual std::unordered_map<std::string, std::string> RequestTokens(std::vector<std::string> tokens) = 0;
	virtual std::string RequestToken(std::string token) = 0;
	virtual ImVec2 GetWindowSize() = 0;
	// TODO: add more requests, for example request for tokens, to isolate cache managers inside app
};
