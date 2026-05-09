#pragma once
#include <SFML/Graphics.hpp>
#include "../include/util.h"
class Graf;


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
	Buton(float x, float y, const sf::Font& font, const std::string Text, StareAplicatie stare);
	bool clickButon(float x, float y) const;
	StareAplicatie getStareAsociata() const;
	float GetHeight() const;
	void SetCuloareButon(CuloareButon color);
};


class Meniu : public sf::Drawable {
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
	void AdaugaButon(const sf::Font& font, std::string Text, StareAplicatie stare);
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

class ManagerEvenimente {
	Graf& G;
	Meniu& meniuStanga;
	Meniu& meniuDreapta;
	sf::RenderWindow& window;
	const sf::Font& font;

	std::string inputCost = "";
	sf::RectangleShape inputBox;
	sf::Text inputText;
public:
	ManagerEvenimente(Graf& graf, Meniu& stanga, Meniu& dreapta, sf::RenderWindow& window, const sf::Font& font);
	void ProceseazaClick(float x, float y);
	void ProceseazaTastatura(int c);
	void Update();
	void DrawInputBox();
};

