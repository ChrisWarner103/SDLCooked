#include "ScreenManager.h"
#include "Food.h"

Lettuce::Lettuce()
{
	mInput = InputManager::Instance();

	mainTexture = new Texture("Food Items/cheese.png");
	choppedTexture = new Texture("Food Items/cheesechopped.png");
	collider = new Texture("BoxCollider.png");

	mainTexture->Parent(this);
	choppedTexture->Parent(this);
	collider->Parent(this);

	mainTexture->Active(false);
	choppedTexture->Active(false);
	collider->Active(false);

	SetItemName("Lettuce");

	mainTexture->Scale(Vector2(1.5f, 1.5f));
	choppedTexture->Scale(Vector2(1.5f, 1.5f));
	collider->Scale(Vector2(0.75f, 0.75f));
}

Lettuce::~Lettuce()
{
	mInput = NULL;

	delete mainTexture;
	mainTexture = NULL;
	delete choppedTexture;
	choppedTexture = NULL;
	delete collider;
	collider = NULL;
}

void Lettuce::Update()
{
	Food::Update();

	if (mInput->isHolding) {
		mInput->hasCheese = true;
	}

	if (this->cookingTime >= 15.0f)
	{
		ChangeFoodState(FoodStates::chopped);

		SetItemName("Chopped Cheese");
	}
}
