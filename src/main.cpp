#include <SFML/Graphics.hpp>
#include "../include/header.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode( { 800, 600 } ), "SFML works!" );
	std::vector<std::unique_ptr<ElementGraf> >shapes;
	float raza = 30.f;
	

	while ( window.isOpen() )
	{
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mousePressed->button == sf::Mouse::Button::Left) {
					float x = static_cast<float>(mousePressed->position.x);
					float y = static_cast<float>(mousePressed->position.y);
					std::unique_ptr<ElementGraf> shape = std::make_unique<Nod>(x, y);
					shapes.push_back(std::move(shape));
				}
			}
		}
		window.clear();
		for (auto& shape : shapes) {
			window.draw(*shape);
		}
		window.display();
	}
}
