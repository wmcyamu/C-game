#include "window.h"

Window::Window(const std::string &title, int width, int height) :
	_title(title), _width(width), _height(height)
{
	_closed = !init();
}

Window::~Window()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Failed tp initialize SDL.\n";
		return 0;
	}

	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_RESIZABLE);
	maxWidth = _width;
	maxHeight = _height;

	if (_window == nullptr)
	{
		std::cerr << "Failed to create window.\n";
		return 0;
	}


	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (_renderer == nullptr)
	{
		std::cerr << "Failed to create renderer.\n";
		return 0;
	}

	return true;
}

void Window::pollEvents(SDL_Event &event)
{
	int sym = event.key.keysym.sym;
	switch (event.type)
	{
	case SDL_KEYDOWN:
		esc = (sym == SDLK_ESCAPE);
		break;

	case SDL_KEYUP:
		if (sym == SDLK_ESCAPE) esc = !(sym == SDLK_ESCAPE);
		break;

	case SDL_QUIT:
		_closed = true;
		break;

	case SDL_WINDOWEVENT:
		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			onWindowResized_callback();
		}





		/*case SDL_QUIT:
		_closed = true;
		break;

		case SDLK_ESCAPE:
		_closed = true;
		break;

		case SDL_WINDOWEVENT:
		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_SIZE_CHANGED:
		onWindowResized_callback();*/

		/*case SDL_QUIT:
		_closed = true;
		break;

		case SDLK_ESCAPE:
		_closed = true;
		break;

		case SDL_WINDOWEVENT:
		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_SIZE_CHANGED:
		onWindowResized_callback();
		}

		default:
		break;*/
	}
}

void Window::clear() const
{
	//:: -- "access something static"
	//.  -- "access something in this instance"
	//-> -- "access something through a pointer"
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);
}

void Window::present() const
{
	SDL_RenderPresent(_renderer);
}


WindowSize Window::getWindowSize() const
{
	int w, h;
	SDL_GetWindowSize(_window, &w, &h);

	return WindowSize
	{
		w, h
	};

}


void Window::setWindowResizeCallback(void(*onWindowResized_callback)())
{
	this->onWindowResized_callback = onWindowResized_callback;
}