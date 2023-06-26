#include "Timer.h"

namespace ChrisFramework {

	Timer* Timer::sInstance = NULL;

	Timer* Timer::Instance()
	{
		if (sInstance == NULL)
			sInstance = new Timer();

		return sInstance;
	}

	void Timer::Release()
	{
		delete sInstance;
		sInstance = NULL;
	}

	Timer::Timer()
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Timer Constructed with Param(%p)\n", this);

		Reset();
		elapsedTicks = 0;
		deltaTime = 0.0f;
		timeScale = 1.0f;
	}

	Timer::~Timer()
	{

	}

	void Timer::Reset()
	{
		startTicks = SDL_GetTicks();
	}

	float Timer::DeltaTime()
	{
		return deltaTime * TimeScale();
	}

	void Timer::TimeScale(float t)
	{
		timeScale = t;
	}

	float Timer::TimeScale()
	{
		return timeScale;
	}

	void Timer::Update()
	{
		elapsedTicks = SDL_GetTicks() - startTicks;
		deltaTime = elapsedTicks * 0.001f;
	}
}