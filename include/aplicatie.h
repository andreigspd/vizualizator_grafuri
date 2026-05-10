#pragma once
#include "../include/manager_evenimente.h"
#include "SFML/Graphics.hpp"

class Aplicatie {
	sf::RenderWindow window;
	sf::Font font;
	Layout layout;

	MeniuInitial meniuStart;
	MeniuStanga meniuStanga;
	MeniuDreapta meniuDreapta;

	std::unique_ptr<Graf> G;
	std::unique_ptr<ManagerEvenimente> inputManager;

	void ProceseazaElemente();
	void Draw();
public:
	Aplicatie();
	void Ruleaza();
};