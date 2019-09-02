#pragma once
#include "window.h"
#include <string>
#include "vector.h"


class enemy : public Window
{
public:
	enemy(const Window &window, int w, int h, int x, int y, int r, int g, int b, int a);
	std::string en;
	SDL_Rect encollider;
	vector velocity;
	void draw() const;
	void setpos(int x, int y);
	//void DEBUG_getpos();
	void pollEvents(SDL_Event &event);
	void collider();
	void move(); 
	//std::vector<setpos*> setpos;


private:
	int __w, __h;
	int __x, __y;
	int __r, __g, __b, __a;
};