#pragma once
#include "SDL.h"
#include <iostream>



class collision
{
public:

	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static void Hello();
	~collision();
};

