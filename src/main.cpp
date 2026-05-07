#include <SFML/Graphics.hpp>
#include "../include/header.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Grafuri");
	sf::Font font("ARIAL.TTF");

	Graf G(window, font);
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) window.close();
			if (const auto* mouseClicked = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouseClicked->button == sf::Mouse::Button::Left) {
					float x = static_cast<float>(mouseClicked->position.x);
					float y = static_cast<float>(mouseClicked->position.y);
					G.AdaugaNod(x, y);
				}
			}
		}
		window.clear();
		G.Draw();
		window.display();
	}

}
