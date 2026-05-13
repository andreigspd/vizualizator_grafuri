#pragma once
#include "../include/meniu.h"
#include "../include/graf.h"

class ManagerEvenimente {
	Graf& G;
	Meniu& meniuStanga;
	Meniu& meniuDreapta;
	sf::RenderWindow& window;
	const sf::Font& font;

	std::string inputCost = "";
	sf::RectangleShape inputBox;
	sf::Text inputText;
public:
	ManagerEvenimente(Graf& graf, Meniu& stanga, Meniu& dreapta, sf::RenderWindow& window, const sf::Font& font);
	void ProceseazaClick(float x, float y);
	void ProceseazaTastatura(int c);
	void ProceseazaMouseMoved(float x, float y);
	void ProceseazaMouseReleased();
	void Update();
	void DrawInputBox();
};

