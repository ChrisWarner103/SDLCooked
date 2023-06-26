#include "Buttons.h"

Buttons::Buttons()
{
}

Buttons::~Buttons()
{
}

void Buttons::SetPosition(int x, int y)
{
	buttonPosition.x = x;
	buttonPosition.y = y;
}

void Buttons::HandleButtonEvent(SDL_Event* e)
{
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);
    }
}

void Buttons::Render()
{
}
