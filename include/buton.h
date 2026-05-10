#pragma once
#include <SFML/Graphics.hpp>
#include "../include/util.h"

class Buton : public sf::Drawable {
	static constexpr float width = 200.f;
	static constexpr float height = 50.f;
	sf::RectangleShape buton;
	sf::Text text;
	StareAplicatie stareButon;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(buton, states);
		target.draw(text, states);
	}
public:
	Buton(float x, float y, const sf::Font& font, const std::string Text, StareAplicatie stare, sf::Color color);
	bool clickButon(float x, float y) const;
	StareAplicatie getStareAsociata() const;
	float GetHeight() const;
	void SetCuloareButon(CuloareButon color);
};

