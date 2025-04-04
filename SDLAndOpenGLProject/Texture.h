#pragma once

#include <string>
#include <assimp/texture.h>

class Texture
{
public:
	Texture();
	~Texture();

	bool Load(const std::string& fileName);
	bool LoadFromAssimp(const aiTexture* embeddedTex);
	void Unload();
	void CreateFromSurface(struct SDL_Surface* surface);
	void CreateForRendering(int width, int height, unsigned int format);

	void SetActive(int index = 0);
	void SetNoActive(int index = 0);

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
	unsigned int GetTextureID() const { return mTextureID; }
private:
	unsigned int mTextureID;
	int mWidth;
	int mHeight;
};