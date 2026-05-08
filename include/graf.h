#pragma once
#include "../include/header.h"
#include <SFML/Graphics.hpp>

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
};

class Muchie : public sf::Drawable {

};

class Graf {
	StareAplicatie StareCurenta;
	int nrNoduri, nrMuchii;
	std::vector<Nod> noduri;
	std::vector<Muchie> muchii;

	std::vector<std::pair<int, int> > matrix;

	sf::RenderWindow& window;
	const sf::Font& font;
	sf::FloatRect BlackScreen;


public:
	Graf(sf::RenderWindow& window, const sf::Font& font, const Layout& layout);
	void AdaugaNod(float x, float y);
	void AdaugaMuchie(int idNod1, int idNod2, int cost);
	void DFS(int startNod);
	void Draw();
	bool VerificaClick(float x, float y);
	void SetStare(StareAplicatie stare);
	StareAplicatie GetStare();
};

