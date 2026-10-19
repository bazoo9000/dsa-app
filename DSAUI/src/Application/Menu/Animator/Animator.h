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

enum class AnimatorState {
    Stopped,
    Playing,
    Paused,
    Finished
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
    void Next(); // proceeds to next step/frame, only when paused
    void Prev(); // proceeds to previous step/frame, only when paused
    virtual void AnimateCurrentStep() = 0; // animates current step, based on type of algorithm used

public:
    bool IsPlaying() { return m_State == AnimatorState::Playing; }
    bool IsPaused() { return m_State == AnimatorState::Paused; }
    bool IsStopped() { return m_State == AnimatorState::Stopped; }
    bool IsFinished() { return m_State == AnimatorState::Finished; }

protected:
    Canvas* m_AnimatedCanvas;
    uint32_t m_StepCount = 0;
    uint32_t m_CrtIndex = 0;
    AnimatorState m_State = AnimatorState::Stopped;
};
