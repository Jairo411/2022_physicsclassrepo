#include "Texture.h"
#include "Window.h"
#include <SDL_image.h>


Texture::Texture():textureID(0) {
	
}

bool Texture::LoadImage(const char* filename) {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	SDL_Surface *textureSurface = IMG_Load(filename);
	if (textureSurface == nullptr) {
		return false;
	}
	int mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	
	SDL_FreeSurface(textureSurface);
	/// Wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0); /// Unbind the texture
	return true;
}


Texture::~Texture(){
	glDeleteTextures(1, &textureID);
}

SDLTexture::SDLTexture(Component* parent_) : Component(parent_) , dstRect(nullptr), srcRect(nullptr), texture(nullptr)
{

}

SDLTexture::~SDLTexture()
{
	delete texture;
	texture = nullptr;
}

bool SDLTexture::OnCreate()
{
	texture = nullptr;
	srcRect = new SDL_Rect();
	dstRect = new SDL_Rect();

	srcRect->x = 0;
	srcRect->y = 0;
	srcRect->w = 0;
	srcRect->h = 0;

	dstRect->x = 0;
	dstRect->y = 0;
	dstRect->w = 0;
	dstRect->h = 0;
	return false;
}

void SDLTexture::OnDestroy()
{
}

void SDLTexture::Update(const float deltaTime_)
{
}

void SDLTexture::Render()
{
	SDL_RenderCopy(Window::getRenderer(),texture,srcRect,dstRect);
}

bool SDLTexture::LoadImage(const char* filename_)
{
	SDL_Surface* texturesurface; 
	texturesurface = IMG_Load(filename_);
	if (texturesurface==nullptr)
	{
		return false;
	}
	texture = SDL_CreateTextureFromSurface(Window::getRenderer(),texturesurface);
	if (texture==nullptr)
	{
		return false;
	}
	return true;
}

void SDLTexture::SetRects(SDL_Rect source_, SDL_Rect display_)
{
	*srcRect = source_;
	*dstRect = display_;
}

void SDLTexture::SetDisplay(SDL_Rect display_)
{
	*dstRect = display_;
}



SDL_Rect* SDLTexture::GetDisplayRect()
{
	return dstRect;
}
