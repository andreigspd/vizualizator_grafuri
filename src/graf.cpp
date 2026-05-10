#include "../include/graf.h"
#include <queue>
// METODE CLASA GRAF -------------------->
//CONSTRUCTOR
Graf::Graf(sf::RenderWindow& window, const sf::Font& font, const Layout& layout) : window(window), font(font){
	nrNoduri = 0;
	nrMuchii = 0;
	nodStart = nodEnd = -1;
	StareCurenta = NEUTRU;
	BlackScreen = sf::FloatRect(
		{ layout.GetCanvasX(), 0.f },
		{ layout.GetCanvasWidth(), layout.screenHeight }
	);
	matrix.resize(1001);
	vizitat.reserve(1001);
}
//VERIFICA CLICK IN ZONA DESENARE
bool Graf::VerificaClick(float x, float y) const {
	return BlackScreen.contains({ x, y });
}
//ADAUGA NOD GRAF
void Graf::AdaugaNod(float x, float y) {
	if (VerificaClick(x, y) == 0) return;
	noduri.emplace_back(x, y, nrNoduri + 1, font);
	nrNoduri++;
}
/*ADAUGA MUCHIE - abstract
void Graf::AdaugaMuchie(int nodStart, int nodEnd, int cost) {
	
}
*/
//DESENARE MUCHII + NODURI
void Graf::Draw() const {
	for (const auto& muchie : muchii) {
		window.draw(muchie);
	}
	for (const auto& nod : noduri) {
		window.draw(nod);
	}
}
//COLORARE NOD PARCURGERI
void Graf::ColoreazaNod(int id, CuloareNod color) {
	noduri[id - 1].SetCuloareNod(color);
}
//DFS
void Graf::DFS(int nod, const std::function<void()>& renderScene) {
	vizitat[nod] = 1;
	noduri[nod - 1].SetCuloareNod(CURENT);
	renderScene();
	sf::sleep(sf::milliseconds(500));

	for (const auto& i : matrix[nod]) {
		if (vizitat[i.first] == 0) {
			DFS(i.first, renderScene);
			noduri[nod - 1].SetCuloareNod(CURENT);
			renderScene();
			sf::sleep(sf::milliseconds(500));
		}
	}
	noduri[nod - 1].SetCuloareNod(VIZITAT);
	renderScene();
	sf::sleep(sf::milliseconds(500));

}
void Graf::BFS(int nod, const std::function<void()>& renderScene) {
	std::queue<int> q;
	q.push(nod);
	vizitat[nod] = 1;
	while (!q.empty()) {
		int nodCurent = q.front();
		q.pop();
		noduri[nodCurent - 1].SetCuloareNod(CURENT);
		renderScene();
		sf::sleep(sf::milliseconds(500));
		for (const auto& vecin : matrix[nodCurent]) {
			if (vizitat[vecin.first] == 0) {
				noduri[vecin.first - 1].SetCuloareNod(SELECTAT);
				vizitat[vecin.first] = 1;
				q.push(vecin.first);
				renderScene();
				sf::sleep(sf::milliseconds(500));
			}
		}
		noduri[nodCurent - 1].SetCuloareNod(VIZITAT);
		renderScene();
		sf::sleep(sf::milliseconds(500));
	}
}

//VERIFICA CLICK PE UN NOD
int Graf::VerificaNod(float x, float y) const {
	for (const auto& nod : noduri) {
		if (nod.VerificaClick(x, y)) {
			return nod.GetNodId();
		}
	}
	return -1;
}
//RESET FRECVENTA VIZITAT
void Graf::ResetVizitat() {
	for (const auto& i : vizitat) {
		if (i.second == 1) {
			noduri[i.first - 1].SetCuloareNod(NEVIZITAT);
		}
	}
	vizitat.clear();
}

//SETERI -------------------
void Graf::SetStare(StareAplicatie stare) {
	StareCurenta = stare;
}
void Graf::SetNodStart(int id) {
	nodStart = id;
}
void Graf::SetNodEnd(int id) {
	nodEnd = id;
}
// -------------------------
// GETERI -----------------
int Graf::GetNodEnd() const {
	return nodEnd;
}
int Graf::GetNodStart() const {
	return nodStart;
}

StareAplicatie Graf::GetStare() const{
	return StareCurenta;
}
// -------------------------------

// METODE CLASA GRAF NEORIENTAT -------------->

GrafNeorientat::GrafNeorientat(sf::RenderWindow& window, sf::Font& font, const Layout& layout) : Graf(window, font, layout) {}
void GrafNeorientat::AdaugaMuchie(int nodStart, int nodEnd, int cost) {
	bool existaMuchie = false;
	for (auto& i : matrix[nodStart]) {
		if (i.first == nodEnd) {
			i.second = cost;
			existaMuchie = true;
			break;
		}
	}
	if (existaMuchie) {
		for (auto& i : matrix[nodEnd]) {
			if (i.first == nodStart) {
				i.second = cost;
			}
		}
		for (auto& muchie : muchii) {
			if ((muchie.GetId1() == nodStart && muchie.GetId2() == nodEnd) ||
				(muchie.GetId1() == nodEnd && muchie.GetId2() == nodStart)) {
				muchie.SetCost(cost);
				break;
			}
		}
	}
	else {
		matrix[nodStart].push_back({ nodEnd, cost });
		matrix[nodEnd].push_back({ nodStart, cost });
		sf::Vector2f poz1 = noduri[nodStart - 1].GetNodPosition();
		sf::Vector2f poz2 = noduri[nodEnd - 1].GetNodPosition();
		muchii.emplace_back(poz1, poz2, nodStart, nodEnd, cost, font, false);
	}
}

