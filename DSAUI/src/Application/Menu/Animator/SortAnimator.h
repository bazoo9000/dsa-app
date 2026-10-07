#pragma once

#include "Animator.h"

class SortAnimator : public Animator
{
public:
    SortAnimator(Canvas* canvas, const std::vector<uint32_t>& indexes, const std::vector<Step>& steps);
    ~SortAnimator() = default;

public:
    virtual void Start() override;
    virtual void Stop() override;
    virtual void AnimateCurrentStep() override;

private:
    void sortDone(uint32_t i);
    void sortSelect(uint32_t i);
    void sortCompare(uint32_t i1, uint32_t i2);
    void sortSwap(uint32_t i1, uint32_t i2);
    void sortReset();

private:
    std::vector<Step> m_AnimationSteps; // maybe should i std::move it?
    std::vector<uint32_t> m_Indexes;
    uint32_t m_LastIndex1 = UINT32_MAX;
    uint32_t m_LastIndex2 = UINT32_MAX;
};