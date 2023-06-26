#include "Chopping.h"
#include "ScreenManager.h"

Chopping::Chopping()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Chopping Board Constructed with Param(%p)\n", this);

	mInput = InputManager::Instance();
	mTimer = Timer::Instance();

	choppingCounter = new Texture("Environment/Chopping Counter.png");
	collider = new Texture("BoxCollider.png");

	choppingBar = new Texture("CookingProgressBar.png");
	choppingBarBack = new Texture("CookingProgressBarBack.png");

	choppingCounter->Parent(this);
	collider->Parent(this);

	choppingBar->Parent(this);
	choppingBarBack->Parent(this);

	collider->Pos(Vector2(0.0f, -32.0f));

	choppingBarLocation = (Vector2(0.0f, choppingCounter->ScaleDimentions().y * -0.7f));

	collider->Scale(Vector2(1.0f, 0.5f));

	choppingBar->Parent(NULL);

	choppingBar->Pos(choppingBarLocation);
	choppingBar->Scale(Vector2(0.0f, 1.0f));

	canChop = true;
}

Chopping::~Chopping()
{
	delete choppingCounter;
	delete collider;
	delete choppingBar;
	delete choppingBarBack;
	choppingCounter = NULL;
	collider = NULL;
	choppingBar = NULL;
	choppingBarBack = NULL;
}

void Chopping::Update()
{
	if (canChop && (ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
		mInput->MouseButtonReleased(mInput->right))
	{
		if (mInput->hasCheese || mInput->hasLettuce)
		{
			isChopping = true;

			choppingItem = mInput->GetCurrentHeldItem();

			choppingItem->Parent(this);
			choppingItem->Pos(VEC2_ZERO);
			
			canChop = false;
		}
	}
	else if (isChopping && (ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
		mInput->MouseButtonReleased(mInput->left))
	{
		mInput->SetCurrentHeldItem(choppingItem);
		choppingItem->Parent(NULL);
		choppingItem = NULL;
		canChop = true;
	}

	if (choppingItem == NULL)
	{
		isChopping = false;
	}

	if (isChopping)
	{
		if (mInput->KeyPressed(SDL_SCANCODE_F))
		{
			choppingItem->cookingTime++;
			AudioManager::Instance()->PlaySFX("/Music/Chopping Sound.wav", 0, 0);
		}

		//Increase cooking progress bar!

		if (choppingItem->cookingTime <= choppingAmount)
		{
			choppingBar->Scale(Vector2((choppingItem->cookingTime / 0.05f) / 100.0f, 1.0f));
			printf("Cooking time: %f\n", choppingItem->cookingTime);
		}

		if (choppingItem->cookingTime >= cookingTime)
		{

		}
	}
}

void Chopping::Render()
{
	choppingCounter->Render();

	choppingBar->Render();
}
