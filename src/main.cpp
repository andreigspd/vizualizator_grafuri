#include <SFML/Graphics.hpp>
#include "../include/graf.h"
#include <iostream>
int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Grafuri");
	sf::Font font("ARIAL.TTF");

	auto desktop = sf::VideoMode::getDesktopMode();
	Layout layout(
		static_cast<float>(desktop.size.x),
		static_cast<float>(desktop.size.y),
		250.f,
		250.f
	);

	Graf G(window, font, layout);
	Meniu MeniuStanga(0, 0, layout.leftMenuWidth, layout.screenHeight);
	Meniu MeniuDreapta(layout.screenWidth - layout.rightMenuWidth, 0, layout.rightMenuWidth, layout.screenHeight);

	MeniuStanga.AdaugaButon(font, "Neutru", NEUTRU_BUTON);
	MeniuStanga.AdaugaButon(font, "Adauga Nod", ADAUGA_NOD);
	MeniuStanga.AdaugaButon(font, "Adauga Muchie", ADAUGA_MUCHIE);

	MeniuDreapta.AdaugaButon(font, "Start DFS", START_DFS);

	ManagerEvenimente inputManager(G, MeniuStanga, MeniuDreapta, window);
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) window.close();
			if (const auto* mouseClicked = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouseClicked->button == sf::Mouse::Button::Left) {
					float x = static_cast<float>(mouseClicked->position.x);
					float y = static_cast<float>(mouseClicked->position.y);
					inputManager.ProceseazaClick(x, y);
				}
			}
		}
		inputManager.Update();
		window.clear();
		window.draw(MeniuStanga);
		window.draw(MeniuDreapta);
		G.Draw();
		window.display();
	}
}


