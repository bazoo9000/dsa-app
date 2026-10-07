#pragma once

#include "../../Widget/Canvas.h"

enum class SortActionType
{
    SWAP, COMPARE, SELECT, DONE
};

struct Step {
    int i1;
    int i2;
    SortActionType type;

    Step (int i1, int i2, SortActionType type)
        : i1(i1), i2(i2), type(type) {}
};

// TODO: add other types of animators, for search, sort, graphs etc
class Animator
{
public:
    Animator(Canvas* canvas);
    virtual ~Animator();

public:
    virtual void Start(); // starts the animation from the beginning, cant start if its playing or paused
    virtual void Stop(); // stops animation and resets to beginning, only stops if its playing or paused
    void Pause(); // pauses the animation at the current step, cant be paused if already paused or not played
    void Resume(); // resumes the animation from where it was paused, cant resume if its playing
    void Update(); // proceeds to next frame, when not paused, used in per frame update functions
    void Next(); // proceeds to next step/frame, only when paused
    void Prev(); // proceeds to previous step/frame, only when paused
    virtual void AnimateCurrentStep() = 0; // animates current step, based on type of algorithm used

public:
    bool IsPlaying() { return m_Playing; }
    bool IsPaused() { return m_Paused; }

protected:
    Canvas* m_AnimatedCanvas;
    uint32_t m_CrtIndex = 0;
    bool m_Paused = false;
    bool m_Playing = false;

protected:
    // TODO: later add a const static class for colors
    static constexpr ImU32 COLOR_DONE = IM_COL32(0, 255, 0, 255);       // green
    static constexpr ImU32 COLOR_SELECTED = IM_COL32(255, 255, 0, 255); // yellow
    static constexpr ImU32 COLOR_COMPARE = IM_COL32(0, 0, 255, 255);    // blue
    static constexpr ImU32 COLOR_SWAP = IM_COL32(255, 0, 0, 255);       // red
    static constexpr ImU32 COLOR_NEUTRAL = IM_COL32_WHITE;              //
};
