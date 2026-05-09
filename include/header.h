#pragma once
#include <SFML/Graphics.hpp>
class Graf;

enum StareAplicatie {
	NEUTRU,
	NEUTRU_BUTON,
	ADAUGA_NOD,
	ADAUGA_MUCHIE,
	START_DFS
};

enum CuloareNod {
	NEVIZITAT,
	SELECTAT,
	CURENT,
	VIZITAT
};
enum CuloareButon {
	ACTIV,
	INACTIV
};

struct Layout {
	float screenWidth;
	float screenHeight;
	float leftMenuWidth;
	float rightMenuWidth;
	Layout(float width, float height, float leftwidth, float rightwidth) : screenWidth(width), screenHeight(height),
		leftMenuWidth(leftwidth), rightMenuWidth(rightwidth) {}
	float GetCanvasX() const {
		return leftMenuWidth;
	}
	float GetCanvasWidth() const {
		return screenWidth - leftMenuWidth - rightMenuWidth;
	}
};



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

class ManagerEvenimente {
	Graf& G;
	Meniu& meniuStanga;
	Meniu& meniuDreapta;
	sf::RenderWindow& window;
public:
	ManagerEvenimente(Graf& graf, Meniu& stanga, Meniu& dreapta, sf::RenderWindow& window);
	void ProceseazaClick(float x, float y);
	void Update();
};

