#include "../../../dsa_pch.h"

#include "SortAnimator.h"

#include "../MenuManger/LearnMenuManager/LearnMenuUtils.h" // this will be instead CanvasUtils later

#include "Logger/Logger.h"

SortAnimator::SortAnimator(Canvas* canvas, const std::vector<uint32_t>& indexes, const std::vector<Step>& steps)
    : Animator(canvas)
{
    if (steps.empty())
    {
        LOG_GUI_WARN("Step list is empty");
    }

    m_AnimationSteps = steps;
    m_Indexes = indexes;
}

void SortAnimator::Start()
{
    Animator::Start();
    m_LastIndex1 = UINT32_MAX;
    m_LastIndex2 = UINT32_MAX;
}

void SortAnimator::Stop()
{
    Animator::Stop();
    m_LastIndex1 = UINT32_MAX;
    m_LastIndex2 = UINT32_MAX;
    sortReset();
}

void SortAnimator::AnimateCurrentStep()
{
    if (m_AnimatedCanvas == nullptr)
    {
        LOG_GUI_ERROR("Can't animate, canvas is null");
        return;
    }

    if (m_CrtIndex >= m_AnimationSteps.size())
    {
        Stop();
        return;
    }

    Step step = m_AnimationSteps[m_CrtIndex];
    switch (step.type)
    {
        case SortActionType::SWAP:
            sortSwap(step.i1, step.i2);
            break;
        case SortActionType::COMPARE:
            sortCompare(step.i1, step.i2);
            break;
        case SortActionType::SELECT:
            sortSelect(step.i1);
            break;
        case SortActionType::DONE:
            sortDone(step.i1);
            break;
    }
}

void SortAnimator::sortDone(uint32_t i)
{
    std::vector<DrawableShape*>& shapes = m_AnimatedCanvas->GetAllDrawableShapes();

    if (m_LastIndex1 != UINT32_MAX && shapes[m_LastIndex1]->GetColor() != COLOR_DONE) { shapes[m_LastIndex1]->SetColor(COLOR_NEUTRAL); }
    if (m_LastIndex2 != UINT32_MAX && shapes[m_LastIndex2]->GetColor() != COLOR_DONE) { shapes[m_LastIndex2]->SetColor(COLOR_NEUTRAL); m_LastIndex2 = UINT32_MAX; }
    m_LastIndex1 = i;

    if (i >= shapes.size())
    {
        return;
    }

    shapes[i]->SetColor(COLOR_DONE);
}

void SortAnimator::sortSelect(uint32_t i)
{
    std::vector<DrawableShape*>& shapes = m_AnimatedCanvas->GetAllDrawableShapes();

    if (m_LastIndex1 != UINT32_MAX && shapes[m_LastIndex1]->GetColor() != COLOR_DONE) { shapes[m_LastIndex1]->SetColor(COLOR_NEUTRAL); }
    if (m_LastIndex2 != UINT32_MAX && shapes[m_LastIndex2]->GetColor() != COLOR_DONE) { shapes[m_LastIndex2]->SetColor(COLOR_NEUTRAL); m_LastIndex2 = UINT32_MAX; }
    m_LastIndex1 = i;

    if (i >= shapes.size())
    {
        return;
    }

    shapes[i]->SetColor(COLOR_SELECTED);
}

void SortAnimator::sortCompare(uint32_t i1, uint32_t i2)
{
    std::vector<DrawableShape*>& shapes = m_AnimatedCanvas->GetAllDrawableShapes();

    if (m_LastIndex1 != UINT32_MAX && shapes[m_LastIndex1]->GetColor() != COLOR_DONE) { shapes[m_LastIndex1]->SetColor(COLOR_NEUTRAL); }
    if (m_LastIndex2 != UINT32_MAX && shapes[m_LastIndex2]->GetColor() != COLOR_DONE) { shapes[m_LastIndex2]->SetColor(COLOR_NEUTRAL); }
    m_LastIndex1 = i1;
    m_LastIndex2 = i2;

    if (i1 == i2)
    {
        return;
    }

    if (i1 >= shapes.size() || i2 >= shapes.size())
    {
        return;
    }

    shapes[i1]->SetColor(COLOR_COMPARE);
    shapes[i2]->SetColor(COLOR_COMPARE);
}

void SortAnimator::sortSwap(uint32_t i1, uint32_t i2)
{
    std::vector<DrawableShape*>& shapes = m_AnimatedCanvas->GetAllDrawableShapes();

    if (m_LastIndex1 != UINT32_MAX && shapes[m_LastIndex1]->GetColor() != COLOR_DONE) { shapes[m_LastIndex1]->SetColor(COLOR_NEUTRAL); }
    if (m_LastIndex2 != UINT32_MAX && shapes[m_LastIndex2]->GetColor() != COLOR_DONE) { shapes[m_LastIndex2]->SetColor(COLOR_NEUTRAL); }
    m_LastIndex1 = i1;
    m_LastIndex2 = i2;

    if (i1 == i2)
    {
        return;
    }

    if (i1 >= shapes.size() || i2 >= shapes.size())
    {
        return;
    }

    shapes[i1]->SetColor(COLOR_SWAP);
    shapes[i2]->SetColor(COLOR_SWAP);
    LearnMenuUtils::SwapRectangles(shapes, i1, i2);

    std::swap(m_Indexes[i1], m_Indexes[i2]);
}

void SortAnimator::sortReset()
{
    std::vector<DrawableShape*>& shapes = m_AnimatedCanvas->GetAllDrawableShapes();

    std::vector<uint32_t> sortedOrderIndexes;
    sortedOrderIndexes.resize(m_Indexes.size());
    std::iota(sortedOrderIndexes.begin(), sortedOrderIndexes.end(), 0);

    for (int i = 0; i < sortedOrderIndexes.size(); i++)
    {
        for (int j = i; j < sortedOrderIndexes.size(); j++)
        {
            if (sortedOrderIndexes[i] == m_Indexes[j])
            {
                LearnMenuUtils::SwapRectangles(shapes, i, j);
                std::swap(m_Indexes[i], m_Indexes[j]);
                break;
            }
        }
    }

    for (auto shape : shapes)
    {
        shape->SetColor(COLOR_NEUTRAL);
    }
}
