#pragma once
#include <SFML/Graphics.hpp>

class ElementGraf : public sf::Drawable {
public:
	~ElementGraf() = default;
	virtual void click() = 0;
};

class Nod : public ElementGraf {
	sf::CircleShape cerc;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(cerc);
	}
public:
	Nod(float x, float y) {
		cerc.setRadius(20.f);
		cerc.setOrigin({ 20.f, 20.f });
		cerc.setPosition({ x, y });
		cerc.setFillColor(sf::Color::White);
	}
	void click() {
		cerc.setFillColor(sf::Color::Red);
	}
};

//class Muchie : public ElementGraf {

//};