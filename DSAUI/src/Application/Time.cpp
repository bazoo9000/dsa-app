#include "../dsa_pch.h"

#include "Time.h"

#include "Logger/Logger.h"

float Time::s_Time = 0.0f;
float Time::s_TimeScale = 1.0f;
float Time::s_DeltaTime = 0.0f;

void Time::CalculateTime()
{
    const ImGuiIO& io = ImGui::GetIO();

    s_DeltaTime = io.DeltaTime;
    s_Time += s_DeltaTime;
}

float Time::GetDeltaTime()
{
    return s_DeltaTime * s_TimeScale;
}

float Time::GetUnscaledDeltaTime()
{
    return s_DeltaTime;
}

float Time::GetTime()
{
    return s_Time;
}

void Time::ResetTime()
{
    s_Time = 0.0f;
    s_DeltaTime = 0.0f;

    LOG_GUI_INFO("Time has been reset");
}

float Time::GetTimeScale()
{
    return s_TimeScale;
}

void Time::SetTimeScale(float scale)
{
    s_TimeScale = scale;
}