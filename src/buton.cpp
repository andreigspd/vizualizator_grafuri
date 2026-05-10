#include "../include/buton.h"
// FUNCTII BUTON ----------->
// CONSTRUCTOR
Buton::Buton(float x, float y, const sf::Font& font, const std::string Text, StareAplicatie stare, sf::Color color) :
	text(font), stareButon(stare) {
	buton.setOrigin({ width / 2.0f, height / 2.0f });
	buton.setFillColor(color);
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
// VF DACA COORDONATELE CLICKULUI SUNT IN INTERIORUL BUTONULUI
bool Buton::clickButon(float x, float y) const {
	return buton.getGlobalBounds().contains({ x, y });
}
// GET STARE
StareAplicatie Buton::getStareAsociata() const {
	return stareButon;
}
// GET HEIGHT
float Buton::GetHeight() const {
	return height;
}
// SET CULOARE
void Buton::SetCuloareButon(CuloareButon color) {
	switch (color) {
	case ACTIV:
		buton.setFillColor(sf::Color::Yellow);
		break;
	case INACTIV:
		buton.setFillColor(sf::Color::Red);
	}
}
// <----------------- END FUNCTII BUTON
