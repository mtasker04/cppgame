#include <cppgame/GameTime.h>

#include <iostream>

void GameTime::Start() {
    m_StartTime = std::chrono::high_resolution_clock::now();
    m_LastFrameTime = m_StartTime;
}
void GameTime::Update() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    m_ElapsedTime = std::chrono::duration_cast<duration_t>(currentTime - m_StartTime);
    m_DeltaTime = std::chrono::duration_cast<duration_t>(currentTime - m_LastFrameTime);
    m_LastFrameTime = currentTime;
}

float GameTime::DurationToSeconds(duration_t duration) {
    return duration.count();
}

duration_t GameTime::GetDeltaTime() {
    return m_DeltaTime;
}
duration_t GameTime::GetElapsedTime() {
    return m_ElapsedTime;
}

time_point_t GameTime::GetTime() {
	return std::chrono::high_resolution_clock::now();
}
duration_t GameTime::GetDuration(time_point_t start, time_point_t end) {
    return std::chrono::duration_cast<duration_t>(end - start);
}

float GameTime::GetDeltaTimeSeconds() {
    return m_DeltaTime.count();
}
float GameTime::GetElapsedTimeSeconds() {
    return m_ElapsedTime.count();
}

duration_t GameTime::m_DeltaTime;
duration_t GameTime::m_ElapsedTime;
time_point_t GameTime::m_StartTime;
time_point_t GameTime::m_LastFrameTime;