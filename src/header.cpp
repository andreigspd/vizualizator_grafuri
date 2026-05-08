#include "../include/header.h"
#include <SFML/Graphics.hpp>



Buton::Buton(float x, float y, const sf::Font& font, const std::string Text, StareAplicatie stare) : text(font), stareButon(stare) {
	buton.setOrigin({ width / 2.0f, height / 2.0f });
	buton.setFillColor(sf::Color::Red);
	buton.setOutlineColor(sf::Color(128, 128, 128));
	buton.setOutlineThickness(2);
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
