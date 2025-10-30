#include "precomp.h"
#include "sprite.h"
#include "FontRenderer.h"
#include "EntityContainer.h"

FontRenderer::FontRenderer()
{
	m_fontSheet = new Sprite(new Surface("assets/Font.tga"), 36);
}


FontRenderer::~FontRenderer()
{
	delete m_fontSheet;
}


void FontRenderer::UnInitFontRenderer()
{
	delete _instance;
	_instance = nullptr;
}


void FontRenderer::DrawText(int2 _position, const char* _content, EntityContainer* _container, uint_fast8_t _screen)
{
	RenderText(_position.x, _position.y, _content, _container, _screen);
}


void FontRenderer::DrawText(int2 _position, int _content, EntityContainer* _container, uint_fast8_t _screen)
{
	string t = to_string(_content);
	char const* n_char = t.c_str();
	RenderText(_position.x, _position.y, n_char, _container, _screen);
}


void FontRenderer::RenderText(int x, int y, const char* s, EntityContainer* _container, uint_fast8_t _screen)
{
	// Code copied from Pepijn and modified
	if (!_instance)
	{
		_instance = new FontRenderer();
	}
		int b = 0;
		int d = 0;
		for (int i = 0; i < strlen(s); i++)
		{
			char c = s[i];
			switch (c)
			{
			case 'a':
				m_fontSheet->SetFrame(0);
				break;
			case 'b':
				m_fontSheet->SetFrame(1);
				break;
			case 'c':
				m_fontSheet->SetFrame(2);
				break;
			case 'd':
				m_fontSheet->SetFrame(3);
				break;
			case 'e':
				m_fontSheet->SetFrame(4);
				break;
			case 'f':
				m_fontSheet->SetFrame(5);
				break;
			case 'g':
				m_fontSheet->SetFrame(6);
				break;
			case 'h':
				m_fontSheet->SetFrame(7);
				break;
			case 'i':
				m_fontSheet->SetFrame(8);
				break;
			case 'j':
				m_fontSheet->SetFrame(9);
				break;
			case 'k':
				m_fontSheet->SetFrame(10);
				break;
			case 'l':
				m_fontSheet->SetFrame(11);
				break;
			case 'm':
				m_fontSheet->SetFrame(12);
				break;
			case 'n':
				m_fontSheet->SetFrame(13);
				break;
			case 'o':
				m_fontSheet->SetFrame(14);
				break;
			case 'p':
				m_fontSheet->SetFrame(15);
				break;
			case 'q':
				m_fontSheet->SetFrame(16);
				break;
			case 'r':
				m_fontSheet->SetFrame(17);
				break;
			case 's':
				m_fontSheet->SetFrame(18);
				break;
			case 't':
				m_fontSheet->SetFrame(19);
				break;
			case 'u':
				m_fontSheet->SetFrame(20);
				break;
			case 'v':
				m_fontSheet->SetFrame(21);
				break;
			case 'w':
				m_fontSheet->SetFrame(22);
				break;
			case 'x':
				m_fontSheet->SetFrame(23);
				break;
			case 'y':
				m_fontSheet->SetFrame(24);
				break;
			case 'z':
				m_fontSheet->SetFrame(25);
				break;
			case '0':
				m_fontSheet->SetFrame(26);
				break;
			case '1':
				m_fontSheet->SetFrame(27);
				break;
			case '2':
				m_fontSheet->SetFrame(28);
				break;
			case '3':
				m_fontSheet->SetFrame(29);
				break;
			case '4':
				m_fontSheet->SetFrame(30);
				break;
			case '5':
				m_fontSheet->SetFrame(31);
				break;
			case '6':
				m_fontSheet->SetFrame(32);
				break;
			case '7':
				m_fontSheet->SetFrame(33);
				break;
			case '8':
				m_fontSheet->SetFrame(34);
				break;
			case '9':
				m_fontSheet->SetFrame(35);
				break;
			case '\n':
				d += 12;
				b = -8;
				break;
			}

			b += 8;

			if (c != ' ' && c != '\n')
			{
				_container->DrawSpriteToScreen(m_fontSheet, { (float)(x - 8 + b),  (float)(y + d) }, _screen);
			}
	}
}