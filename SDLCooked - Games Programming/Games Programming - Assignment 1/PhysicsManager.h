#ifndef PhysicsManager_H
#define PhysicsManager_H

#include "PhysicsEntity.h"
#include <bitset>


class PhysicsManager {

public:

	enum class CollisionLayers {

		Player = 0,
		Plate,
		Food,
		Counter,
		Goal,

		MaxLayers
	};

	enum class CollisionFlags {

		None				= 0x00,
		Player				= 0x01,
		Plate				= 0x02,
		Food				= 0x04,
		Counter				= 0x08,
		Goal				= 0x016


	};

private:

	static PhysicsManager* sInstance;

	vector<PhysicsEntity*> mCollisionLayers[static_cast<unsigned int> (CollisionLayers::MaxLayers)];
	bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int> (CollisionLayers::MaxLayers)];

	unsigned long mLastID;

public:

	static PhysicsManager* Instance();
	static void Release();

	void SetLayerCollisonMask(CollisionLayers layer, CollisionFlags flags);

	unsigned long RegisterEntity(PhysicsEntity* entity, CollisionLayers layer);
	void UnregisterEntity(unsigned long id);

	void Update();

private:

	PhysicsManager();
	~PhysicsManager();
};

inline PhysicsManager::CollisionFlags operator|(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b)
{
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | (static_cast<unsigned int>(b)));
}

inline PhysicsManager::CollisionFlags operator&(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b)
{
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a)& (static_cast<unsigned int>(b)));
}

#endif // !PhysicsManager_H


