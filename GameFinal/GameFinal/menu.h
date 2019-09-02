#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include "SDL_image.h"
#include <vector>
#include "windows.h"

class MenuButton
{
public:
	//Appearance of the menu button
	SDL_Texture * texture;
	SDL_Texture* highlightedTexture;

	bool highlighted = false;

	//Every menu button has a width and height
	int width, height;
	//The percent position on the screen (for relative)
	float percentX, percentY;

	void setHighlighted(bool value);


	MenuButton(const char* texturePath, const char* highlightPath, float percentX, float percentY, SDL_Renderer* renderer);
	~MenuButton();
	void Render(SDL_Window* window, SDL_Renderer* renderer);
};

class MenuTitle
{
public:
	//Appearance of the menu button
	SDL_Texture * texture;
	//Every menu button has a width and height
	int width, height;
	//The percent position on the screen (for relative)
	float percentX, percentY;

	MenuTitle(const char* texturePath, const char* highlightPath, float percentX, float percentY, SDL_Renderer* renderer);
	~MenuTitle();
	void Render(SDL_Window* window, SDL_Renderer* renderer);
};

class MenuControls
{
public:
	//Appearance of the menu button
	SDL_Texture * texture;
	//Every menu button has a width and height
	int width, height;
	//The percent position on the screen (for relative)
	float percentX, percentY;

	MenuControls(const char* texturePath, const char* highlightPath, float percentX, float percentY, SDL_Renderer* renderer);
	~MenuControls();
	void Render(SDL_Window* window, SDL_Renderer* renderer);
};



class Menu
{
public:

	SDL_Texture * BGT;
	bool menuActive = true;
	MenuButton* playButton;
	MenuButton* quitButton;
	MenuControls* Controls;
	MenuTitle* Title;


	std::vector<MenuButton*> menuItems;
	const Uint8 *keyState = SDL_GetKeyboardState(NULL);

	void pollevent(SDL_Event &event);

	void Render(SDL_Window* window, SDL_Renderer* renderer);
	Menu(SDL_Renderer* renderer);
	~Menu();
	void Menufunc();

private:
	int currentMenuIndex = 0;
	bool up = false;
	bool down = false;
	bool enter = false;

};
