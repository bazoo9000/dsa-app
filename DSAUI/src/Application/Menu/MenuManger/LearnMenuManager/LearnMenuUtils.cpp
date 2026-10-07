#include "../../../../dsa_pch.h"

#include "LearnMenuUtils.h"

#include "../../../Widget/Shape/DrawableRectangle.h"
#include "Logger/Logger.h"

void LearnMenuUtils::SwapRectangles(std::vector<DrawableShape*>& shapes, uint32_t i1, uint32_t i2)
{
    DrawableRectangle* rect1 = (DrawableRectangle*)shapes[i1];
    DrawableRectangle* rect2 = (DrawableRectangle*)shapes[i2];

    ImVec2 r1Origin = rect1->GetOrigin();
    ImVec2 r2Origin = rect2->GetOrigin();
    ImVec2 r1End = rect1->GetEnd();
    ImVec2 r2End = rect2->GetEnd();

    rect1->SetOrigin(r2Origin);
    rect2->SetOrigin(r1Origin);
    rect1->SetEnd({ r2End.x, r1End.y });
    rect2->SetEnd({ r1End.x, r2End.y });

    auto temp = shapes[i1];
    shapes[i1] = shapes[i2];
    shapes[i2] = temp;
}
