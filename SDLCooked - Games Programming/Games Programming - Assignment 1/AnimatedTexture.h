#ifndef AnimatedTexture_H
#define AnimatedTexture_H

#include "Timer.h"
#include "Texture.h"

namespace ChrisFramework {

	class AnimatedTexture : public Texture {

	public:

		enum WRAP_MODE { once = 0, loop = 1 };
		enum ANIM_DIR { horizontal = 0, vertical = 0 };

	private:

		Timer* mTimer;

		int startX;
		int startY;

		float animTimer;
		float mAnimSpeed;
		float timePerFrame;

		int mFrameCount;

		WRAP_MODE wrapMode;
		ANIM_DIR animDirection;

		bool animIsDone;

	public:

		AnimatedTexture(string fileName, int x, int y, int w, int h, int frameCount, float animSpeed, ANIM_DIR animDir);
		~AnimatedTexture();

		void WrapMode(WRAP_MODE mode);

		void ResetAnimation();
		bool IsAnimating();

		void Update();
	};
}

#endif // !AnimatedTextre_H

