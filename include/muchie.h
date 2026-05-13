#pragma once
#include <SFML/Graphics.hpp>

class Muchie : public sf::Drawable {
	static constexpr float grosime = 4.0f;
	static constexpr float pi = 3.141592f;
	sf::RectangleShape linie;
	sf::Text costText;
	int idNod1, idNod2;
	int cost;
	bool esteOrientat;
	sf::CircleShape sageata;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(linie, states);
		if (esteOrientat) {
			target.draw(sageata);
		}
		if (cost != 1) target.draw(costText, states);
	}
public:
	Muchie(sf::Vector2f poz1, sf::Vector2f poz2, int id1, int id2, int cost, const sf::Font& font, bool orientat);
	void SetCost(int cost);
	int GetId1() const;
	int GetId2() const;
	void SetId1(int id);
	void SetId2(int id);
	void SetPosition(sf::Vector2f poz1, sf::Vector2f poz2);
};