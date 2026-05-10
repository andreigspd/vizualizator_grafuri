#pragma once
#include <SFML/Graphics.hpp>
#include "../include/util.h"

class Nod : public sf::Drawable {
	static constexpr double radius = 30.f;
	sf::CircleShape cerc;
	sf::Text text;
	int id;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(cerc, states);
		target.draw(text, states);
	}
public:
	Nod(float x, float y, int index, const sf::Font& font);
	bool VerificaClick(float x, float y) const;
	int GetNodId() const;
	sf::Vector2f GetNodPosition() const;
	void SetCuloareNod(CuloareNod color);
};