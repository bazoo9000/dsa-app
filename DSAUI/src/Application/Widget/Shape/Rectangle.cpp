#include "../../../dsa_pch.h"

#include "Rectangle.h"

Rectangle::Rectangle(ImVec2 start, ImVec2 end)
	: m_End(end)
{
	m_Origin = start;
}

Rectangle::~Rectangle()
{
}

float Rectangle::GetWidth()
{
	return std::abs(m_Origin.y - m_End.y);
}

float Rectangle::GetHeight()
{
	return std::abs(m_Origin.x - m_End.x);
}
