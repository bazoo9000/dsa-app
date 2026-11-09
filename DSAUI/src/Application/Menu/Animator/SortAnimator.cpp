#include "../../../dsa_pch.h"

#include "SortAnimator.h"

#include "../MenuManger/LearnMenuManager/LearnMenuUtils.h" // this will be instead CanvasUtils later
#include "../../Color.h"

#include "Logger/Logger.h"

SortAnimator::SortAnimator(Canvas* canvas)
    : Animator(canvas)
{
    // shuffle begin
    std::vector<DrawableShape*>& shapes = canvas->GetAllDrawableShapes();
    m_Indexes = createVector(shapes.size(), true);
    std::vector<uint32_t> currentOrder = createVector(m_Indexes.size());
    for (int i = 0; i < m_Indexes.size(); i++)
    {
        for (int j = i; j < m_Indexes.size(); j++)
        {
            if (currentOrder[j] == m_Indexes[i])
            {
                LearnMenuUtils::SwapRectangles(shapes, i, j);
                std::swap(currentOrder[i], currentOrder[j]);
                break;
            }
        }
    }
    // shuffle end

    // sort begin
    // bubble sort as an example
    // TODO: move step generation to core
    for (int i = 0; i < m_Indexes.size(); i++)
    {
        for (int j = i + 1 ; j < m_Indexes.size(); j++)
        {
            m_AnimationSteps.emplace_back(i, j, SortActionType::COMPARE);
            if (m_Indexes[i] > m_Indexes[j])
            {
                std::swap(m_Indexes[i], m_Indexes[j]);
                m_AnimationSteps.emplace_back(i, j, SortActionType::SWAP);
            }
        }

        m_AnimationSteps.emplace_back(i, 0, SortActionType::DONE);
    }
    // sort end

    if (m_AnimationSteps.empty())
    {
        LOG_GUI_WARN("Step list is empty");
    }

    m_StepCount = m_AnimationSteps.size();
}

void SortAnimator::Start()
{
    Animator::Start();
    m_LastIndex1 = UINT32_MAX;
    m_LastIndex2 = UINT32_MAX;
    sortReset();
}

void SortAnimator::Stop()
{
    Animator::Stop();
    m_LastIndex1 = UINT32_MAX;
    m_LastIndex2 = UINT32_MAX;

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

    sortReset();
}

void SortAnimator::AnimateCurrentStep()
{
    if (m_AnimatedCanvas == nullptr)
    {
        LOG_GUI_ERROR("Can't animate, canvas is null");
        return;
    }

    if (m_CrtIndex >= m_StepCount)
    {
        m_State = AnimatorState::Finished;
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

std::vector<uint32_t> SortAnimator::createVector(uint32_t max, bool shuffle)
{
    if (max == 0)
    {
        // TODO: should this be fatal?
        LOG_GUI_FATAL("Can't create vector, max value is 0");
        exit(1);
    }

    std::vector<uint32_t> ret;
    ret.resize(max);

    std::iota(ret.begin(), ret.end(), 0);
    if (shuffle)
    {
        static std::mt19937 rng(std::random_device{}());
        std::shuffle(ret.begin(), ret.end(), rng);
    }

    return ret;
}

void SortAnimator::sortDone(uint32_t i)
{
    std::vector<DrawableShape*>& shapes = m_AnimatedCanvas->GetAllDrawableShapes();

    if (m_LastIndex1 != UINT32_MAX && shapes[m_LastIndex1]->GetColor() != COLOR_GREEN) { shapes[m_LastIndex1]->SetColor(COLOR_WHITE); }
    if (m_LastIndex2 != UINT32_MAX && shapes[m_LastIndex2]->GetColor() != COLOR_GREEN) { shapes[m_LastIndex2]->SetColor(COLOR_WHITE); m_LastIndex2 = UINT32_MAX; }
    m_LastIndex1 = i;

    if (i >= shapes.size())
    {
        return;
    }

    shapes[i]->SetColor(COLOR_GREEN);
}

void SortAnimator::sortSelect(uint32_t i)
{
    std::vector<DrawableShape*>& shapes = m_AnimatedCanvas->GetAllDrawableShapes();

    if (m_LastIndex1 != UINT32_MAX && shapes[m_LastIndex1]->GetColor() != COLOR_GREEN) { shapes[m_LastIndex1]->SetColor(COLOR_WHITE); }
    if (m_LastIndex2 != UINT32_MAX && shapes[m_LastIndex2]->GetColor() != COLOR_GREEN) { shapes[m_LastIndex2]->SetColor(COLOR_WHITE); m_LastIndex2 = UINT32_MAX; }
    m_LastIndex1 = i;

    if (i >= shapes.size())
    {
        return;
    }

    shapes[i]->SetColor(COLOR_YELLOW);
}

void SortAnimator::sortCompare(uint32_t i1, uint32_t i2)
{
    std::vector<DrawableShape*>& shapes = m_AnimatedCanvas->GetAllDrawableShapes();

    if (m_LastIndex1 != UINT32_MAX && shapes[m_LastIndex1]->GetColor() != COLOR_GREEN) { shapes[m_LastIndex1]->SetColor(COLOR_WHITE); }
    if (m_LastIndex2 != UINT32_MAX && shapes[m_LastIndex2]->GetColor() != COLOR_GREEN) { shapes[m_LastIndex2]->SetColor(COLOR_WHITE); }
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

    shapes[i1]->SetColor(COLOR_BLUE);
    shapes[i2]->SetColor(COLOR_BLUE);
}

void SortAnimator::sortSwap(uint32_t i1, uint32_t i2)
{
    std::vector<DrawableShape*>& shapes = m_AnimatedCanvas->GetAllDrawableShapes();

    if (m_LastIndex1 != UINT32_MAX && shapes[m_LastIndex1]->GetColor() != COLOR_GREEN) { shapes[m_LastIndex1]->SetColor(COLOR_WHITE); }
    if (m_LastIndex2 != UINT32_MAX && shapes[m_LastIndex2]->GetColor() != COLOR_GREEN) { shapes[m_LastIndex2]->SetColor(COLOR_WHITE); }
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

    shapes[i1]->SetColor(COLOR_RED);
    shapes[i2]->SetColor(COLOR_RED);
    LearnMenuUtils::SwapRectangles(shapes, i1, i2);

    std::swap(m_Indexes[i1], m_Indexes[i2]);
}

void SortAnimator::sortReset()
{
    for (auto shape : m_AnimatedCanvas->GetAllDrawableShapes())
    {
        shape->SetColor(COLOR_WHITE);
    }
}
