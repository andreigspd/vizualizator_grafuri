#include "../include/header.h"
#include <SFML/Graphics.hpp>



Buton::Buton(float x, float y, const sf::Font& font, const std::string Text, StareAplicatie stare) : 
	text(font), stareButon(stare) {
	buton.setOrigin({ width / 2.0f, height / 2.0f });
	buton.setFillColor(sf::Color::Red);
	buton.setOutlineColor(sf::Color::Black);
	buton.setOutlineThickness(5);
	buton.setSize({ width, height });
	buton.setPosition({ x, y });

	text.setString(Text);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	const auto bounds = text.getLocalBounds();
	text.setOrigin({
		bounds.position.x + bounds.size.x / 2.0f,
		bounds.position.y + bounds.size.y / 2.0f
		});
	text.setPosition({ x, y });

}
bool Buton::clickButon(float x, float y) const {
	return buton.getGlobalBounds().contains({ x, y });
}
StareAplicatie Buton::getStareAsociata() const {
	return stareButon;
}
float Buton::GetHeight() const {
	return height;
}
void Buton::SetCuloareButon(CuloareButon color) {
	switch (color) {
	case ACTIV:
		buton.setFillColor(sf::Color::Yellow);
		break;
	case INACTIV:
		buton.setFillColor(sf::Color::Red);
	}
}

Meniu::Meniu(float x, float y, float width, float height) {
	fundal.setSize({ width, height });
	fundal.setPosition({ x, y });
	fundal.setFillColor(CuloareFundal);
	nextPositionY = y + 50.f;
}
void Meniu::AdaugaButon(const sf::Font& font, std::string Text, StareAplicatie stare) {
	float CentruMeniu = fundal.getPosition().x + fundal.getSize().x / 2.0f;
	butoane.emplace_back(CentruMeniu, nextPositionY, font, Text, stare);
	nextPositionY += 20.f + butoane.front().GetHeight();
}
StareAplicatie Meniu::VerificaClick(float x, float y) {
	for (const auto& b : butoane) {
		if (b.clickButon(x, y)) {
			return b.getStareAsociata();
		}
	}
	return NEUTRU;
}
void Meniu::SetCuloareButon(StareAplicatie StareCurenta) {
	for (auto& buton : butoane) {
		if (buton.getStareAsociata() == StareCurenta) {
			buton.SetCuloareButon(ACTIV);
		}
		else {
			buton.SetCuloareButon(INACTIV);
		}
	}
}