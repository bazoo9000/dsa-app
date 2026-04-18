#include "../../../dsa_pch.h"

#include "Circle.h"
#include "Logger/Logger.h"

Circle::Circle(ImVec2 center, float radius)
	: m_Radius(radius)
{
	m_Origin = center;
}

Circle::~Circle()
{
}