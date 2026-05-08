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
	bool VerificaClick(float x, float y) const;
	int GetNodId() const;
	sf::Vector2f GetNodPosition() const;
};

class Muchie : public sf::Drawable {
	static constexpr float grosime = 4.0f;
	static constexpr float pi = 3.141592f;
	sf::RectangleShape linie;
	sf::Text costText;
	int idNod1, idNod2;
	int cost;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(linie, states);
		if(cost != 1) target.draw(costText, states);
	}
public:
	Muchie(sf::Vector2f poz1, sf::Vector2f poz2, int id1, int id2, int cost, const sf::Font& font);
};

class Graf {
	StareAplicatie StareCurenta;
	int nrNoduri, nrMuchii;
	std::vector<Nod> noduri;
	std::vector<Muchie> muchii;
	int nodStart, nodEnd;

	std::vector<std::vector<std::pair<int, int>>> matrix;

	sf::RenderWindow& window;
	const sf::Font& font;
	sf::FloatRect BlackScreen;


public:
	Graf(sf::RenderWindow& window, const sf::Font& font, const Layout& layout);
	void AdaugaNod(float x, float y);
	void AdaugaMuchie(int idNod1, int idNod2, int cost);
	void DFS(int startNod);
	void Draw() const;
	bool VerificaClick(float x, float y) const;
	int VerificaNod(float x, float y) const;
	void SetStare(StareAplicatie stare);
	void SetNodStart(int id);
	void SetNodEnd(int id);
	int GetNodStart() const;
	int GetNodEnd() const;
	StareAplicatie GetStare() const;
};

