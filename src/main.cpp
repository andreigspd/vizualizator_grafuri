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

	std::unique_ptr<Graf> G = std::make_unique<GrafOrientat>(window, font, layout);
	MeniuStanga meniuStanga(layout, font);
	MeniuDreapta meniuDreapta(layout, font);
	
	ManagerEvenimente inputManager(*G, meniuStanga, meniuDreapta, window, font);
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
			if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
				inputManager.ProceseazaTastatura(textEntered->unicode);
			}
		}
		inputManager.Update();
		window.clear();
		window.draw(meniuStanga);
		window.draw(meniuDreapta);
		G->Draw();
		inputManager.DrawInputBox();
		window.display();
	}
}


