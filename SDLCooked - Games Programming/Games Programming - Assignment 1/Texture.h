#ifndef Texture_h
#define Texture_h

#include "SDL.h"
#include "GameEntity.h"
#include "AssetManager.h"

namespace ChrisFramework {

	class Texture : public GameEntity {

	protected:

		SDL_Texture* mTexture;

		Graphics* mGraphics;

		int width;
		int height;

		bool clipped;
		SDL_Rect mRenderRect;
		SDL_Rect mClipRect;


	public:

		Texture(string fileName);
		Texture(string fileName, int x, int y, int w, int h);
		Texture(string text, string fontPath, int size, SDL_Color color);
		~Texture();

		Vector2 ScaleDimentions();

		void Update();

		virtual void Render();

	};
}
#endif // !Texture_h