GrafOrientat::GrafOrientat(sf::RenderWindow& window, sf::Font& font, const Layout& layout) : Graf(window, font, layout) {}
void GrafOrientat::AdaugaMuchie(int nodStart, int nodEnd, int cost) {
	bool existaMuchie = false;
	for (auto& i : matrix[nodStart]) {
		if (i.first == nodEnd) {
			i.second = cost;
			existaMuchie = true;
			break;
		}
	}
	if (existaMuchie) {
		for (auto& muchie : muchii) {
			if ((muchie.GetId1() == nodStart && muchie.GetId2() == nodEnd)) {
				muchie.SetCost(cost);
				break;
			}
		}
	}
	else {
		matrix[nodStart].push_back({ nodEnd, cost });
		sf::Vector2f poz1 = noduri[nodStart - 1].GetNodPosition();
		sf::Vector2f poz2 = noduri[nodEnd - 1].GetNodPosition();
		muchii.emplace_back(poz1, poz2, nodStart, nodEnd, cost, font, true);
	}
}

//METODE CLASA NOD ---------------------------->
//CONSTRUCTOR
Nod::Nod(float x, float y, int index, const sf::Font& font) : id(index), text(font) {
	cerc.setRadius(radius);
	cerc.setOrigin({ radius, radius });
	cerc.setPosition({ x, y });
	cerc.setFillColor(sf::Color::Cyan);
	cerc.setOutlineColor(sf::Color::Blue);
	cerc.setOutlineThickness(1);

	text.setString(std::to_string(index));
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::Black);
	const auto bounds = text.getLocalBounds();
	text.setOrigin({
		bounds.position.x + bounds.size.x / 2.0f,
		bounds.position.y + bounds.size.y / 2.0f
		});
	text.setPosition({ x, y });
}

//VERIFICA CLICK PE NOD RESPECTIV
bool Nod::VerificaClick(float x, float y) const {
	return cerc.getGlobalBounds().contains({ x, y });
}

// GETERI ->>>>>>>>>>>
int Nod::GetNodId() const {
	return id;
}

sf::Vector2f Nod::GetNodPosition() const {
	return cerc.getPosition();
}
// --------------------------

// SETERI ----------------->
void Nod::SetCuloareNod(CuloareNod color) {
	switch (color) {
	case NEVIZITAT:
		cerc.setFillColor(sf::Color::Cyan);
		break;
	case VIZITAT:
		cerc.setFillColor(sf::Color::Green);
		break;
	case CURENT:
		cerc.setFillColor(sf::Color::Yellow);
		break;
	case SELECTAT:
		cerc.setFillColor(sf::Color::Red);
		break;
	}
}
// -----------------------------------

// METODE CLASA MUCHIE ---------------->
//CONSTRUCTOR
Muchie::Muchie(sf::Vector2f poz1, sf::Vector2f poz2, int id1, int id2, int cost, const sf::Font& font, bool orientat) :
	costText(font), idNod1(id1), idNod2(id2), cost(cost), esteOrientat(orientat) {
	float dx = poz2.x - poz1.x;
	float dy = poz2.y - poz1.y;
	float distanta = sqrt(dx * dx + dy * dy);

	linie.setSize({ distanta, grosime });
	linie.setOrigin({ 0.f, grosime / 2.0f });
	linie.setPosition(poz1);
	linie.setFillColor(sf::Color::Magenta);

	float unghiRadiani = std::atan2(dy, dx);
	linie.setRotation(sf::radians(unghiRadiani));
	if (esteOrientat) {
		float razaSageata = 12.f;
		sageata.setRadius(razaSageata);
		sageata.setPointCount(3);
		sageata.setFillColor(sf::Color::Magenta);
		sageata.setOrigin({ razaSageata, 0.f });
		float margineNodEndX = poz2.x - 30.f * std::cos(unghiRadiani);
		float margineNodEndY = poz2.y - 30.f * std::sin(unghiRadiani);
		sageata.setPosition({ margineNodEndX, margineNodEndY });
		sageata.setRotation(sf::radians(unghiRadiani + pi / 2));
	}

	costText.setString(std::to_string(cost));
	costText.setCharacterSize(16);
	costText.setFillColor(sf::Color::Yellow);
	const auto bounds = costText.getLocalBounds();
	costText.setOrigin({
		bounds.position.x + bounds.size.x / 2.0f,
		bounds.position.y + bounds.size.y / 2.0f
		});
	costText.setPosition({ poz1.x + dx / 2.0f, poz1.y + dy / 2.0f - 15.f});
}
// SETERI 
void Muchie::SetCost(int c) {
	cost = c;
	costText.setString(std::to_string(cost));
}

// GETERI
int Muchie::GetId1() const {
	return idNod1;
}
int Muchie::GetId2() const {
	return idNod2;
}
