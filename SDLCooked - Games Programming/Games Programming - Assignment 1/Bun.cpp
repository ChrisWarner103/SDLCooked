#include "Bun.h"
#include "ScreenManager.h"

Bun::Bun()
{
	mInput = InputManager::Instance();

	bun = new Texture("Food Items/breadbun.png");
	platedBun = new Texture("Food Items/burgerbreadonly.png");
	platedCheese = new Texture("Food Items/burgercheese.png");
	platedCheeseLettuce = new Texture("Food Items/burgercheeselettuce.png");
	platedLettuce = new Texture("Food Items/burgerlettuce.png");
	platedMeat = new Texture("Food Items/burgerpatty.png");
	platedMeatCheese = new Texture("Food Items/burgerpattycheese.png");
	platedMeatLettuce = new Texture("Food Items/burgerpattylettuce.png");
	platedFull = new Texture("Food Items/burgerfinish.png");
	collider = new Texture("BoxCollider.png");

	bun->Parent(this);
	platedBun->Parent(this);
	platedCheese->Parent(this);
	platedCheeseLettuce->Parent(this);
	platedLettuce->Parent(this);
	platedMeat->Parent(this);
	platedMeatCheese->Parent(this);
	platedMeatLettuce->Parent(this);
	platedFull->Parent(this);
	collider->Parent(this);

	bun->Active(false);
	platedBun->Active(false);
	collider->Active(false);

	SetItemName("Bun");

	bun->Scale(Vector2(1.5f, 1.5f));
	platedBun->Scale(Vector2(1.5f, 1.5f));
	platedCheese->Scale(Vector2(1.5f, 1.5f));
	platedCheeseLettuce->Scale(Vector2(1.5f, 1.5f));
	platedLettuce->Scale(Vector2(1.5f, 1.5f));
	platedFull->Scale(Vector2(1.5f, 1.5f));
	platedMeat->Scale(Vector2(1.5f, 1.5f));
	platedMeatCheese->Scale(Vector2(1.5f, 1.5f));
	platedMeatLettuce->Scale(Vector2(1.5f, 1.5f));
	collider->Scale(Vector2(0.75f, 0.75f));
}

Bun::~Bun()
{
	mInput = NULL;

	delete bun;
	bun = NULL;
	delete platedBun;
	platedBun = NULL;
	delete collider;
	collider = NULL;
	delete platedCheese;
	platedCheese = NULL;
	delete platedCheeseLettuce;
	platedCheeseLettuce = NULL;
	delete platedLettuce;
	platedLettuce = NULL;
	delete platedMeat;
	platedMeat = NULL;
	delete platedMeatCheese;
	platedMeatCheese = NULL;
	delete platedMeatLettuce;
	platedMeatLettuce = NULL;
	delete platedFull;
	platedFull = NULL;
}

void Bun::ChangeFoodState(FoodStates state)
{
	currentFoodState = state;
}

