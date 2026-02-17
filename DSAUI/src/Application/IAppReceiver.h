#pragma once

#include "../dsa_pch.h"

// Observer pattern btw
class IAppReceiver
{
public:
	virtual void ChangeScreen(std::string id) = 0;
	virtual void Close() = 0;
};