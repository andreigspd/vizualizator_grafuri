#include "../include/aplicatie.h"

Aplicatie::Aplicatie() :
	window(sf::VideoMode::getDesktopMode(), "Grafuri", sf::State::Fullscreen),
	layout(static_cast<float>(sf::VideoMode::getDesktopMode().size.x),
		static_cast<float>(sf::VideoMode::getDesktopMode().size.y),
		250.f, 250.f),
	G(nullptr),
	inputManager(nullptr),
	meniuStart(layout, font),
	meniuStanga(layout, font),
	meniuDreapta(layout, font),
	font("ARIAL.TTF"){ }

void Aplicatie::ProceseazaElemente() {
	while (const auto event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) window.close();
		if (const auto* keyboardInput = event->getIf<sf::Event::KeyPressed>()) {
			if (keyboardInput->code == sf::Keyboard::Key::Z && G != nullptr) {
				inputManager = nullptr;
				G = nullptr;
			}
			else if (keyboardInput->code == sf::Keyboard::Key::X) {
				window.close();
			}
		}
		if (const auto* mouseClicked = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (mouseClicked->button == sf::Mouse::Button::Left) {
				float x = static_cast<float>(mouseClicked->position.x);
				float y = static_cast<float>(mouseClicked->position.y);
				if (G == nullptr) {
					StareAplicatie clickMeniu = meniuStart.VerificaClick(x, y);
					if (clickMeniu == ALEGE_ORIENTAT) {
						G = std::make_unique<GrafOrientat>(window, font, layout);
						inputManager = std::make_unique<ManagerEvenimente>(*G, meniuStanga, meniuDreapta, window, font);
					}
					else if (clickMeniu == ALEGE_NEORIENTAT) {
						G = std::make_unique<GrafNeorientat>(window, font, layout);
						inputManager = std::make_unique<ManagerEvenimente>(*G, meniuStanga, meniuDreapta, window, font);
					}
				}
				else {
					inputManager->ProceseazaClick(x, y);
				}
			}
		}
		if (G != nullptr) {
			if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
				inputManager->ProceseazaTastatura(textEntered->unicode);
			}
		}
	}
}

void Aplicatie::Draw() {
	window.clear();
	if (G == nullptr) {
		window.draw(meniuStart);
	}
	else {
		inputManager->Update();
		window.draw(meniuStanga);
		window.draw(meniuDreapta);
		G->Draw();
		inputManager->DrawInputBox();
	}
	window.display();
}

void Aplicatie::Ruleaza() {
	while (window.isOpen()) {
		ProceseazaElemente();
		Draw();
	}
}