#pragma once
#include "sprite.h"

class EntityContainer;

class FontRenderer
{
public:
	static void UnInitFontRenderer();
	static void DrawText(int2 _position, const char* _content, EntityContainer* _container, uint_fast8_t _screen = 0);
	static void DrawText(int2 _position, int _content, EntityContainer* _container, uint_fast8_t _screen = 0);

private:
	FontRenderer();
	~FontRenderer();
	static void RenderText(int x, int y, const char* s, EntityContainer* _container, uint_fast8_t _screen = 0);
	static inline Sprite* m_fontSheet;
	inline static FontRenderer* _instance = nullptr;
};

