#include "../include/muchie.h"

// METODE CLASA MUCHIE ---------------->
//CONSTRUCTOR
Muchie::Muchie(sf::Vector2f poz1, sf::Vector2f poz2, int id1, int id2, int cost, const sf::Font& font, bool orientat) :
	costText(font), idNod1(id1), idNod2(id2), cost(cost), esteOrientat(orientat) {
	
	linie.setOrigin({ 0.f, grosime / 2.0f });
	
	linie.setFillColor(sf::Color::Magenta);

	if (esteOrientat) {
		float razaSageata = 12.f;
		sageata.setRadius(razaSageata);
		sageata.setPointCount(3);
		sageata.setFillColor(sf::Color::Magenta);
		sageata.setOrigin({ razaSageata, 0.f });
	}

	costText.setString(std::to_string(cost));
	costText.setCharacterSize(16);
	costText.setFillColor(sf::Color::Yellow);
	const auto bounds = costText.getLocalBounds();
	costText.setOrigin({
		bounds.position.x + bounds.size.x / 2.0f,
		bounds.position.y + bounds.size.y / 2.0f
		});
	SetPosition(poz1, poz2);
}
// SETERI 
void Muchie::SetCost(int c) {
	cost = c;
	costText.setString(std::to_string(cost));
}
void Muchie::SetId1(int id) {
	idNod1 = id;
}
void Muchie::SetId2(int id) {
	idNod2 = id;
}
void Muchie::SetPosition(sf::Vector2f poz1, sf::Vector2f poz2) {
	float dx = poz2.x - poz1.x;
	float dy = poz2.y - poz1.y;
	float distanta = sqrt(dx * dx + dy * dy);
	
	linie.setSize({ distanta, grosime });
	linie.setPosition(poz1);

	float unghiRadiani = std::atan2(dy, dx);
	linie.setRotation(sf::radians(unghiRadiani));

	if (esteOrientat) {
		float margineNodEndX = poz2.x - 30.f * std::cos(unghiRadiani);
		float margineNodEndY = poz2.y - 30.f * std::sin(unghiRadiani);
		sageata.setPosition({ margineNodEndX, margineNodEndY });
		sageata.setRotation(sf::radians(unghiRadiani + pi / 2));
	}
	costText.setPosition({ poz1.x + dx * 0.7f + (-dy / distanta) * 15.f, poz1.y + dy * 0.7f + (dx / distanta) * 15.f });
}


// GETERI
int Muchie::GetId1() const {
	return idNod1;
}
int Muchie::GetId2() const {
	return idNod2;
}
