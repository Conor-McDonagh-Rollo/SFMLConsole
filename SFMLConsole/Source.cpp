#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#include <iostream>
#include <Source.h>

int main()
{
	Source src;
	return 0;
}

Source::Source() : console{ 800.f, 600.f, "Test", "SpaceMono-Regular.ttf" }
{
	Run();
}

void Source::Run()
{
	console.AddText("------------------------------");
	console.AddText("  THE ADVENTURES OF DEWRUNE  ");
	console.AddText("------------------------------");
	console.NewLine();
	console.Pause();
	Menu();
}

void Source::Menu()
{
	console.AddText("------------------------------");
	console.AddText("       WELCOME   PLAYER       ");
	console.AddText("       Gold: " + std::to_string(gold));
	console.AddText("------------------------------");
	console.NewLine();
	console.AddText("1) Add Gold (10)");
	console.NewLine();
	int choice = console.InputInt("C:/> ");
	if (choice == 1)
	{
		gold += 10;
	}
	console.Pause();
	console.Pause();
	console.Pause();
	console.Pause();
	console.Pause();
	console.Pause();
	console.Pause();
	console.Pause();
	Menu();
}
