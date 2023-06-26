#ifndef GameEntity_H
#define GameEntity_H

#include "MathHelper.h"
#include <string>

using namespace std;

namespace ChrisFramework {

	class GameEntity {

	public:

		enum SPACE { local = 0, world = 1 };

		Vector2 velocity;

		string itemName;

		float cookingTime;

		int itemNumber;

		GameEntity* mParent;

		Vector2 mPosition;
		float mRotation;
		Vector2 mScale;

		bool isActive;

	public:

		GameEntity(Vector2 postion = VEC2_ZERO);
		~GameEntity();

		void Pos(Vector2 position);
		Vector2 position(SPACE space = world);

		void Rotation(float roation);
		float rotation(SPACE space = world);

		void Scale(Vector2 scale);
		Vector2 scale(SPACE space = world);

		void Active(bool active);
		bool active();

		void Parent(GameEntity* parent);
		GameEntity* parent();

		void Translate(Vector2 vector);
		void Rotate(float amount);

		void SetItemName(string name);
		string ItemName();

		virtual void Update();
		virtual void Render();

	};

}
#endif // !GameEntity_H
