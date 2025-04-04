#pragma once
#include <string>
#include <unordered_map>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include "Math.h"

class Font
{
public:
	Font(class BaseScene* game);
	~Font();

	// Load/unload from a file
	bool Load(const std::string& fileName);
	void Unload();

	// Given string and this font, draw to a texture
	class Texture* RenderText(const std::string& textKey,
		const Vector3& color = Color::White,
		int pointSize = 30);
private:
	// Map of point sizes to font data
	std::unordered_map<int, TTF_Font*> mFontData;
	class BaseScene* mGame;
};