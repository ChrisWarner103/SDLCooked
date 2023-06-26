#include "GameEntity.h"

namespace ChrisFramework {

	GameEntity::GameEntity(Vector2 position)
	{
		mPosition.x = position.x;
		mPosition.y = position.y;
		mRotation = 0.0f;
		isActive = true;
		mParent = NULL;
		mScale = VEC2_ONE;
	}

	GameEntity::~GameEntity()
	{
		mParent = NULL;
	}

	void GameEntity::Pos(Vector2 pos)
	{
			mPosition = pos;
	}

	Vector2 GameEntity::position(SPACE space)
	{
		if (space == local || mParent == NULL)
			return mPosition;

		Vector2 parentScale = mParent->scale(world);
		Vector2 rotVector = Vector2(mPosition.x * parentScale.x, mPosition.y * parentScale.y);
		Vector2 rotPostion = RotateVector(rotVector, mParent->rotation(local));

		return mParent->position(local) + rotPostion;
	}

	void GameEntity::Rotation(float r)
	{
		mRotation = r;

		if (mRotation > 360.0f)
			mRotation -= 360.0f;


		if (mRotation < 0.0f)
			mRotation += 360.0f;

	}

	float GameEntity::rotation(SPACE space)
	{
		if (space == local || mParent == NULL)
			return mRotation;

		return mParent->rotation(world) + mRotation;
	}

	void GameEntity::Scale(Vector2 scale)
	{
		mScale = scale;
	}

	Vector2 GameEntity::scale(SPACE space)
	{
		if (space == local || mParent == NULL)
			return mScale;

		Vector2 scale = mParent->scale(world);
		scale.x *= mScale.x;
		scale.y *= mScale.y;

		return scale;
	}

	void GameEntity::Active(bool active) {
		isActive = active;
	}

	bool GameEntity::active()
	{
		return isActive;
	}

	void GameEntity::Parent(GameEntity* parent)
	{
		//If the parent is removed, The Position/Rotation/Scale are the GameEntity's world values, to keep the object looking the same after the removal of the parent;
		if (parent == NULL) {

			mPosition = position(world);
			mScale = scale(world);
			mRotation = rotation(world);
		}
		else {

			//If the object already has a parent, remove the current parent to get it ready to be the child for the new parent
			if (mParent != NULL)
				Parent(NULL);

			Vector2 parentScale = parent->scale(world);

			//Setting the local position to be relative to the new parent (while maintaining the same world position as before)
			Vector2 normalBack = Vector2(position(world) - parent->position(world));

			mPosition = RotateVector(normalBack, -parent->rotation(world));
			mPosition.x /= parentScale.x;
			mPosition.y /= parentScale.y;

			//Setting the local rotation to be relative to the new parent (while maintaining the same world rotation as before)
			mRotation = mRotation - parent->rotation(world);

			//Setting the new scale to be relative to the new parent (while maintaining the same world scale as before)
			mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
		}

		mParent = parent;
	}

	GameEntity* GameEntity::parent()
	{
		return mParent;
	}

	void GameEntity::Translate(Vector2 vector)
	{
		mPosition += vector;
	}

	void GameEntity::Rotate(float amount)
	{
		mRotation += amount;
	}

	void GameEntity::SetItemName(string name)
	{
		itemName = name;
	}

	string GameEntity::ItemName()
	{
		return itemName;
	}

	void GameEntity::Update()
	{

	}

	void GameEntity::Render()
	{

	}
}