#include <GTime.h>

#include <iostream>

void Time::Start() {
    m_StartTime = std::chrono::high_resolution_clock::now();
    m_LastFrameTime = m_StartTime;
}
void Time::Update() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    m_ElapsedTime = std::chrono::duration_cast<duration_t>(currentTime - m_StartTime);
    m_DeltaTime = std::chrono::duration_cast<duration_t>(currentTime - m_LastFrameTime);
    m_LastFrameTime = currentTime;
}

float Time::DurationToSeconds(duration_t duration) {
    return duration.count();
}

duration_t Time::GetDeltaTime() {
    return m_DeltaTime;
}
duration_t Time::GetElapsedTime() {
    return m_ElapsedTime;
}

time_point_t Time::GetTime() {
	return std::chrono::high_resolution_clock::now();
}
duration_t Time::GetDuration(time_point_t start, time_point_t end) {
    return std::chrono::duration_cast<duration_t>(end - start);
}

float Time::GetDeltaTimeSeconds() {
    return m_DeltaTime.count();
}
float Time::GetElapsedTimeSeconds() {
    return m_ElapsedTime.count();
}

duration_t Time::m_DeltaTime;
duration_t Time::m_ElapsedTime;
time_point_t Time::m_StartTime;
time_point_t Time::m_LastFrameTime;