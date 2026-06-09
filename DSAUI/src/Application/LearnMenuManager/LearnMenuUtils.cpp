#include "../../dsa_pch.h"

#include "LearnMenuUtils.h"

#include "../Widget/Shape/DrawableRectangle.h"
#include "Logger/Logger.h"

uint32_t LearnMenuUtils::s_LastIndex1 = UINT32_MAX;
uint32_t LearnMenuUtils::s_LastIndex2 = UINT32_MAX;
uint32_t LearnMenuUtils::s_DelayMilis = 1;

void LearnMenuUtils::SortSetDelay(uint32_t milis)
{
    if (milis > 1000)
    {
        LOG_GUI_WARN("Step delay in milliseconds is more than 1000ms, this may get too slow/boring");
    }
    s_DelayMilis = milis;
}

void LearnMenuUtils::SortDone(Canvas* canvas)
{
    std::vector<DrawableShape*>& shapes = canvas->GetAllDrawableShapes();
    uint32_t size = shapes.size();

    // iterate all with delay and make them green
}

void LearnMenuUtils::SortSelect(Canvas* canvas, uint32_t i)
{
    std::vector<DrawableShape*>& shapes = canvas->GetAllDrawableShapes();
    uint32_t size = shapes.size();

    if (s_LastIndex1 != UINT32_MAX) { shapes[s_LastIndex1]->SetColor(COLOR_NEUTRAL); }
    if (s_LastIndex2 != UINT32_MAX) { shapes[s_LastIndex2]->SetColor(COLOR_NEUTRAL); s_LastIndex2 = UINT32_MAX; }
    s_LastIndex1 = i;

    if (i > size)
    {
        return;
    }

    shapes[i]->SetColor(COLOR_SELECTED);
}

void LearnMenuUtils::SortCompare(Canvas* canvas, uint32_t i1, uint32_t i2)
{
    std::vector<DrawableShape*>& shapes = canvas->GetAllDrawableShapes();
    uint32_t size = shapes.size();

    if (s_LastIndex1 != UINT32_MAX) { shapes[s_LastIndex1]->SetColor(COLOR_NEUTRAL); }
    if (s_LastIndex2 != UINT32_MAX) { shapes[s_LastIndex2]->SetColor(COLOR_NEUTRAL); }
    s_LastIndex1 = i1;
    s_LastIndex2 = i2;

    if (i1 == i2)
    {
        return;
    }

    if (i1 > size || i2 > size)
    {
        return;
    }

    shapes[i1]->SetColor(COLOR_COMPARE);
    shapes[i2]->SetColor(COLOR_COMPARE);
}

void LearnMenuUtils::SortSwap(Canvas* canvas, uint32_t i1, uint32_t i2)
{
    std::vector<DrawableShape*>& shapes = canvas->GetAllDrawableShapes();
    uint32_t size = shapes.size();

    if (s_LastIndex1 != UINT32_MAX) { shapes[s_LastIndex1]->SetColor(COLOR_NEUTRAL); }
    if (s_LastIndex2 != UINT32_MAX) { shapes[s_LastIndex2]->SetColor(COLOR_NEUTRAL); }
    s_LastIndex1 = i1;
    s_LastIndex2 = i2;

    if (i1 == i2)
    {
        return;
    }

    if (i1 > size || i2 > size)
    {
        return;
    }

    DrawableRectangle* rect1 = (DrawableRectangle*)shapes[i1];
    DrawableRectangle* rect2 = (DrawableRectangle*)shapes[i2];

    ImVec2 r1Origin = rect1->GetOrigin();
    ImVec2 r2Origin = rect2->GetOrigin();
    ImVec2 r1End = rect1->GetEnd();
    ImVec2 r2End = rect2->GetEnd();

    rect1->SetColor(COLOR_SWAP);
    rect2->SetColor(COLOR_SWAP);

    rect1->SetOrigin(r2Origin);
    rect2->SetOrigin(r1Origin);
    rect1->SetEnd({ r2End.x, r1End.y });
    rect2->SetEnd({ r1End.x, r2End.y });

    auto temp = shapes[i1];
    shapes[i1] = shapes[i2];
    shapes[i2] = temp;
}
