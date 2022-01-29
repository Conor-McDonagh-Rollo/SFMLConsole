#pragma once
#include <SFMLConsole.h>

class Source
{
public:
	Source();
	void Run();
	void Menu();

	SFMLConsole console;

	int gold = 0;
};