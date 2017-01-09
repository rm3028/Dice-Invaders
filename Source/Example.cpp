#include <windows.h>
#include <cassert>
#include <cstdio>
#include "DiceInvaders.h"

class DiceInvadersLib
{
public:
	explicit DiceInvadersLib(const wchar_t* libraryPath)
	{
		m_lib = LoadLibraryW(libraryPath);
		assert(m_lib);

		DiceInvadersFactoryType* factory = (DiceInvadersFactoryType*)GetProcAddress(
				m_lib, "DiceInvadersFactory");
		m_interface = factory();
		assert(m_interface);
	}

	~DiceInvadersLib()
	{
		FreeLibrary(m_lib);
	}

	IDiceInvaders* get() const 
	{
		return m_interface;
	}

private: 
	DiceInvadersLib(const DiceInvadersLib&);
	DiceInvadersLib& operator=(const DiceInvadersLib&);

private: 
	IDiceInvaders* m_interface;
	HMODULE m_lib;
};


int APIENTRY WinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	LPSTR commandLine,
	int commandShow)
{
	DiceInvadersLib lib(L"DiceInvaders.dll");
	IDiceInvaders* system = lib.get();

	system->init(640, 480);

	ISprite* sprite = system->createSprite("data/player.bmp");

	float horizontalPosition = 320;
	float lastTime = system->getElapsedTime();
	while (system->update())
	{
		sprite->draw(int(horizontalPosition), 480-32);

		float newTime = system->getElapsedTime();
		float move = (newTime - lastTime) * 160.0f;
		lastTime = newTime;
		
		IDiceInvaders::KeyStatus keys;
		system->getKeyStatus(keys);
		if (keys.right)
			horizontalPosition += move;
		else if (keys.left)
			horizontalPosition -= move;
	}

	sprite->destroy();
	system->destroy();

	return 0;
}