void Bun::Update()
{
	if (itemName == "Burger Empty")
	{
		currentFoodState = FoodStates::Plated;
		bun->Parent(this);
		platedBun->Parent(this);
		platedCheese->Parent(this);
		platedCheeseLettuce->Parent(this);
		platedLettuce->Parent(this);
		platedFull->Parent(this);
		platedMeat->Parent(this);
		platedMeatCheese->Parent(this);
		platedMeatLettuce->Parent(this);
		collider->Parent(this);
	}

	if (itemName == "Burger Plain")
	{
		currentFoodState = FoodStates::PlatedMeat;
	}

	if (parent() == NULL)
	{
		bun->Parent(NULL);
		platedBun->Parent(NULL);
		platedCheese->Parent(NULL);
		platedCheeseLettuce->Parent(NULL);
		platedLettuce->Parent(NULL);
		platedFull->Parent(NULL);
		platedMeat->Parent(NULL);
		platedMeatCheese->Parent(NULL);
		platedMeatLettuce->Parent(NULL);
		collider->Parent(NULL);

		bun->Pos(position(world));
		platedBun->Pos(position(world));
		platedCheese->Pos(position(world));
		platedCheeseLettuce->Pos(position(world));
		platedLettuce->Pos(position(world));
		platedFull->Pos(position(world));
		platedMeat->Pos(position(world));
		platedMeatCheese->Pos(position(world));
		platedMeatLettuce->Pos(position(world));
		collider->Pos(position(world));
	}

	switch (currentFoodState)
	{
	case FoodStates::Normal:

		if (!mInput->isHolding)
		{

			if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
				mInput->MouseButtonReleased(mInput->left))
			{
				mInput->SetCurrentHeldItem(this);
				mInput->isHolding = true;

				bun->Parent(ScreenManager::Instance()->returnPlayer());
				platedBun->Parent(ScreenManager::Instance()->returnPlayer());
				collider->Parent(ScreenManager::Instance()->returnPlayer());

				bun->Pos(Vector2(0.0f, -32.0f));
				platedBun->Pos(Vector2(0.0f, -32.0f));
				platedCheese->Pos(Vector2(0.0f, -32.0f));
				platedCheeseLettuce->Pos(Vector2(0.0f, -32.0f));
				platedFull->Pos(Vector2(0.0f, -32.0f));
				platedLettuce->Pos(Vector2(0.0f, -32.0f));
				platedMeat->Pos(Vector2(0.0f, -32.0f));
				platedMeatCheese->Pos(Vector2(0.0f, -32.0f));
				platedMeatLettuce->Pos(Vector2(0.0f, -32.0f));

				collider->Pos(Vector2(0.0f, -32.0f));

				bun->Rotation(0.0f);
				platedBun->Rotation(0.0f);
				platedCheese->Rotation(0.0f);
				platedCheeseLettuce->Rotation(0.0f);
				platedFull->Rotation(0.0f);
				platedLettuce->Rotation(0.0f);
				platedMeat->Rotation(0.0f);
				platedMeatCheese->Rotation(0.0f);
				platedMeatLettuce->Rotation(0.0f);

				collider->Rotation(0.0f);
			}
		}
		if (mInput->isHolding && mInput->GetCurrentHeldItem() == this)
		{
			if (mInput->MouseButtonReleased(mInput->right))
			{
				bun->Parent(NULL);
				platedBun->Parent(bun);
				platedCheese->Parent(bun);
				platedCheeseLettuce->Parent(bun);
				platedLettuce->Parent(bun);
				platedFull->Parent(bun);
				platedMeat->Parent(bun);
				platedMeatCheese->Parent(bun);
				platedMeatLettuce->Parent(bun);
				collider->Parent(bun);

				mInput->DropItem();

			}
		}
		break;


	case FoodStates::Plated:

		if (itemName == "Burger Cheese")
		{
			currentFoodState = FoodStates::PlatedCheese;
			bun->Parent(this);
			platedBun->Parent(this);
			platedCheese->Parent(this);
			platedCheeseLettuce->Parent(this);
			platedLettuce->Parent(this);
			platedFull->Parent(this);
			platedMeat->Parent(this);
			platedMeatCheese->Parent(this);
			platedMeatLettuce->Parent(this);
			collider->Parent(this);
		}

		if (itemName == "Burger Lettuce")
		{
			currentFoodState = FoodStates::PlatedLettuce;
			bun->Parent(this);
			platedBun->Parent(this);
			platedCheese->Parent(this);
			platedCheeseLettuce->Parent(this);
			platedLettuce->Parent(this);
			platedFull->Parent(this);
			platedMeat->Parent(this);
			platedMeatCheese->Parent(this);
			platedMeatLettuce->Parent(this);
			collider->Parent(this);
		}

		break;

	case FoodStates::PlatedCheese:

		if (itemName == "Burger Meat Cheese")
		{
			currentFoodState = FoodStates::PlatedMeatCheese;
			bun->Parent(this);
			platedBun->Parent(this);
			platedCheese->Parent(this);
			platedCheeseLettuce->Parent(this);
			platedLettuce->Parent(this);
			platedFull->Parent(this);
			platedMeat->Parent(this);
			platedMeatCheese->Parent(this);
			platedMeatLettuce->Parent(this);
			collider->Parent(this);
		}

		if (itemName == "Burger Lettuce Cheese")
		{
			currentFoodState = FoodStates::PlatedCheeseLettuce;
			bun->Parent(this);
			platedBun->Parent(this);
			platedCheese->Parent(this);
			platedCheeseLettuce->Parent(this);
			platedLettuce->Parent(this);
			platedFull->Parent(this);
			platedMeat->Parent(this);
			platedMeatCheese->Parent(this);
			platedMeatLettuce->Parent(this);
			collider->Parent(this);
		}

		break;

	case FoodStates::PlatedMeat:

		if (itemName == "Burger Meat Cheese")
		{
			currentFoodState = FoodStates::PlatedMeatCheese;
		}

		if (itemName == "Burger Meat Lettuce")
		{
			currentFoodState = FoodStates::PlatedMeatLetuce;
		}

		break;

	case FoodStates::PlatedLettuce:

		if (itemName == "Burger Lettuce Cheese")
		{
			currentFoodState = FoodStates::PlatedCheeseLettuce;
		}

		if (itemName == "Burger Meat Lettuce")
		{
			currentFoodState = FoodStates::PlatedMeatLetuce;
		}

		break;

	case FoodStates::PlatedCheeseLettuce:

		if (itemName == "Burger Full")
		{
			currentFoodState = FoodStates::PlatedFull;
		}

			break;

	case FoodStates::PlatedMeatCheese:

		if (itemName == "Burger Full")
		{
			currentFoodState = FoodStates::PlatedFull;
		}
		break;

	case FoodStates::PlatedMeatLetuce:

		if (itemName == "Burger Full")
		{
			currentFoodState = FoodStates::PlatedFull;
		}
		break;
	}
}

void Bun::Render()
{
	switch (currentFoodState)
	{
	case FoodStates::Normal:

		bun->Render();

		break;

	case FoodStates::Plated:

		platedBun->Render();

		break;

	case FoodStates::PlatedMeat:
		platedMeat->Render();
		break;

	case FoodStates::PlatedCheese:
		platedCheese->Render();
		break;

	case FoodStates::PlatedLettuce:
		platedLettuce->Render();
		break;

	case FoodStates::PlatedCheeseLettuce:
		platedCheeseLettuce->Render();
		break;

	case FoodStates::PlatedMeatCheese:
		platedMeatCheese->Render();
		break;

	case FoodStates::PlatedMeatLetuce:
		platedMeatLettuce->Render();
		break;

	case FoodStates::PlatedFull:
		platedFull->Render();
		break;
	}
}
