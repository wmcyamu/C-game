#include "player.h"

player::player(const Window &window, int w, int h, int x, int y, int r, int g, int b, int a) :
	Window(window), _w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a)
{

}

void player::draw() const
{
	SDL_Rect player;
	player.w = _w;
	player.h = _h;
	//--
	player.x = this->_x;
	player.y = this->_y;
	//--
	SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);
	SDL_RenderFillRect(_renderer, &player);
}

void player::setpos(int x, int y)
{
	this->_x = x - (this->_w / 2);
	this->_y = y - (this->_h / 2);
}

void player::pollEvents(SDL_Event &event)
{

	/*velocity.X = 8;
	velocity.Y = 8;*/

	/*dashvelocity.X = 50;
	dashvelocity.Y = 50;*/

	if (_x + _w > (maxWidth - maxWidth) && _y + _h > (maxHeight - maxHeight))
	{
		dashvelocity.X = 50;
		dashvelocity.Y = 50;
		velocity.X = 8;
		velocity.Y = 8;
	}

	if (_x + _w < (maxWidth * 0))
	{
		dashvelocity.X = 50;
		dashvelocity.Y = 50;
		velocity.X = 0;
		velocity.Y = 0;
		_x = 0;
		_y = 0;
	}

	if (_y + _h < (maxHeight * 0))
	{
		dashvelocity.X = 50;
		dashvelocity.Y = 50;
		velocity.X = 0;
		velocity.Y = 0;
		_x = 0;
		_y = 0;
	}

	if (_x + _w > maxWidth)
	{
		dashvelocity.X = 50;
		dashvelocity.Y = 50;
		velocity.X = 0;
		velocity.Y = 0;
		_x = 0;
		_y = 0;

	}

	if (_y + _h > maxHeight)
	{
		dashvelocity.X = 50;
		dashvelocity.Y = 50;
		velocity.X = 0;
		velocity.Y = 0;
		_x = 0;
		_y = 0;

	}

	int sym = event.key.keysym.sym;
	switch (event.type)
	{



	case SDL_KEYDOWN:
		w = (sym == SDLK_w);
		a = (sym == SDLK_a);
		s = (sym == SDLK_s);
		d = (sym == SDLK_d);
		up = (sym == SDLK_UP);
		left = (sym == SDLK_LEFT);
		down = (sym == SDLK_DOWN);
		right = (sym == SDLK_RIGHT);
		shift = (sym == SDLK_LSHIFT);
		break;

	case SDL_KEYUP:
		if (sym == SDLK_w) w = !(sym == SDLK_w);
		if (sym == SDLK_a) a = !(sym == SDLK_a);
		if (sym == SDLK_s) s = !(sym == SDLK_s);
		if (sym == SDLK_d) d = !(sym == SDLK_d);
		if (sym == SDLK_UP) up = !(sym == SDLK_UP);
		if (sym == SDLK_LEFT) left = !(sym == SDLK_LEFT);
		if (sym == SDLK_DOWN) down = !(sym == SDLK_DOWN);
		if (sym == SDLK_RIGHT) right = !(sym == SDLK_RIGHT);
		if (sym == SDLK_LSHIFT) shift = !(sym == SDLK_LSHIFT);
		break;
	}

	if (keyState[SDL_SCANCODE_W])  _y = _y - velocity.Y;
	if (keyState[SDL_SCANCODE_UP]) _y = _y - velocity.Y;

	if (keyState[SDL_SCANCODE_A]) _x = _x - velocity.X;
	if (keyState[SDL_SCANCODE_LEFT]) _x = _x - velocity.X;

	if (keyState[SDL_SCANCODE_S]) _y = _y + velocity.Y;
	if (keyState[SDL_SCANCODE_DOWN]) _y = _y + velocity.Y;

	if (keyState[SDL_SCANCODE_D]) _x = _x + velocity.Y;
	if (keyState[SDL_SCANCODE_RIGHT]) _x = _x + velocity.Y;

	if (keyState[SDL_SCANCODE_W] & keyState[SDL_SCANCODE_A]) _y = _y - velocity.Y, _x = _x - velocity.X;
	if (keyState[SDL_SCANCODE_UP] & keyState[SDL_SCANCODE_LEFT]) _y = _y - velocity.Y, _x = _x - velocity.X;

	if (keyState[SDL_SCANCODE_W] & keyState[SDL_SCANCODE_D]) _y = _y - velocity.Y, _x = _x + velocity.X;
	if (keyState[SDL_SCANCODE_UP] & keyState[SDL_SCANCODE_RIGHT]) _y = _y - velocity.Y, _x = _x + velocity.X;

	if (keyState[SDL_SCANCODE_S] & keyState[SDL_SCANCODE_A]) _y = _y + velocity.Y, _x = _x - velocity.X;
	if (keyState[SDL_SCANCODE_DOWN] & keyState[SDL_SCANCODE_LEFT]) _y = _y + velocity.Y, _x = _x - velocity.X;

	if (keyState[SDL_SCANCODE_S] & keyState[SDL_SCANCODE_D]) _y = _y + velocity.Y, _x = _x + velocity.X;
	if (keyState[SDL_SCANCODE_DOWN] & keyState[SDL_SCANCODE_RIGHT]) _y = _y + velocity.Y, _x = _x + velocity.X;

	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_W]) _y = _y - dashvelocity.Y;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_A]) _x = _x - dashvelocity.X;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_S]) _y = _y + dashvelocity.Y;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_D]) _x = _x + dashvelocity.X;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_W] & keyState[SDL_SCANCODE_A]) _x = _x - dashvelocity.X, _y = _y - dashvelocity.Y;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_W] & keyState[SDL_SCANCODE_D]) _x = _x + dashvelocity.X, _y = _y - dashvelocity.Y;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_S] & keyState[SDL_SCANCODE_A]) _x = _x - dashvelocity.X, _y = _y + dashvelocity.Y;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_S] & keyState[SDL_SCANCODE_D]) _x = _x + dashvelocity.X, _y = _y + dashvelocity.Y;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_LEFT]) _x = _x - dashvelocity.X;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_RIGHT]) _x = _x + dashvelocity.X;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_UP]) _y = _y - dashvelocity.Y;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_DOWN]) _y = _y + dashvelocity.Y;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_UP] & keyState[SDL_SCANCODE_LEFT]) _x = _x - dashvelocity.X, _y = _y - dashvelocity.Y;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_UP] & keyState[SDL_SCANCODE_RIGHT]) _x = _x + dashvelocity.X, _y = _y - dashvelocity.Y;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_DOWN] & keyState[SDL_SCANCODE_LEFT]) _x = _x - dashvelocity.X, _y = _y + dashvelocity.Y;
	if (keyState[SDL_SCANCODE_LSHIFT] & keyState[SDL_SCANCODE_DOWN] & keyState[SDL_SCANCODE_RIGHT]) _x = _x + dashvelocity.X, _y = _y + dashvelocity.Y;

	if (keyState[NULL]) _y -= 0, _y += 0, _x -= 0, _x += 0;

}

void player::collider()
{
	mccollider.x = _x;
	mccollider.y = _y;
	mccollider.w = _w;
	mccollider.y = _h;
}

//void player::bounds()
//{	
//	SDL_Rect bound;
//	bound.x = 0;
//	bound.y = 0;
//	bound.w = _w;
//	bound.h = _h;
//
//}

//void player::AABB(whichobject)
//{
//	if (
//		recAx + recA.w >= whichObject.x &&
//		recB.x + recB.w >= recA.x &&
//		recA.y + recA.h >= recB.y &&
//		recB.y + recB.h >= recA.y
//		)
//	{
//		return true;
//
//	}
//
//	return false;
//}





