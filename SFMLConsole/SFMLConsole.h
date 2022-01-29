#ifndef SFMLCONSOLE_H
#define SFMLCONSOLE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class SFMLConsole
{
public:
	SFMLConsole(float width = 800.f, float height = 600.f, std::string title = "Console", std::string FontPath = "");
	sf::RenderWindow console_window;
	void Update();
	void AddText(std::string str);
	void NewLine();
	std::string Input(std::string str = " ");
	int InputInt(std::string str = " ");
	float InputFloat(std::string str = " ");
	void Pause(bool noText = false);
	void Clear();
private:
	//console window properties
	const float console_width;
	const float console_height;
	const std::string console_name;
	sf::View view;

	//text related
	void NewLineText();
	void Move(float y);
	int totalNewLines = 1;
	int newLinesToAdd = 0;
	float forcedNewLineOffset = 0.f;
	float posOffset = 0.f;
	std::vector<sf::Text> text;
	sf::Font font;

	//input
	bool FinishedInput = false;
	sf::Text* inputText = nullptr;

	bool contains(const std::string& str, const std::string substr);
};
#endif

