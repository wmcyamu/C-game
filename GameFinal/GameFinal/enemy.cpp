#include "enemy.h"
#include "vector"

enemy::enemy(const Window & window, int w, int h, int x, int y, int r, int g, int b, int a) :
	Window(window), __w(w), __h(h), __x(x), __y(y), __r(r), __g(g), __b(b), __a(a)
{

}

void enemy::draw() const
{
	SDL_Rect enemy;
	enemy.w = __w;
	enemy.h = __h;
	//--
	enemy.x = this->__x;
	enemy.y = this->__y;
	//--
	SDL_SetRenderDrawColor(_renderer, 139, 0, 0, 255);
	SDL_RenderFillRect(_renderer, &enemy);
}

void enemy::setpos(int x, int y)
{
	this->__x = x - (this->__w / 2);
	this->__y = y - (this->__h / 2);
}

//void enemy::DEBUG_getpos()
//{
//	printf("X: %i \n", __x);
//	printf("Y: %i \n", __y);
//}

void enemy::pollEvents(SDL_Event & event)
{

}

void enemy::collider()
{
	encollider.x = __x;
	encollider.y = __y;
	encollider.w = __w;
	encollider.y = __h;

}

void enemy::move()
{
	velocity.Y = 5;
	__y = __y + velocity.Y;
}
