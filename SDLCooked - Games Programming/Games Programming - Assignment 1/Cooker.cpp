#include "Cooker.h"
#include "ScreenManager.h"

Cooker::Cooker()
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Cooker Station Constructed with Param(%p)\n", this);

	mInput = InputManager::Instance();
	mTimer = Timer::Instance();

	cookerCounter = new Texture("Environment/Cooker.png");
	fryingPan = new FryingPan();
	collider = new Texture("BoxCollider.png");

	cookingBar = new Texture("CookingProgressBar.png");
	cookingBarBack = new Texture("CookingProgressBarBack.png");

	cookerCounter->Parent(this);
	fryingPan->Parent(this);
	collider->Parent(this);

	cookingBar->Parent(this);
	cookingBarBack->Parent(this);

	fryingPan->Scale(Vector2(1.75f, 1.75f));
	collider->Pos(Vector2(0.0f, 32.0f));

	cookingBar->Pos(Vector2(0.0f, cookerCounter->ScaleDimentions().y * 0.7f));

	collider->Scale(Vector2(1.0f, 0.5f));

	cookingBar->Parent(NULL);

	//cookerCounter->Active(true);
	//fryingPan->Active(true);
}

Cooker::~Cooker()
{
	delete cookerCounter;
	cookerCounter = NULL;
	delete fryingPan;
	fryingPan = NULL;
	delete cookingBar;
	cookingBar = NULL;
	delete cookingBarBack;
	cookingBarBack = NULL;
	delete collider;
	collider = NULL;
}

void Cooker::Update()
{
	if (isCooking)
	{
		//fryingPan->Active(false);
	}

	if (fryingPan->parent() == this)
	{
		fryingPan->Update();
		canCook = true;
	}
	else
	{
		canCook = false;
	}

	if (canCook && (ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
		mInput->MouseButtonReleased(mInput->right))
	{
		if (mInput->hasMeat)
		{
			isCooking = true;

			cookingItem = mInput->GetCurrentHeldItem();

			cookingItem->Parent(this);
			cookingItem->Pos(VEC2_ZERO);

		}
	}
	else if (isCooking && (ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
		(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
		mInput->MouseButtonReleased(mInput->left))
	{
		mInput->SetCurrentHeldItem(cookingItem);
		cookingItem->Parent(NULL);
		cookingItem = NULL;
	}

	if (cookingItem == NULL)
	{
		isCooking = false;
	}

	if (isCooking)
	{
		cookingItem->cookingTime += mTimer->DeltaTime();

		//Increase cooking progress bar!

		if (cookingItem->cookingTime <= cookingTime)
		{
			cookingBar->Scale(Vector2((cookingItem->cookingTime / 0.05f) / 100.0f, 1.0f));
			printf("Cooking time: %f\n", cookingItem->cookingTime);
		}

		if (cookingItem->cookingTime >= cookingTime)
		{

		}
	}
}

void Cooker::Render()
{
	cookerCounter->Render();
	fryingPan->Render();

	cookingBar->Render();
}
