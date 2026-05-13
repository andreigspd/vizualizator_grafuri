#include "../include/nod.h"
#include "../include/util.h"
//METODE CLASA NOD ---------------------------->
//CONSTRUCTOR
Nod::Nod(float x, float y, int index, const sf::Font& font) : id(index), text(font), distanta(font) {
	cerc.setRadius(radius);
	cerc.setOrigin({ radius, radius });
	cerc.setPosition({ x, y });
	cerc.setFillColor(sf::Color::Cyan);
	cerc.setOutlineColor(sf::Color::Blue);
	cerc.setOutlineThickness(1);

	text.setString(std::to_string(index));
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::Black);

	const auto bounds = text.getLocalBounds();
	text.setOrigin({
		bounds.position.x + bounds.size.x / 2.0f,
		bounds.position.y + bounds.size.y / 2.0f
		});
	text.setPosition({ x, y });
}

//VERIFICA CLICK PE NOD RESPECTIV
bool Nod::VerificaClick(float x, float y) const {
	return cerc.getGlobalBounds().contains({ x, y });
}

// GETERI ->>>>>>>>>>>
int Nod::GetNodId() const {
	return id;
}

sf::Vector2f Nod::GetNodPosition() const {
	return cerc.getPosition();
}
// --------------------------

// SETERI ----------------->
void Nod::SetCuloareNod(CuloareNod color) {
	switch (color) {
	case NEVIZITAT:
		cerc.setFillColor(sf::Color::Cyan);
		break;
	case VIZITAT:
		cerc.setFillColor(sf::Color::Green);
		break;
	case CURENT:
		cerc.setFillColor(sf::Color::Yellow);
		break;
	case SELECTAT:
		cerc.setFillColor(sf::Color::Red);
		break;
	}
}
void Nod::SetNodId(int id) {
	this->id = id;
}
void Nod::SetNodTextId(std::string input) {
	text.setString(input);
}

void Nod::SetTextCost(int d) {
	if (d == -1) {
		distanta.setString("");
		return;
	}
	if (d == INT_MAX) {
		distanta.setString("inf");
	}
	else {
		distanta.setString(std::to_string(d));
	}
	distanta.setFillColor(sf::Color::Green);
	distanta.setCharacterSize(15);
	const auto bounds = distanta.getLocalBounds();
	distanta.setOrigin({
		bounds.position.x + bounds.size.x / 2.0f,
		bounds.position.y + bounds.size.y / 2.0f
		});
	const auto poz = cerc.getPosition();
	distanta.setPosition({ poz.x, poz.y + radius + 10.f });
}

// -----------------------------------
