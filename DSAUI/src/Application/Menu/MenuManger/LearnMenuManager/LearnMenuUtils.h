#pragma once

#include "../../../Widget/Shape/DrawableRectangle.h"


// TODO: rename this to canvas utils instead
class LearnMenuUtils
{
public:
	static void SwapRectangles(std::vector<DrawableShape*>& shapes, uint32_t i1, uint32_t i2);
};
