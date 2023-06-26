#ifndef AudioManager_H
#define AudioManager_H

#include "AssetManager.h"

namespace ChrisFramework {

	class AudioManager {

	private:

		static AudioManager* sInstance;

		AssetManager* mAssetManager;

	public:

		static AudioManager* Instance();
		static void Release();

		void PlayMusic(string fileName, int loops = -1);
		void PauseMusic();
		void ResumeMusic();

		void PlaySFX(string fileName, int loops = 0, int channel = 0);

	private:

		AudioManager();
		~AudioManager();

	};
}
#endif // !AudioManager_H

