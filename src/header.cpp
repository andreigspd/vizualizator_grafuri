#include "../include/header.h"
#include "../include/graf.h"
#include <SFML/Graphics.hpp>

// FUNCTII BUTON ----------->
// CONSTRUCTOR
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

// FUNCTII MENIU --------------->

//CONSTRUCTOR
Meniu::Meniu(float x, float y, float width, float height) {
	fundal.setSize({ width, height });
	fundal.setPosition({ x, y });
	fundal.setFillColor(CuloareFundal);
	nextPositionY = y + 50.f;
}
//ADAUGARE BUTON
void Meniu::AdaugaButon(const sf::Font& font, std::string Text, StareAplicatie stare) {
	float CentruMeniu = fundal.getPosition().x + fundal.getSize().x / 2.0f;
	butoane.emplace_back(CentruMeniu, nextPositionY, font, Text, stare);
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
	AdaugaButon(font, "Neutru", NEUTRU_BUTON);
	AdaugaButon(font, "Adauga Nod", ADAUGA_NOD);
	AdaugaButon(font, "Adauga Muchie", ADAUGA_MUCHIE);
}

MeniuDreapta::MeniuDreapta(const Layout& layout, const sf::Font& font) :
	Meniu(layout.screenWidth - layout.rightMenuWidth, 0, layout.rightMenuWidth, layout.screenHeight) {
	AdaugaButon(font, "DFS", START_DFS);
}
// <----------------- END FUNCTII MENIU

// FUNCTII MANAGER CLICK ------------------------->

//CONSTRUCTOR
ManagerEvenimente::ManagerEvenimente(Graf& graf, Meniu& stanga, Meniu& dreapta, sf::RenderWindow& window) :
	G(graf), meniuStanga(stanga), meniuDreapta(dreapta), window(window) {}
//PROCESS CLICK
void ManagerEvenimente::ProceseazaClick(float x, float y) {
	StareAplicatie StareNoua = NEUTRU;
	StareNoua = meniuStanga.VerificaClick(x, y);
	if (StareNoua == NEUTRU) {
		StareNoua = meniuDreapta.VerificaClick(x, y);
	}
	if (StareNoua != NEUTRU) {
		if (G.GetNodStart() != -1) {
			G.ColoreazaNod(G.GetNodStart(), NEVIZITAT);
			G.SetNodStart(-1);
		}
		if (StareNoua == NEUTRU_BUTON) G.SetStare(NEUTRU);
		else G.SetStare(StareNoua);
	}
	else {
		if (G.GetStare() == ADAUGA_NOD) G.AdaugaNod(x, y);
		else if (G.GetStare() == ADAUGA_MUCHIE) {
			int nod = G.VerificaNod(x, y);
			if (nod != -1) {
				if (G.GetNodStart() == -1) {
					G.SetNodStart(nod);
					G.ColoreazaNod(nod, SELECTAT);
				}
				else if (nod != G.GetNodStart()) {
					G.SetNodEnd(nod);
					G.AdaugaMuchie(G.GetNodStart(), G.GetNodEnd(), 1);
					G.ColoreazaNod(G.GetNodStart(), NEVIZITAT);
					G.SetNodStart(-1);
					G.SetNodEnd(-1);
				}
			}
		}
		else if (G.GetStare() == START_DFS) {
			int nod = G.VerificaNod(x, y);
			if (nod != -1) {
				G.SetNodStart(nod);
				G.DFS(nod, [&]() {
					window.clear();
					window.draw(meniuStanga);
					window.draw(meniuDreapta);
					G.Draw();
					window.display();
					});
				G.ResetVizitat();
			}
		}
	}
}
//UPDADTE MENIURI
void ManagerEvenimente::Update() {
	StareAplicatie stareaAcum = G.GetStare();
	if (stareaAcum == NEUTRU) {
		meniuStanga.SetCuloareButon(NEUTRU_BUTON);
		meniuDreapta.SetCuloareButon(NEUTRU_BUTON);
		return;
	}
	meniuStanga.SetCuloareButon(stareaAcum);
	meniuDreapta.SetCuloareButon(stareaAcum);
}

// <------------------ END FUNCTII MANAGER CLICK