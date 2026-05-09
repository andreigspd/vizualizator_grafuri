#include "../include/header.h"
#include "../include/graf.h"
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

ManagerEvenimente::ManagerEvenimente(Graf& graf, Meniu& stanga, Meniu& dreapta, sf::RenderWindow& window) :
	G(graf), meniuStanga(stanga), meniuDreapta(dreapta), window(window) {}
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