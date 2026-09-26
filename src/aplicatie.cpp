#include "../include/aplicatie.h"
#include <stdexcept>

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
	font()
{
	// Load the UI font. The `assets/` folder is copied next to the executable
	// at build time (see CMakeLists.txt), so this relative path resolves at runtime.
	if (!font.openFromFile("assets/DejaVuSans.ttf")) {
		throw std::runtime_error(
			"Could not load font 'assets/DejaVuSans.ttf'. "
			"Make sure a .ttf file exists in the assets/ folder.");
	}
}

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
		if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
			if (G != nullptr) {
				float x = static_cast<float>(mouseMoved->position.x);
				float y = static_cast<float>(mouseMoved->position.y);
				inputManager->ProceseazaMouseMoved(x, y);
			}
		}
		if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
			if (mouseReleased->button == sf::Mouse::Button::Left) {
				if (G != nullptr) inputManager->ProceseazaMouseReleased();
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