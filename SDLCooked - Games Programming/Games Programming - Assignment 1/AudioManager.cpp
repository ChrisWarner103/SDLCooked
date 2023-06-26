#include "AudioManager.h"

namespace ChrisFramework {

	AudioManager* AudioManager::sInstance = NULL;

	AudioManager* AudioManager::Instance()
	{
		if (sInstance == NULL)
			sInstance = new AudioManager();

		return sInstance;
	}

	void AudioManager::Release()
	{
		delete sInstance;
		sInstance = NULL;
	}

	AudioManager::AudioManager()
	{
		mAssetManager = AssetManager::Instance();
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Audio Manager Constructed with Param(%p)\n", this);

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		{
			printf("Mixer Initialization Error: %s\n", Mix_GetError());
		}
	}

	AudioManager::~AudioManager()
	{
		mAssetManager = NULL;
		Mix_Quit();
	}

	void AudioManager::PlayMusic(string fileName, int loops)
	{
		Mix_PlayMusic(mAssetManager->GetMusic(fileName), loops);
	}

	void AudioManager::PauseMusic()
	{
		if (Mix_PlayingMusic() != 0)
			Mix_PauseMusic();
	}

	void AudioManager::ResumeMusic()
	{
		if (Mix_PausedMusic() != 0)
			Mix_ResumeMusic();
	}

	void AudioManager::PlaySFX(string fileName, int loops, int channel)
	{
		Mix_PlayChannel(channel, mAssetManager->GetSFX(fileName), loops);
	}

}