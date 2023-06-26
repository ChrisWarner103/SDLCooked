#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::sInstance = nullptr;

PhysicsManager* PhysicsManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new PhysicsManager();

	return sInstance;
}

void PhysicsManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

void PhysicsManager::SetLayerCollisonMask(CollisionLayers layer, CollisionFlags flags)
{
	mLayerMasks[static_cast<unsigned int>(layer)] = bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)>(static_cast<unsigned int>(flags));
}

unsigned long PhysicsManager::RegisterEntity(PhysicsEntity* entity, CollisionLayers layer)
{
	mCollisionLayers[static_cast<unsigned int>(layer)].push_back(entity);

	mLastID++;

	return mLastID;
}

void PhysicsManager::UnregisterEntity(unsigned long id)
{
	bool found = false;

	for (int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers) && !found; i++)
	{
		for (int j = 0; j < mCollisionLayers[i].size() && !found; j++)
		{
			if (mCollisionLayers[i][j]->GetID() == id)
			{
				mCollisionLayers[i].erase(mCollisionLayers[i].begin() + j);
				found = true;
			}
		}
	}
}

PhysicsManager::PhysicsManager()
{
	mLastID = 0;

	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++)
	{
		mLayerMasks[i] = bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)>(static_cast<unsigned int>(CollisionFlags::None));
	}
}

PhysicsManager::~PhysicsManager()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++)
	{
		mCollisionLayers[i].clear();
	}
}

void PhysicsManager::Update()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++)
	{
		for (unsigned int j = 0; j < static_cast<unsigned int>(CollisionLayers::MaxLayers); j++)
		{
			if (mLayerMasks[i].test(j) && i <= j)
			{
				for (unsigned int k = 0; k < mCollisionLayers[i].size(); k++)
				{
					for (unsigned int l = 0; l < mCollisionLayers[j].size(); l++)
					{
						if (mCollisionLayers[i][k]->CheckCollision(mCollisionLayers[j][l]))
						{
							mCollisionLayers[i][k]->Hit(mCollisionLayers[j][l]);
							mCollisionLayers[j][l]->Hit(mCollisionLayers[i][k]);
						}
					}
				}
			}
		}
	}
}


