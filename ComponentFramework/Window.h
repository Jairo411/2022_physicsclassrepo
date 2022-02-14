#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Debug.h"
#include "Vector.h"
#include "Matrix.h"
class Window {
private:
	int width, height;
	SDL_Window* window;
	SDL_GLContext context;
	static SDL_Renderer* renderer;
public:
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;

	Window();
	~Window();
	bool OnCreate(std::string name_, int width_, int height_, bool flag_);
	void OnDestroy();
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	SDL_Window* getWindow() const { return window; }
	static SDL_Renderer* getRenderer() { return renderer; }
private: /// internal tools OpenGl versions. 
	void setAttributes(int major_, int minor_);
	void getInstalledOpenGLInfo(int *major, int *minor);

};
#endif /// !WINDOW_H