#pragma once

#include "../../../Widget/Canvas.h"

class LearnMenuUtils
{
public:
	static void SortSetDelay(uint32_t milis);
	static void SortDone(Canvas* canvas);
	static void SortSelect(Canvas* canvas, uint32_t i);
	static void SortCompare(Canvas* canvas, uint32_t i1, uint32_t i2);
	static void SortSwap(Canvas* canvas, uint32_t i1, uint32_t i2);

private:
	static uint32_t s_LastIndex1;
	static uint32_t s_LastIndex2;
	static uint32_t s_DelayMilis; // milisecond delay step animation

private:
	static constexpr ImU32 COLOR_DONE = IM_COL32(0, 255, 0, 255);       // green
	static constexpr ImU32 COLOR_SELECTED = IM_COL32(255, 255, 0, 255); // yellow
	static constexpr ImU32 COLOR_COMPARE = IM_COL32(0, 0, 255, 255);    // blue
	static constexpr ImU32 COLOR_SWAP = IM_COL32(255, 0, 0, 255);       // red
	static constexpr ImU32 COLOR_NEUTRAL = IM_COL32_WHITE;              // 
};