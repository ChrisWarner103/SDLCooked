#ifndef AssetManager_h
#define AssetManager_h

#include "Graphics.h"
#include <SDL_mixer.h>
#include <map>
#include <vector>

namespace ChrisFramework {

	class AssetManager {

	private:

		static AssetManager* sInstance;

		map<string, SDL_Texture*> mTexture;
		map<string, SDL_Texture*> mText;
		map<string, TTF_Font*> mFonts;
		map<string, Mix_Music*> mMusic;
		map<string, Mix_Chunk*> mSFX;

	public:

		static AssetManager* Instance();
		static void Release();

		SDL_Texture* GetTexture(string fileName);
		SDL_Texture* GetText(string text, string fileName, int size, SDL_Color color);

		Mix_Music* GetMusic(string fileName);
		Mix_Chunk* GetSFX(string fileName);

	private:

		AssetManager();
		~AssetManager();

		TTF_Font* GetFont(string fileName, int size);
	};
}
#endif // !AssetManager_h

