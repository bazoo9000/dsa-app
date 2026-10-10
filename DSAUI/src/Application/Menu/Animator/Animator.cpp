#include "../../../dsa_pch.h"

#include "Animator.h"

#include "Logger/Logger.h"

Animator::Animator(Canvas *canvas)
{
    if (canvas == nullptr) {
        LOG_GUI_ERROR("Can't create Animator, canvas is null");
        return;
    }

    m_AnimatedCanvas = canvas;
}

Animator::~Animator()
{
    m_AnimatedCanvas = nullptr;
}

void Animator::Start()
{
    if (IsPlaying() || IsPaused())
    {
        LOG_GUI_WARN("Can't start, is already playing or paused");
        return;
    }

    m_State = AnimatorState::Playing;
    m_CrtIndex = 0;
}

void Animator::Stop()
{
    if (IsStopped())
    {
        LOG_GUI_WARN("Can't stop, it's already stopped");
        return;
    }

    m_State = AnimatorState::Stopped;
    m_CrtIndex = 0;
}

void Animator::Pause()
{
    if (IsPaused())
    {
        LOG_GUI_WARN("Can't pause, it's not playing or already paused");
        return;
    }

    m_State = AnimatorState::Paused;
}

void Animator::Resume()
{
    if (!IsPaused())
    {
        LOG_GUI_WARN("Can't resume, it's not paused");
        return;
    }

    m_State = AnimatorState::Playing;
}

void Animator::Next()
{
    if (m_CrtIndex >= m_StepCount)
    {
        return;
    }
    m_CrtIndex++;
}

void Animator::Prev()
{
    if (m_CrtIndex == 0)
    {
        return;
    }
    m_CrtIndex--;
}
