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

	MeniuStanga.AdaugaButon(font, "Adauga Nod", ADAUGA_NOD);
	MeniuStanga.AdaugaButon(font, "Adauga Muchie", ADAUGA_MUCHIE1);

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
						G.SetStare(StareNoua);
					}
					else {
						if(G.GetStare() == ADAUGA_NOD) G.AdaugaNod(x, y);
						else if (G.GetStare() == ADAUGA_MUCHIE1) {
							int nod = G.VerificaNod(x, y);
							if (nod != -1) {
								G.SetNodStart(nod);
								G.SetStare(ADAUGA_MUCHIE2);
							}
						}
						else if (G.GetStare() == ADAUGA_MUCHIE2) {
							int nod = G.VerificaNod(x, y);
							if (nod != -1 && nod != G.GetNodStart()) {
								G.SetNodEnd(nod);
								G.AdaugaMuchie(G.GetNodStart(), G.GetNodEnd(), 1);
								G.SetNodStart(-1);
								G.SetNodEnd(-1);
								G.SetStare(ADAUGA_MUCHIE1);
							}
						}
					}
				}
			}
		}
		window.clear();
		window.draw(MeniuStanga);
		window.draw(MeniuDreapta);
		G.Draw();
		window.display();
	}

}
