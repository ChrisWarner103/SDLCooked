#include "Plate.h"
#include "ScreenManager.h"

Plate::Plate()
{
	mInput = InputManager::Instance();

	plate = new Texture("Items/plate.png");
	collider = new Texture("BoxCollider.png");

	plate->Parent(this);
	collider->Parent(this);

	plate->Active(false);
	collider->Active(false);

	SetItemName("Plate");

	plate->Scale(Vector2(1.5f, 1.5f));
	collider->Scale(Vector2(0.75f, 0.75f));
}

Plate::~Plate()
{
	mInput = NULL;

	delete plate;
	plate = NULL;
	delete collider;
	collider = NULL;
}

void Plate::ChangeFoodState(PlateStates state)
{
	currentFoodState = state;
}

void Plate::Update()
{

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
			plate->Parent(ScreenManager::Instance()->returnPlayer());
			collider->Parent(ScreenManager::Instance()->returnPlayer());

			plate->Pos(Vector2(0.0f, -32.0f));
			collider->Pos(Vector2(0.0f, -32.0f));

			plate->Rotation(0.0f);
			collider->Rotation(0.0f);
		}
	}

	if (!ScreenManager::Instance()->returnPlayer()->atGoal && mInput->MouseButtonDown(mInput->right) && mInput->GetCurrentHeldItem() == this)
	{
		plate->Parent(NULL);
		collider->Parent(plate);
		mInput->DropItem();
	}

	switch (currentFoodState)
	{
	case PlateStates::empty:

		if (mInput->isHolding && mInput->GetCurrentHeldItem()->ItemName() == "Bun" && !hasBun)
		{
			if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
				mInput->MouseButtonReleased(mInput->left))
			{
				hasBun = true;

				bun = mInput->GetCurrentHeldItem();
				mInput->SetCurrentHeldItem(NULL);
				mInput->isHolding = false;

				bun->Parent(NULL);
				bun->SetItemName("Burger Empty");
				currentFoodState = PlateStates::first;
			}
		}

		break;


	case PlateStates::first:

		bun->Pos(plate->position(world));

		if (mInput->isHolding && mInput->GetCurrentHeldItem()->ItemName() == "Cooked Meat" && hasBun)
		{
			if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
				mInput->MouseButtonReleased(mInput->left))
			{
				hasMeat = true;

				mInput->GetCurrentHeldItem()->Active(false);
				mInput->GetCurrentHeldItem()->Parent(NULL);
				mInput->isHolding = false;
				mInput->SetCurrentHeldItem(NULL);

				bun->SetItemName("Burger Plain");
				SetItemName("Plated Burger Plain");
				currentFoodState = PlateStates::second;
			}
		}

		if (mInput->isHolding && mInput->GetCurrentHeldItem()->ItemName() == "Chopped Cheese" && hasBun)
		{
			if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
				mInput->MouseButtonReleased(mInput->left))
			{
				hasCheese = true;

				mInput->GetCurrentHeldItem()->Active(false);
				mInput->GetCurrentHeldItem()->Parent(NULL);
				mInput->isHolding = false;
				mInput->SetCurrentHeldItem(NULL);

				bun->SetItemName("Burger Cheese");
				currentFoodState = PlateStates::second;
			}
		}

		if (mInput->isHolding && mInput->GetCurrentHeldItem()->ItemName() == "Chopped Lettuce" && hasBun)
		{
			if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
				mInput->MouseButtonReleased(mInput->left))
			{
				hasLettuce = true;

				mInput->GetCurrentHeldItem()->Active(false);
				mInput->GetCurrentHeldItem()->Parent(NULL);
				mInput->isHolding = false;
				mInput->SetCurrentHeldItem(NULL);

				bun->SetItemName("Burger Lettuce");
				currentFoodState = PlateStates::second;
			}
		}

		break;

	case PlateStates::second:

		bun->Pos(plate->position(world));

		if (mInput->isHolding && mInput->GetCurrentHeldItem()->ItemName() == "Cooked Meat" && hasBun && hasCheese && !hasMeat)
		{
			if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
				mInput->MouseButtonReleased(mInput->left))
			{

				hasMeat = true;

				mInput->GetCurrentHeldItem()->Active(false);
				mInput->GetCurrentHeldItem()->Parent(NULL);
				mInput->isHolding = false;
				mInput->SetCurrentHeldItem(NULL);

				bun->SetItemName("Burger Meat Cheese");
				SetItemName("Plated Burger Cheese");
				currentFoodState = PlateStates::third;
			}
		}

		if (mInput->isHolding && mInput->GetCurrentHeldItem()->ItemName() == "Cooked Meat" && hasBun && hasLettuce && !hasMeat)
		{
			if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
				mInput->MouseButtonReleased(mInput->left))
			{
				hasMeat = true;

				mInput->GetCurrentHeldItem()->Active(false);
				mInput->GetCurrentHeldItem()->Parent(NULL);
				mInput->isHolding = false;
				mInput->SetCurrentHeldItem(NULL);

				bun->SetItemName("Burger Meat Lettuce");
				SetItemName("Plated Burger Lettuce");
				currentFoodState = PlateStates::third;
			}
		}

		if (mInput->isHolding && mInput->GetCurrentHeldItem()->ItemName() == "Chopped Cheese" && hasBun && hasMeat && !hasCheese)
		{
			if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
				mInput->MouseButtonReleased(mInput->left))
			{
				hasCheese = true;

				mInput->GetCurrentHeldItem()->Active(false);
				mInput->GetCurrentHeldItem()->Parent(NULL);
				mInput->isHolding = false;
				mInput->SetCurrentHeldItem(NULL);

				bun->SetItemName("Burger Meat Cheese");
				SetItemName("Plated Burger Cheese");
				currentFoodState = PlateStates::third;
			}
		}

		if (mInput->isHolding && mInput->GetCurrentHeldItem()->ItemName() == "Chopped Cheese" && hasBun && hasLettuce && !hasCheese)
		{
			if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
				mInput->MouseButtonReleased(mInput->left))
			{
				hasCheese = true;

				mInput->GetCurrentHeldItem()->Active(false);
				mInput->GetCurrentHeldItem()->Parent(NULL);
				mInput->isHolding = false;
				mInput->SetCurrentHeldItem(NULL);

				bun->SetItemName("Burger Lettuce Cheese");
				currentFoodState = PlateStates::third;
			}
		}

		if (mInput->isHolding && mInput->GetCurrentHeldItem()->ItemName() == "Chopped Lettuce" && hasBun && hasMeat && !hasLettuce)
		{
			if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
				mInput->MouseButtonReleased(mInput->left))
			{
				hasLettuce = true;

				mInput->GetCurrentHeldItem()->Active(false);
				mInput->GetCurrentHeldItem()->Parent(NULL);
				mInput->isHolding = false;
				mInput->SetCurrentHeldItem(NULL);

				bun->SetItemName("Burger Meat Lettuce");
				SetItemName("Plated Burger Lettuce");
				currentFoodState = PlateStates::third;
			}
		}

		if (mInput->isHolding && mInput->GetCurrentHeldItem()->ItemName() == "Chopped Lettuce" && hasBun && hasCheese && !hasLettuce)
		{
			if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
				mInput->MouseButtonReleased(mInput->left))
			{
				hasLettuce = true;

				mInput->GetCurrentHeldItem()->Active(false);
				mInput->GetCurrentHeldItem()->Parent(NULL);
				mInput->isHolding = false;
				mInput->SetCurrentHeldItem(NULL);

				bun->SetItemName("Burger Lettuce Cheese");
				currentFoodState = PlateStates::third;
			}
		}

		break;

	case PlateStates::third:

		bun->Pos(plate->position(world));

		if (mInput->isHolding && mInput->GetCurrentHeldItem()->ItemName() == "Cooked Meat" && hasBun && hasCheese && hasLettuce && !hasMeat)
		{
			if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
				mInput->MouseButtonReleased(mInput->left))
			{

				hasMeat = true;

				mInput->GetCurrentHeldItem()->Active(false);
				mInput->GetCurrentHeldItem()->Parent(NULL);
				mInput->isHolding = false;
				mInput->SetCurrentHeldItem(NULL);

				bun->SetItemName("Burger Full");
				SetItemName("Plated Burger Full");
			}
		}

		if (mInput->isHolding && mInput->GetCurrentHeldItem()->ItemName() == "Chopped Cheese" && hasBun && hasMeat && hasLettuce && !hasCheese)
		{
			if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
				mInput->MouseButtonReleased(mInput->left))
			{
				hasCheese = true;

				mInput->GetCurrentHeldItem()->Active(false);
				mInput->GetCurrentHeldItem()->Parent(NULL);
				mInput->isHolding = false;
				mInput->SetCurrentHeldItem(NULL);

				bun->SetItemName("Burger Full");
				SetItemName("Plated Burger Full");
			}
		}

		if (mInput->isHolding && mInput->GetCurrentHeldItem()->ItemName() == "Chopped Lettuce" && hasBun && hasCheese && hasMeat && !hasLettuce)
		{
			if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
				(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
				mInput->MouseButtonReleased(mInput->left))
			{
				hasLettuce = true;

				mInput->GetCurrentHeldItem()->Active(false);
				mInput->GetCurrentHeldItem()->Parent(NULL);
				mInput->isHolding = false;
				mInput->SetCurrentHeldItem(NULL);

				bun->SetItemName("Burger Full");
				SetItemName("Plated Burger Full");
			}
		}

		break;
	}

}

void Plate::Render()
{
	switch (currentFoodState)
	{
	case PlateStates::empty:
		plate->Render();
		break;
	case PlateStates::first:
		plate->Render();
		break;
	case PlateStates::second:
		plate->Render();
		break;
	case PlateStates::third:
		plate->Render();
		break;
	}
}
