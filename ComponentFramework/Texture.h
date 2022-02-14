#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL.h>
#include <glew.h>
#include "Component.h"
class Window;
class Texture {
public:
	Texture();
	~Texture();
	bool LoadImage(const char* filename);
	inline GLuint getTextureID() const { return textureID; }
private:
	GLuint textureID;
};

class SDLTexture : public Component
{
public:
	SDLTexture(Component* parent_);
	~SDLTexture();
	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render();

	bool LoadImage(const char* filename_);
	void SetRects(SDL_Rect source_, SDL_Rect display_);
	void SetDisplay(SDL_Rect display_);	
	SDL_Rect* GetDisplayRect();
private:
	SDL_Rect* srcRect;
	SDL_Rect* dstRect;
	SDL_Texture* texture;
};
#endif // TEXTURE_H
