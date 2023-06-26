#include "Food.h"
#include "ScreenManager.h"
#include <iostream>

void Food::Update() {

	switch (currentFoodState)
	{
	case FoodStates::raw:
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
				mainTexture->Parent(ScreenManager::Instance()->returnPlayer());
				cookedTexture->Parent(ScreenManager::Instance()->returnPlayer());
				choppedTexture->Parent(ScreenManager::Instance()->returnPlayer());
				collider->Parent(ScreenManager::Instance()->returnPlayer());

				mainTexture->Pos(Vector2(0.0f, -32.0f));
				cookedTexture->Pos(Vector2(0.0f, -32.0f));
				choppedTexture->Pos(Vector2(0.0f, -32.0f));
				collider->Pos(Vector2(0.0f, -32.0f));

				mainTexture->Rotation(0.0f);
				cookedTexture->Rotation(0.0f);
				choppedTexture->Rotation(0.0f);
				collider->Rotation(0.0f);
			}
		}

		if (mInput->isHolding && mInput->GetCurrentHeldItem() == this)
		{
			if (mInput->MouseButtonReleased(mInput->right))
			{
				mainTexture->Parent(NULL);
				cookedTexture->Parent(mainTexture);
				collider->Parent(mainTexture);
				mInput->DropItem();
				mInput->hasMeat = false;
			}
		}

		break;

	case FoodStates::cooked:

		if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
			(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
			(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
			(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
			mInput->MouseButtonReleased(mInput->left))
		{
			mInput->SetCurrentHeldItem(this);
			mInput->isHolding = true;
			mainTexture->Parent(ScreenManager::Instance()->returnPlayer());
			cookedTexture->Parent(ScreenManager::Instance()->returnPlayer());
			collider->Parent(ScreenManager::Instance()->returnPlayer());

			mainTexture->Pos(Vector2(0.0f, -32.0f));
			cookedTexture->Pos(Vector2(0.0f, -32.0f));
			collider->Pos(Vector2(0.0f, -32.0f));

			mainTexture->Rotation(0.0f);
			cookedTexture->Rotation(0.0f);
			collider->Rotation(0.0f);
		}

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
				mainTexture->Parent(ScreenManager::Instance()->returnPlayer());
				cookedTexture->Parent(ScreenManager::Instance()->returnPlayer());
				collider->Parent(ScreenManager::Instance()->returnPlayer());

				mainTexture->Pos(Vector2(0.0f, -32.0f));
				cookedTexture->Pos(Vector2(0.0f, -32.0f));
				collider->Pos(Vector2(0.0f, -32.0f));

				mainTexture->Rotation(0.0f);
				cookedTexture->Rotation(0.0f);
				collider->Rotation(0.0f);
			}
		}

		if (mInput->isHolding && mInput->GetCurrentHeldItem() == this)
		{
			if (mInput->MouseButtonReleased(mInput->right))
			{
				cookedTexture->Parent(NULL);
				mainTexture->Parent(cookedTexture);
				collider->Parent(cookedTexture);
				mInput->SetCurrentHeldItem(NULL);
				mInput->isHolding = false;
				mInput->hasMeat = false;
			}
		}

		break;

	case FoodStates::chopped:

		if ((ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x > (collider->position(world).x - collider->ScaleDimentions().x)) &&
			(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().x < (collider->position(world).x + collider->ScaleDimentions().x)) &&
			(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y > (collider->position(world).y - collider->ScaleDimentions().y)) &&
			(ScreenManager::Instance()->returnPlayer()->playerColliderPosition().y < (collider->position(world).y + collider->ScaleDimentions().y)) &&
			mInput->MouseButtonReleased(mInput->left))
		{
			mInput->SetCurrentHeldItem(this);
			mInput->isHolding = true;
			mainTexture->Parent(ScreenManager::Instance()->returnPlayer());
			choppedTexture->Parent(ScreenManager::Instance()->returnPlayer());
			collider->Parent(ScreenManager::Instance()->returnPlayer());

			mainTexture->Pos(Vector2(0.0f, -32.0f));
			choppedTexture->Pos(Vector2(0.0f, -32.0f));
			collider->Pos(Vector2(0.0f, -32.0f));

			mainTexture->Rotation(0.0f);
			choppedTexture->Rotation(0.0f);
			collider->Rotation(0.0f);
		}

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

				mainTexture->Parent(ScreenManager::Instance()->returnPlayer());
				choppedTexture->Parent(ScreenManager::Instance()->returnPlayer());
				collider->Parent(ScreenManager::Instance()->returnPlayer());

				mainTexture->Pos(Vector2(0.0f, -32.0f));
				choppedTexture->Pos(Vector2(0.0f, -32.0f));
				collider->Pos(Vector2(0.0f, -32.0f));

				mainTexture->Rotation(0.0f);
				choppedTexture->Rotation(0.0f);
				collider->Rotation(0.0f);
			}
		}

		if (mInput->isHolding && mInput->GetCurrentHeldItem() == this)
		{
			if (mInput->MouseButtonReleased(mInput->right))
			{
				choppedTexture->Parent(NULL);
				mainTexture->Parent(choppedTexture);
				collider->Parent(choppedTexture);
				mInput->DropItem();
				mInput->hasCheese = false;
				mInput->hasLettuce = false;
			}
		}

		break;
	}
}

void Food::ChangeFoodState(FoodStates state) {
	currentFoodState = state;
}

void Food::Render()
{
	if (active())
	{
		switch (currentFoodState)
		{
		case FoodStates::raw:
			mainTexture->Render();
			break;

		case FoodStates::cooked:
			cookedTexture->Render();
			break;

		case FoodStates::chopped:
			choppedTexture->Render();
			break;
		}
	}
}