#ifndef Timer_H
#define Timer_H

#include "SDL.h"

namespace ChrisFramework {

	class Timer
	{

	private:

		static Timer* sInstance;

		unsigned int startTicks;
		unsigned int elapsedTicks;
		float deltaTime;
		float timeScale;

	public:

		static Timer* Instance();
		static void Release();

		void Reset();
		float DeltaTime();

		void TimeScale(float t);
		float TimeScale();

		void Update();

	private:

		Timer();
		~Timer();
	};
}
#endif // !Timer_H
