#include "include\Timer.h"

GD_Tool::Mainframework::Timer::Timer()
	:m_secondsPerCount(0.0)
	,m_deltaTime(-1.0)
	,m_baseTime(0)
	,m_pausedTime(0)
	,m_prevTime(0)
	,m_currTime(0)
	,m_stopped(false)
{
	int64_t countsPerSecond; 
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecond);
	m_secondsPerCount = 1.0 / (double)countsPerSecond; 
}

float GD_Tool::Mainframework::Timer::Time() const
{
	if (m_stopped)
	{
		return (float)(((m_stopTime - m_pausedTime) - m_baseTime)*m_secondsPerCount);
	}
	else
	{
		return (float)(((m_currTime - m_pausedTime) - m_baseTime)*m_secondsPerCount);
	}
}

float GD_Tool::Mainframework::Timer::DeltaTime() const
{
	return (float)m_deltaTime;
}

void GD_Tool::Mainframework::Timer::Reset()
{
	int64_t currTime; 
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime); 

	m_baseTime = currTime; 
	m_prevTime = currTime; 
	m_stopTime = 0; 
	m_stopped = false; 
}

void GD_Tool::Mainframework::Timer::Start()
{
	int64_t startTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if (m_stopped)
	{
		m_pausedTime += (startTime - m_stopTime);
		m_prevTime = startTime;

		m_stopTime = 0;
		m_stopped = false;
	}
}

void GD_Tool::Mainframework::Timer::Stop()
{
	if (!m_stopped)
	{
		int64_t currTime; 
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime); 

		m_stopTime = currTime; 
		m_stopped = true; 
	}
}

void GD_Tool::Mainframework::Timer::Tick()
{
	if (m_stopped)
	{
		m_deltaTime = 0.0; 
		return;
	}
	int64_t currTime; 
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime); 
	m_currTime = currTime; 

	m_deltaTime = (m_currTime - m_prevTime)*m_secondsPerCount;

	m_prevTime = m_currTime; 

	if (m_deltaTime < 0.0)
		m_deltaTime = 0.0;
}
