#include "SFMLConsole.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <lexical_cast.hpp>
#include <boost/range/adaptor/reversed.hpp>

SFMLConsole::SFMLConsole(float width, float height, std::string title, std::string FontPath) :
	console_width{ width }, console_height{ height }, console_name{ title }
{
	console_window.create(sf::VideoMode(console_width, console_height), console_name);
	console_window.setFramerateLimit(60);
	font.loadFromFile(FontPath);
	view.reset(sf::FloatRect(0, 0, width, height));
	view.setSize(sf::Vector2f(width, height));
	console_window.setView(view);
}

void SFMLConsole::Update()
{
	sf::Event event;
	while (console_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			console_window.close();
	}
	console_window.clear(sf::Color::Black);

	for (int i = 0; i < text.size(); i++)
	{
		console_window.draw(text[i]);
	}
	console_window.setView(view);
	console_window.display();
}

void SFMLConsole::AddText(std::string str)
{
	newLinesToAdd = 0;
	if (contains(str, "\n")) newLinesToAdd += str.find("\n");
	bool textAligned = false;
	int charDif = 0;
	bool newLined = false;
	while (!textAligned)
	{
		std::string testStr = str;
		std::string newLn = "\n";
		if (testStr.size() - charDif == 0)
		{
			std::cout << "\nText output too long!\n";
			throw std::exception();
		}
		testStr.insert(testStr.size() - charDif, newLn);
		sf::Text test(testStr, font, 20);
		if (test.getGlobalBounds().width > console_width)
		{
			charDif++;
			newLined = true;
		}
		else
		{
			textAligned = true;
			str = testStr;
			if (newLined)
			{
				newLinesToAdd++;
				forcedNewLineOffset -= 14.f;
			}
		}
	}
	text.push_back(sf::Text(str, font, 20));
	text[text.size() - 1].setFillColor(sf::Color::White);
	totalNewLines++;
	NewLineText();
	if (text[text.size() - 1].getPosition().y > console_height + forcedNewLineOffset + 10.0f) Move(26.0f);
	totalNewLines += newLinesToAdd;
}

void SFMLConsole::Move(float y)
{
	forcedNewLineOffset += y;
	view.move(sf::Vector2f(0.f,y));
}

void SFMLConsole::NewLineText()
{
	text[text.size() - 1].setPosition(0.f, ((26 * totalNewLines) - 52) + posOffset);
}

void SFMLConsole::NewLine()
{
	AddText(" ");
}

std::string SFMLConsole::Input(std::string str)
{
	std::string returnStr = "";
	AddText(str);
	inputText = &text[text.size() - 1];
	if (text[text.size() - 1].getPosition().y > (console_height + forcedNewLineOffset + 10.0f))
	{
		Move(26.0f);
	}
	FinishedInput = false;
	while (!FinishedInput)
	{
		sf::Event ev;
		while (console_window.pollEvent(ev))
		{
			if (ev.type == sf::Event::TextEntered)
			{
				str += ev.text.unicode;
				returnStr += ev.text.unicode;
				inputText->setString(str);
			}
			if (ev.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::Enter == ev.key.code)
				{
					FinishedInput = true;
				}
			}
			if (ev.type == sf::Event::Closed)
			{
				console_window.close();
			}
		}
		console_window.clear(sf::Color::Black);
		for (int i = 0; i < text.size(); i++)
		{
			console_window.draw(text[i]);
		}
		console_window.setView(view);
		console_window.display();
	}
	boost::erase_all(returnStr, "\r");
	return returnStr;
}

int SFMLConsole::InputInt(std::string str)
{
	std::string s = Input(str);
	return boost::lexical_cast<int>(s);
}

float SFMLConsole::InputFloat(std::string str)
{
	std::string s = Input(str);
	return boost::lexical_cast<float>(s);
}

void SFMLConsole::Pause(bool noText)
{
	if (!noText) AddText("Type anything to continue...");
	std::string input = Input(" ");
}

void SFMLConsole::Clear()
{
	totalNewLines = 1;
	newLinesToAdd = 0;
	forcedNewLineOffset = 0.f;
	posOffset = 0.f;
	FinishedInput = false;
	inputText = nullptr;
	text.clear();
}

bool SFMLConsole::contains(const std::string& str, const std::string substr)
{
	if (str.size() < substr.size()) return false;

	for (int i = 0; i < str.size(); i++)
	{
		if (str.size() - i < substr.size()) return false;

		bool match = true;
		for (int j = 0; j < substr.size(); j++)
		{
			if (str.at(i + j) != substr.at(j))
			{
				match = false;
				break;
			}
		}
		if (match) return true;
	}
	return false;
}