#pragma once
#include "window.h"
#include "windows.h"
#include <string>
#include "vector.h"

class player : public Window
{
public:
	player(const Window &window, int w, int h, int x, int y, int r, int g, int b, int a);

	SDL_Rect mccollider;
	std::string mc;
	void draw() const;
	void setpos(int x, int y);
	const Uint8 *keyState = SDL_GetKeyboardState(NULL);
	void pollEvents(SDL_Event &event);
	vector velocity;
	vector dashvelocity;
	bool w = false;
	bool a = false;
	bool s = false;
	bool d = false;
	bool up = false;
	bool left = false;
	bool down = false;
	bool right = false;
	bool shift = false;
	void collider();
	/*void bounds();*/

	//void AABB(whichObject);


private:
	int _w, _h;
	int _x, _y;
	int _r, _g, _b, _a;
};

