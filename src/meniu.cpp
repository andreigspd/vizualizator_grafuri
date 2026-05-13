#include "../include/meniu.h"

// FUNCTII MENIU --------------->

//CONSTRUCTOR
Meniu::Meniu(float x, float y, float width, float height) {
	fundal.setSize({ width, height });
	fundal.setPosition({ x, y });
	fundal.setFillColor(CuloareFundal);
	nextPositionY = y + 50.f;
}
//ADAUGARE BUTON
void Meniu::AdaugaButon(const sf::Font& font, std::string Text, StareAplicatie stare, sf::Color color) {
	float CentruMeniu = fundal.getPosition().x + fundal.getSize().x / 2.0f;
	butoane.emplace_back(CentruMeniu, nextPositionY, font, Text, stare, color);
	nextPositionY += 20.f + butoane.front().GetHeight();
}
//VERIFICA CLICK 
StareAplicatie Meniu::VerificaClick(float x, float y) {
	for (const auto& b : butoane) {
		if (b.clickButon(x, y)) {
			return b.getStareAsociata();
		}
	}
	return NEUTRU;
}
//SET CULOARE
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

MeniuStanga::MeniuStanga(const Layout& layout, const sf::Font& font) :
	Meniu(0, 0, layout.leftMenuWidth, layout.screenHeight) {
	AdaugaButon(font, "Neutru", NEUTRU_BUTON, sf::Color::Red);
	AdaugaButon(font, "Adauga Nod", ADAUGA_NOD, sf::Color::Red);
	AdaugaButon(font, "Adauga Muchie", ADAUGA_MUCHIE, sf::Color::Red);
	AdaugaButon(font, "Adauga Cost", ADAUGA_COST, sf::Color::Red);
	AdaugaButon(font, "Sterge Nod", STERGE_NOD, sf::Color::Red);
	AdaugaButon(font, "Sterge Muchie", STERGE_MUCHIE, sf::Color::Red);
}

MeniuDreapta::MeniuDreapta(const Layout& layout, const sf::Font& font) :
	Meniu(layout.screenWidth - layout.rightMenuWidth, 0, layout.rightMenuWidth, layout.screenHeight), tastaBack(font), tastaExit(font) {
	AdaugaButon(font, "DFS", START_DFS, sf::Color::Red);
	AdaugaButon(font, "BFS", START_BFS, sf::Color::Red);
	AdaugaButon(font, "DIJKSTRA", DIJKSTRA, sf::Color::Red);

	tastaBack.setString("Press Z to go back");
	tastaBack.setFillColor(sf::Color::Yellow);
	tastaBack.setCharacterSize(20);
	auto bounds = tastaBack.getLocalBounds();
	tastaBack.setOrigin({
		bounds.position.x + bounds.size.x / 2.0f,
		bounds.position.y + bounds.size.y / 2.0f
		});
	tastaBack.setPosition({ fundal.getPosition().x + fundal.getSize().x / 2.0f, layout.screenHeight - 35.f});

	tastaExit.setString("Press X to quit");
	tastaExit.setFillColor(sf::Color::Red);
	tastaExit.setCharacterSize(20);

	bounds = tastaExit.getLocalBounds();
	tastaExit.setOrigin({
		bounds.position.x + bounds.size.x / 2.0f,
		bounds.position.y + bounds.size.y / 2.0f
		});
	tastaExit.setPosition({ tastaBack.getPosition().x, layout.screenHeight - 15.f});
}


MeniuInitial::MeniuInitial(const Layout& layout, const sf::Font& font) :
	Meniu(0, 0, layout.screenWidth, layout.screenHeight), titlu(font) {
	titlu.setString("Vizualizator de grafuri");
	titlu.setCharacterSize(40);
	titlu.setFillColor(sf::Color(19, 94, 156));
	titlu.setStyle(sf::Text::Bold);
	titlu.setOutlineColor(sf::Color::Black);
	titlu.setOutlineThickness(2);
	auto bounds = titlu.getLocalBounds();
	titlu.setOrigin({
		bounds.position.x + bounds.size.x / 2.0f,
		bounds.position.y + bounds.size.y / 2.0f
		});
	titlu.setPosition({ layout.screenWidth / 2.0f, layout.screenHeight / 2.0f - 200.f });
	nextPositionY = layout.screenHeight / 2.0f - 100.f;
	AdaugaButon(font, "Graf Orientat", ALEGE_ORIENTAT, sf::Color(0, 180, 196));
	AdaugaButon(font, "Graf Neorientat", ALEGE_NEORIENTAT, sf::Color(0, 180, 196));
}


// <----------------- END FUNCTII MENIU