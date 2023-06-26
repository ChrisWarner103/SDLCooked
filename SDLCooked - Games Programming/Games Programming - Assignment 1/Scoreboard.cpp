#include "Scoreboard.h"

Scoreboard::Scoreboard(Uint8 R, Uint8 G, Uint8 B)
{
	colourR = R;
	colourG = G;
	colourB = B;

	SetScore(0);
}

Scoreboard::~Scoreboard()
{
	ClearScore();
}

void Scoreboard::SetScore(int score)
{
	ClearScore();

	if (score == 0)
	{
		for (int i = 0; i < 1; i++)
		{
			mScore.push_back(new Texture("0", "seguibl.ttf", 72, { colourR, colourG, colourB }));
			mScore[i]->Parent(this);
			mScore[i]->Pos(Vector2(-48.0f * i, 0.0f));
		}
	}
	else
	{
		string string = to_string(score);
		int lastIndex = string.length() - 1;

		for (int i = 0; i <= lastIndex; i++)
		{
			mScore.push_back(new Texture(string.substr(i, 1), "seguibl.ttf", 72, { colourR, colourG, colourB }));
			mScore[i]->Parent(this);
			mScore[i]->Pos(Vector2(-48.0f * (lastIndex - i), 0.0f));
		}
	}
}

void Scoreboard::Render()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		mScore[i]->Render();
	}
}

void Scoreboard::ClearScore()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		delete mScore[i];
		mScore[i] = NULL;
	}

	mScore.clear();
}
