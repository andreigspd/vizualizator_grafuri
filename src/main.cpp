#include <SFML/Graphics.hpp>
#include "../include/header.h"
#include <iostream>
int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Grafuri");
	float width = sf::VideoMode::getDesktopMode().size.x; // de facut o clasa SCREEN, pt butoane, graf
	float height = sf::VideoMode::getDesktopMode().size.y;
	sf::RectangleShape buton1({ 200.f, 50.f });// de facut clasa buton
	buton1.setFillColor(sf::Color::Red);
	buton1.setOrigin({ 100.f, 25.f });
	buton1.setPosition({ 200.f, 200.f });
	sf::Font font("ARIAL.TTF");
	sf::Text TextButon1(font);
	TextButon1.setString("Adauga Nod");
	TextButon1.setCharacterSize(15);
	const auto bounds = TextButon1.getLocalBounds();
	TextButon1.setOrigin({
		bounds.position.x + bounds.size.x / 2.0f,
		bounds.position.y + bounds.size.y / 2.0f
		});
	TextButon1.setPosition({ 200.f, 200.f });

	Graf G(window, font);
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) window.close();
			if (const auto* mouseClicked = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouseClicked->button == sf::Mouse::Button::Left) {
					float x = static_cast<float>(mouseClicked->position.x);
					float y = static_cast<float>(mouseClicked->position.y);
					if (buton1.getGlobalBounds().contains({x, y})) {
						G.SetStare(ADAUGA_NOD);
					}
					else if(G.GetStare() == ADAUGA_NOD) G.AdaugaNod(x, y);
				}
			}
		}
		window.clear();
		window.draw(buton1);
		window.draw(TextButon1);
		G.Draw();
		window.display();
	}

}
