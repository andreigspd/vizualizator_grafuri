#pragma once
#include <SFML/Graphics.hpp>

class ElementGraf : public sf::Drawable {
public:
	~ElementGraf() = default;
	virtual void click() = 0;
};

class Nod : public ElementGraf {
	sf::CircleShape cerc;
	int index;
	sf::Text text;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(cerc);
		target.draw(text);
	}
public:
	Nod(float x, float y, int index, const sf::Font& font) : index(index), text(font){
		float raza = 25.f;

		cerc.setRadius(raza);
		cerc.setOrigin({ raza, raza });
		cerc.setPosition({ x, y });
		cerc.setFillColor(sf::Color::Cyan);
		cerc.setOutlineColor(sf::Color::Blue);
		cerc.setOutlineThickness(2);

		text.setFont(font);
		text.setString(std::to_string(index));
		text.setCharacterSize(18);
		text.setFillColor(sf::Color::Black);
		text.setPosition({ x, y });

		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin({
			bounds.position.x + bounds.size.x / 2.0f,
			bounds.position.y + bounds.size.y / 2.0f
			});


	}
	void click() {
		cerc.setFillColor(sf::Color::Red);
	}
};

