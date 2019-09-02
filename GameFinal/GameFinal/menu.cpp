#include "menu.h"

void MenuButton::setHighlighted(bool value)
{
	highlighted = value;
}



MenuButton::MenuButton(const char * texturePath, const char* highlightPath, float percentX, float percentY, SDL_Renderer * renderer)
{
	//Set up percent variables
	this->percentX = percentX;
	this->percentY = percentY;

	//the pixel width & height of this menu button
	this->width = 128;
	this->height = 128;
	/*this->widthTI = 200;
	this->heighTI = 200;
	this->hct = 200;
	this->wct = 200;*/

	// ----------------------

	//load in the texture
	SDL_Surface* surface = IMG_Load(texturePath);
	//error checker
	if (surface == NULL)
		printf("yolo: error is %s\n", SDL_GetError());

	this->texture = SDL_CreateTextureFromSurface(renderer, surface);

	//-------------------------

	//load in the texture
	SDL_Surface* surface2 = IMG_Load(highlightPath);
	//error checker
	if (surface == NULL)
		printf("yolo: error is %s\n", SDL_GetError());

	this->highlightedTexture = SDL_CreateTextureFromSurface(renderer, surface2);
}

MenuButton::~MenuButton()
{
}

void MenuButton::Render(SDL_Window * window, SDL_Renderer * renderer)
{
	//the width and height
	int w, h;

	//Actually get the window size
	SDL_GetWindowSize(window, &w, &h);

	//Calculate the relative location according to percent
	int x = (int)(w * percentX);
	int y = (int)(h * percentY);

	//Make the rectangle region where we're gonna copy to
	SDL_Rect rect = SDL_Rect{ x, y, width, height };

	//Copy to the screen
	if (this->highlighted)
		SDL_RenderCopy(renderer, highlightedTexture, NULL, &rect);
	else
		SDL_RenderCopy(renderer, texture, NULL, &rect);
}

Menu::Menu(SDL_Renderer * renderer)
{


	SDL_Surface* surface = IMG_Load("Img/meme_overload");
	this->BGT = SDL_CreateTextureFromSurface(renderer, surface);
	//Icon Made by Smashicons "https://www.flaticon.com/free-icon/play-button_148744#term=play&page=1&position=4"
	playButton = new MenuButton("Img/play.png", "img/play_highlighted.png", 0.1f, 0.2f, renderer);
	//Icon made by Freepik "https://www.flaticon.com/free-icon/cross-circular-button_59338#term=quit&page=1&position=2"
	quitButton = new MenuButton("Img/quit.png", "img/quit_highlighted.png", 0.8f, 0.2f, renderer);
	Controls = new MenuControls("Img/Controls.png", "Img/Controls.png", 0.3f, 0.4f, renderer);
	//Icon made with https://cooltext.com/Logo-Design-Neon
	Title = new MenuTitle("Img/Title.png", "Img/Title.png", 0.3f, 0.1f, renderer);

	menuItems.push_back(playButton);
	menuItems.push_back(quitButton);
}

Menu::~Menu()
{

}

void Menu::Menufunc()
{
	SDL_Event event;

	if (up)
	{
		if ((currentMenuIndex - 1) < 0)
			currentMenuIndex = menuItems.size() - 1;
		else
			currentMenuIndex--;

		up = false;
	}
	if (down)
	{
		currentMenuIndex = (currentMenuIndex + 1) % menuItems.size();
		down = false;
	}

	for (int i = 0; i < menuItems.size(); i++)
	{
		if (i == currentMenuIndex)
			menuItems[i]->highlighted = true;
		else
			menuItems[i]->highlighted = false;
	}

	if (enter)
	{
		this->menuActive = false;
	}
}
void Menu::pollevent(SDL_Event & event)
{
	int sym = event.key.keysym.sym;
	switch (event.type)
	{
	case SDL_KEYDOWN:
		up = (sym == SDLK_UP);
		down = (sym == SDLK_DOWN);
		enter = (sym == SDLK_RETURN);
		break;
	case SDL_KEYUP:
		if (sym == SDLK_UP) up = !(sym == SDLK_UP);
		if (sym == SDLK_DOWN) down = !(sym == SDLK_DOWN);
		if (sym == SDLK_RETURN) enter = !(sym = SDLK_RETURN);
		break;
	}
}

void Menu::Render(SDL_Window * window, SDL_Renderer * renderer)
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	SDL_Rect rect = SDL_Rect{ 0, 0, w, h };
	SDL_RenderCopy(renderer, BGT, NULL, &rect);
	this->playButton->Render(window, renderer);
	this->Controls->Render(window, renderer);
	this->quitButton->Render(window, renderer);
	this->Title->Render(window, renderer);


}

MenuTitle::MenuTitle(const char * texturePath, const char * highlightPath, float percentX, float percentY, SDL_Renderer * renderer)
{
	//Set up percent variables
	this->percentX = percentX;
	this->percentY = percentY;

	//the pixel width & height of this menu button
	this->width = 500;
	this->height = 128;
	//load in the texture

	SDL_Surface* surface = IMG_Load(texturePath);
	//error checker
	if (surface == NULL)
		printf("yolo: error is %s\n", SDL_GetError());

	this->texture = SDL_CreateTextureFromSurface(renderer, surface);

}

void MenuTitle::Render(SDL_Window * window, SDL_Renderer * renderer)
{
	//the width and height
	int w, h;

	//Actually get the window size
	SDL_GetWindowSize(window, &w, &h);

	//Calculate the relative location according to percent
	int x = (int)(w * percentX);
	int y = (int)(h * percentY);

	//Make the rectangle region where we're gonna copy to
	SDL_Rect rect = SDL_Rect{ x, y, width, height };

	//Copy to the screen
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
MenuTitle::~MenuTitle()
{
}

MenuControls::MenuControls(const char * texturePath, const char * highlightPath, float percentX, float percentY, SDL_Renderer * renderer)
{
	//Set up percent variables
	this->percentX = percentX;
	this->percentY = percentY;

	//the pixel width & height of this menu button
	this->width = 550;
	this->height = 450;
	//load in the texture

	SDL_Surface* surface = IMG_Load(texturePath);
	//error checker
	if (surface == NULL)
		printf("yolo: error is %s\n", SDL_GetError());

	this->texture = SDL_CreateTextureFromSurface(renderer, surface);

}

void MenuControls::Render(SDL_Window * window, SDL_Renderer * renderer)
{
	//the width and height
	int w, h;

	//Actually get the window size
	SDL_GetWindowSize(window, &w, &h);

	//Calculate the relative location according to percent
	int x = (int)(w * percentX);
	int y = (int)(h * percentY);

	//Make the rectangle region where we're gonna copy to
	SDL_Rect rect = SDL_Rect{ x, y, width, height };

	//Copy to the screen
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}
MenuControls::~MenuControls()
{
}
