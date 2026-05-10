#pragma once
#include "../include/util.h"
#include "../include/buton.h"
#include <SFML/Graphics.hpp>
class Meniu : public sf::Drawable {
protected:
	static constexpr float padding = 20.f;
	static constexpr sf::Color CuloareFundal = sf::Color(128, 128, 128);
	sf::RectangleShape fundal;
	std::vector<Buton> butoane;
	float nextPositionY;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(fundal, states);
		for (const auto& buton : butoane) {
			target.draw(buton, states);
		}
	}
public:
	Meniu(float x, float y, float width, float height);
	void AdaugaButon(const sf::Font& font, std::string Text, StareAplicatie stare, sf::Color color);
	StareAplicatie VerificaClick(float x, float y);
	void SetCuloareButon(StareAplicatie StareCurenta);
};

class MeniuStanga : public Meniu {
public:
	MeniuStanga(const Layout& layout, const sf::Font& font);
};

class MeniuDreapta : public Meniu {
public:
	MeniuDreapta(const Layout& layout, const sf::Font& font);
};

class MeniuInitial : public Meniu {
	sf::Text titlu;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(fundal, states);
		target.draw(titlu, states);
		for (const auto& buton : butoane) {
			target.draw(buton, states);
		}
	}
public:
	MeniuInitial(const Layout& layout, const sf::Font& font);
};