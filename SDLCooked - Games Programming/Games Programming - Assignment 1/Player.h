#ifndef Player_H
#define Player_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "PhysicsManager.h"

using namespace ChrisFramework;

class Player : public PhysicsEntity {

private:

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mActive;
	bool isWalking;
	bool mWasHit;

	int score;

	AnimatedTexture* mWalkAnimation;
	Texture* mIdleAnimation;
	Texture* collider;

	float movementSpeed;
	Vector2 moveBoundsX;
	Vector2 moveBoundsY;
	Vector2 colliderBounds;

public:

	bool hasMeat = false;
	bool hasCheese = false;
	bool hasLettuce = false;
	bool hasBun = false;
	bool hasPlate = false;
	bool atGoal = false;

private:

	bool IgnoreCollisions() override;

	void HandleMovement();

public:

	Player();
	~Player();

	void Active(bool active);

	void Hit(PhysicsEntity* other) override;
	bool WasHit();

	bool IsWalking();

	int Score();
	void AddScore(int change);

	Vector2 playerColliderPosition();
	void GetColliderPosition();

	void Update();

	void Render();


};
#endif // !Player_H

