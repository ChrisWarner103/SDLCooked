#ifndef  Scoreboard_H
#define Scoreboard_H

#include "Texture.h"
#include <vector>

using namespace ChrisFramework;
using namespace std;

class Scoreboard : public GameEntity {

private:

	vector<Texture*> mScore;

	Uint8 colourR, colourG, colourB;

public:

	Scoreboard(Uint8 R, Uint8 G, Uint8 B);
	~Scoreboard();

	void SetScore(int score);

	void Render();

private:

	void ClearScore();
};
#endif // ! Scoreboard_H

