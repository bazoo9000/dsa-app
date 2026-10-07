#pragma once

class Time
{
public:
    static void CalculateTime();

public:
    static float GetDeltaTime();
    static float GetUnscaledDeltaTime();
    static float GetTime();
    static void ResetTime();
    static float GetTimeScale();
    static void SetTimeScale(float scale);

private:
    static float s_Time;
    static float s_DeltaTime;
    static float s_TimeScale;
};