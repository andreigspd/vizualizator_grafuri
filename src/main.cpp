#include <SFML/Graphics.hpp>
#include "../include/graf.h"
#include <iostream>
int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Grafuri");
	sf::Font font("ARIAL.TTF");

	auto desktop = sf::VideoMode::getDesktopMode();
	Layout layout(
		static_cast<float>(desktop.size.x),
		static_cast<float>(desktop.size.y),
		250.f,
		250.f
	);

	Graf G(window, font, layout);
	Meniu MeniuStanga(0, 0, layout.leftMenuWidth, layout.screenHeight);
	Meniu MeniuDreapta(layout.screenWidth - layout.rightMenuWidth, 0, layout.rightMenuWidth, layout.screenHeight);

	MeniuStanga.AdaugaButon(font, "Neutru", NEUTRU_BUTON);
	MeniuStanga.AdaugaButon(font, "Adauga Nod", ADAUGA_NOD);
	MeniuStanga.AdaugaButon(font, "Adauga Muchie", ADAUGA_MUCHIE);

	MeniuDreapta.AdaugaButon(font, "Start DFS", START_DFS);
	while (window.isOpen()) {
		while (const auto event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) window.close();
			if (const auto* mouseClicked = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (mouseClicked->button == sf::Mouse::Button::Left) {
					float x = static_cast<float>(mouseClicked->position.x);
					float y = static_cast<float>(mouseClicked->position.y);
					StareAplicatie StareNoua = NEUTRU;
					StareNoua = MeniuStanga.VerificaClick(x, y);
					if (StareNoua == NEUTRU) {
						StareNoua = MeniuDreapta.VerificaClick(x, y);
					}
					if (StareNoua != NEUTRU) {
						if (StareNoua == NEUTRU_BUTON) G.SetStare(NEUTRU);
						else G.SetStare(StareNoua);
					}
					else {
						if(G.GetStare() == ADAUGA_NOD) G.AdaugaNod(x, y);
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
								G.DFS(nod);
								G.ResetVizitat();
							}
						}
					}
				}
			}
		}
		StareAplicatie stare = G.GetStare();
		MeniuStanga.SetCuloareButon(stare);
		MeniuDreapta.SetCuloareButon(stare);

		window.clear();
		window.draw(MeniuStanga);
		window.draw(MeniuDreapta);
		G.Draw();
		window.display();
	}

}
