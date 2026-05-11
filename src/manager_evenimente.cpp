#include "../include/manager_evenimente.h"
// FUNCTII MANAGER CLICK ------------------------->

//CONSTRUCTOR
ManagerEvenimente::ManagerEvenimente(Graf& graf, Meniu& stanga, Meniu& dreapta, sf::RenderWindow& window, const sf::Font& font) :
	G(graf), meniuStanga(stanga), meniuDreapta(dreapta), window(window), font(font), inputText(font) {
	inputBox.setSize({ 200.f, 50.f });
	inputBox.setFillColor(sf::Color(50, 50, 50, 200));
	inputBox.setOutlineThickness(2);
	inputBox.setOrigin({ 100.f, 25.f });
	inputBox.setPosition({ window.getSize().x / 2.0f, 50.f });

	inputText.setFont(font);
	inputText.setString("Cost: ");
	inputText.setCharacterSize(20);
	inputText.setFillColor(sf::Color::White);
	inputText.setPosition({ window.getSize().x / 2.0f - 80.f, 40.f });

}
//PROCESS CLICK
void ManagerEvenimente::ProceseazaClick(float x, float y) {
	StareAplicatie StareNoua = NEUTRU;
	StareNoua = meniuStanga.VerificaClick(x, y);
	if (StareNoua == NEUTRU) {
		StareNoua = meniuDreapta.VerificaClick(x, y);
	}
	if (StareNoua != NEUTRU) {
		if (G.GetNodStart() != -1) {
			G.SetNodStart(-1);
		}
		if (StareNoua == NEUTRU_BUTON) G.SetStare(NEUTRU), G.ResetVizitat();
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
				G.ResetVizitat();
				G.SetNodStart(nod);
				G.DFS(nod, [&]() {
					window.clear();
					window.draw(meniuStanga);
					window.draw(meniuDreapta);
					G.Draw();
					window.display();
					});
			}
		}
		else if (G.GetStare() == START_BFS) {
			int nod = G.VerificaClick(x, y);
			if (nod != -1) {
				G.ResetVizitat();
				G.SetNodStart(nod);
				G.BFS(nod, [&] {
					window.clear();
					window.draw(meniuStanga);
					window.draw(meniuDreapta);
					G.Draw();
					window.display();
					});
			}
		}
		else if (G.GetStare() == ADAUGA_COST) {
			int nod = G.VerificaNod(x, y);
			if (nod != -1) {
				if (G.GetNodStart() == -1) {
					G.SetNodStart(nod);
					G.ColoreazaNod(nod, SELECTAT);
				}
				else {
					if (nod != G.GetNodStart()) {
						G.SetNodEnd(nod);
						G.ColoreazaNod(nod, SELECTAT);
						G.SetStare(ASTEAPTA_COST);
					}
				}
			}
		}
		else if (G.GetStare() == DIJKSTRA) {
			int nod = G.VerificaNod(x, y);
			if (nod != -1) {
				G.ResetVizitat();
				G.SetNodStart(nod);
				G.Dijkstra(nod, [&] {
					window.clear();
					window.draw(meniuStanga);
					window.draw(meniuDreapta);
					G.Draw();
					window.display();
					});			
			}
		}
	}
}
// PROCESEAZA INPUT
void ManagerEvenimente::ProceseazaTastatura(int c) {
	if (G.GetStare() == ASTEAPTA_COST) {
		if (c == 8 && !inputCost.empty()) {
			inputCost.pop_back();
			DrawInputBox();
		}
		else if (c == 13 || c == 10) {
			DrawInputBox();
			int cost = 1;
			if (!inputCost.empty()) cost = std::stoi(inputCost);
			G.AdaugaMuchie(G.GetNodStart(), G.GetNodEnd(), cost);
			G.ColoreazaNod(G.GetNodStart(), NEVIZITAT);
			G.ColoreazaNod(G.GetNodEnd(), NEVIZITAT);
			G.SetNodStart(-1);
			G.SetNodEnd(-1);
			G.SetStare(ADAUGA_COST);
			inputCost = "";
		}
		else if (c >= '0' && c <= '9') {
			inputCost += static_cast<char>(c);
			DrawInputBox();
		}
		inputText.setString("Cost: " + inputCost);
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
	else if (stareaAcum == ASTEAPTA_COST) {
		meniuStanga.SetCuloareButon(ADAUGA_COST);
		meniuDreapta.SetCuloareButon(ADAUGA_COST);
		return;
	}
	meniuStanga.SetCuloareButon(stareaAcum);
	meniuDreapta.SetCuloareButon(stareaAcum);
}

void ManagerEvenimente::DrawInputBox() {
	if (G.GetStare() == ASTEAPTA_COST) {
		window.draw(inputBox);
		window.draw(inputText);
	}
}
// <------------------ END FUNCTII MANAGER CLICK