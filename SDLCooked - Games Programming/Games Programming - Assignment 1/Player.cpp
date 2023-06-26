#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

bool Player::IgnoreCollisions()
{
	return !mActive || isWalking;
}

Player::Player()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player Constructed with Param(%p)\n", this);

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mActive = true;
	isWalking = true;
	mWasHit = false;

	mWalkAnimation = new AnimatedTexture("Player1.png", 0, 0, 64, 64, 6, 0.8f, AnimatedTexture::horizontal);
	mIdleAnimation = new Texture("Player1.png", 0, 0, 64, 64);
	collider = new Texture("BoxCollider.png");
	mWalkAnimation->Parent(this);
	mIdleAnimation->Parent(this);
	collider->Parent(this);
	mWalkAnimation->Pos(VEC2_ZERO);
	mIdleAnimation->Pos(VEC2_ZERO);
	collider->Pos(Vector2(0.0f, -32.0f));

	mWalkAnimation->Scale(Vector2(1.25f, 1.25f));
	mIdleAnimation->Scale(Vector2(1.25f, 1.25f));
	collider->Scale(Vector2(0.75f, 0.75f));

	movementSpeed = 250.0f;
	moveBoundsX = Vector2(275.0f, 1010.0f);
	moveBoundsY = Vector2(220.0f, 570.0f);

	//AddCollider(new BoxCollider(mWalkAnimation->ScaleDimentions()), this, Vector2(200.0f, 500.0f));

	//ID = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Player);
}

Player::~Player()
{
	mTimer = NULL;
	mInput = NULL;

	delete mWalkAnimation;
	mWalkAnimation = NULL;

	delete mIdleAnimation;
	mIdleAnimation = NULL;
}

void Player::HandleMovement()
{
	if (mInput->KeyDown(SDL_SCANCODE_W))
	{
		Translate(-VEC2_UP * movementSpeed * mTimer->DeltaTime());
		isWalking = true;
	}
	else
	{
		isWalking = false;
	}

	if (mInput->KeyDown(SDL_SCANCODE_S))
	{
		Translate(VEC2_UP * movementSpeed * mTimer->DeltaTime());
		isWalking = true;
	}
	else
	{
		isWalking = false;
	}

	if (mInput->KeyDown(SDL_SCANCODE_A))
	{
		Translate(-VEC2_RIGHT * movementSpeed * mTimer->DeltaTime());
		isWalking = true;
	}
	else {
		isWalking = false;
	}

	if (mInput->KeyDown(SDL_SCANCODE_D))
	{
		Translate(VEC2_RIGHT * movementSpeed * mTimer->DeltaTime());
		isWalking = true;
	}
	else {
		isWalking = false;
	}

	if (mInput->KeyDown(SDL_SCANCODE_LSHIFT))
	{
		movementSpeed = 400.0f;
	}
	else if (mInput->KeyReleased(SDL_SCANCODE_LSHIFT))
	{
		movementSpeed = 250.0f;
	}

	Vector2 mousePosition = mInput->MousePosition();

	float angle = AngleBetweenTwoPoints(position(), mousePosition);

	Rotation(angle - 90.0f);
		
	Vector2 pos = position(local);
	if (pos.x < moveBoundsX.x)
		pos.x = moveBoundsX.x;
	else if (pos.x > moveBoundsX.y)
		pos.x = moveBoundsX.y;

	if (pos.y < moveBoundsY.x)
		pos.y = moveBoundsY.x;
	else if (pos.y > moveBoundsY.y)
		pos.y = moveBoundsY.y;

	Pos(pos);
}

void Player::Active(bool active)
{
	mActive = active;
}

bool Player::IsWalking()
{
	return isWalking;
}

int Player::Score()
{
	return score;
}

void Player::AddScore(int change)
{
	score += change;
}

Vector2 Player::playerColliderPosition()
{
	GetColliderPosition();
	return colliderBounds;
}

void Player::GetColliderPosition()
{
	colliderBounds = collider->position(world);
}

void Player::Hit(PhysicsEntity* other)
{
	mWasHit = true;
}

bool Player::WasHit()
{
	return mWasHit;
}


void Player::Update()
{
	if (IsWalking())
	{
		mWalkAnimation->Update();
		HandleMovement();
		if (mWasHit)
			mWasHit = false;
	}
	else
	{
		HandleMovement();
	}
}

void Player::Render()
{
	if (mActive)
	{

		if (IsWalking())
		{
			mWalkAnimation->Render();
		}
		else
		{
			mIdleAnimation->Render();
		}
	}

}
