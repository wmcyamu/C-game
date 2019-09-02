#pragma once
#include <iostream>
#include <string>
#include <SDL.h>

typedef struct
{
	int width;
	int height;
} WindowSize;

class Window
{
public:
	Window(const std::string &title, int width, int height);
	~Window();
	void setWindowResizeCallback(void(*onWindowResized_callback)());
	bool esc = false;
	void pollEvents(SDL_Event &event);
	void clear() const;
	void present() const;
	WindowSize getWindowSize() const;
	inline bool isClosed() const { return _closed; }
	SDL_Renderer * _renderer = nullptr;
	SDL_Window * _window = nullptr;
	int maxWidth;
	int maxHeight;


private:
	bool init();

private:
	std::string _title;
	int _width;
	int _height;
	bool _closed = false;
	void(*onWindowResized_callback)();

	//protected:

};