#pragma once

#include <Generic.h>
#include <Updatable.h>

#include <chrono>

using duration_t = std::chrono::duration<float>;
using time_point_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

class GameTime
{
public:
	CPPGAPI static float DurationToSeconds(duration_t duration);

	CPPGAPI static duration_t GetDeltaTime();
	CPPGAPI static duration_t GetElapsedTime();

	CPPGAPI static time_point_t GetTime();
	CPPGAPI static duration_t GetDuration(time_point_t start, time_point_t end);

	CPPGAPI static float GetDeltaTimeSeconds();
	CPPGAPI static float GetElapsedTimeSeconds();

	static void Start();
	static void Update();

private:
	static duration_t m_DeltaTime;
	static duration_t m_ElapsedTime;
	static time_point_t m_StartTime;
	static time_point_t m_LastFrameTime;
};