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
    if (m_Playing || m_Paused)
    {
        LOG_GUI_WARN("Can't start, is already playing or paused");
        return;
    }

    m_Playing = true;
    m_Paused = false;
    m_CrtIndex = 0;
}

void Animator::Stop()
{
    if (!m_Playing && !m_Paused)
    {
        LOG_GUI_WARN("Can't stop, it's already stopped");
        return;
    }

    m_Playing = false;
    m_Paused = false;
    m_CrtIndex = 0;
}

void Animator::Pause()
{
    if (!m_Playing || m_Paused)
    {
        LOG_GUI_WARN("Can't pause, it's not playing or already paused");
        return;
    }

    m_Playing = false;
    m_Paused = true;
}

void Animator::Resume()
{
    if (!m_Paused)
    {
        LOG_GUI_WARN("Can't resume, it's not paused");
        return;
    }

    m_Playing = true;
    m_Paused = false;
}

void Animator::Update()
{
    if (!m_Playing || m_Paused)
    {
        return;
    }

    AnimateCurrentStep();
    Next();
}

void Animator::Next()
{
    m_CrtIndex++;
}

void Animator::Prev()
{
    m_CrtIndex--;
}
