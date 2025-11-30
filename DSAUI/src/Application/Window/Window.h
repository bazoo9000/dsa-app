#pragma once

#include "../../dsa_pch.h"

class Window
{
public:
	Window(std::string title, int width, int height, bool vsync = true);
	~Window();

public:
	GLFWwindow* GetWindow() { return m_Window; }
	std::string GetTitle() { return m_Title; }
	ImVec2 GetWindowSize();

private:
	GLFWwindow* m_Window = nullptr;
	std::string m_Title;
	int m_Width = 0;
	int m_Height = 0;
};