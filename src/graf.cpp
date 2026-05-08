#include "../include/graf.h"

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
bool Graf::VerificaClick(float x, float y) const {
	return BlackScreen.contains({ x, y });
}
void Graf::AdaugaNod(float x, float y) {
	if (VerificaClick(x, y) == 0) return;
	noduri.emplace_back(x, y, nrNoduri + 1, font);
	nrNoduri++;
}
void Graf::AdaugaMuchie(int nodStart, int nodEnd, int cost) {
	matrix[nodStart].push_back({ nodEnd, cost });
	matrix[nodEnd].push_back({ nodStart, cost });
	sf::Vector2f poz1 = noduri[nodStart - 1].GetNodPosition();
	sf::Vector2f poz2 = noduri[nodEnd - 1].GetNodPosition();
	muchii.emplace_back(poz1, poz2, nodStart, nodEnd, cost, font);
}
void Graf::Draw() const {
	for (const auto& muchie : muchii) {
		window.draw(muchie);
	}
	for (const auto& nod : noduri) {
		window.draw(nod);
	}
}
void Graf::SetStare(StareAplicatie stare) {
	StareCurenta = stare;
}
void Graf::SetNodStart(int id) {
	nodStart = id;
}
void Graf::SetNodEnd(int id) {
	nodEnd = id;
}
int Graf::GetNodEnd() const {
	return nodEnd;
}
int Graf::GetNodStart() const {
	return nodStart;
}

StareAplicatie Graf::GetStare() const{
	return StareCurenta;
}

void Graf::ColoreazaNod(int id, CuloareNod color) {
	noduri[id - 1].SetCuloareNod(color);
}
void Graf::DFS(int nod) {
	vizitat[nod] = 1;
	noduri[nod - 1].SetCuloareNod(CURENT);
	window.clear();
	Draw();
	window.display();
	sf::sleep(sf::milliseconds(500));

	for (const auto& i : matrix[nod]) {
		if (vizitat[i.first] == 0) {
			DFS(i.first);
			noduri[nod - 1].SetCuloareNod(CURENT);
			window.clear(); Draw(); window.display(); sf::sleep(sf::milliseconds(500));
		}
	}
	noduri[nod - 1].SetCuloareNod(VIZITAT);
	window.clear();
	Draw();
	window.display();
	sf::sleep(sf::milliseconds(500));

}

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
int Nod::GetNodId() const {
	return id;
}
bool Nod::VerificaClick(float x, float y) const {
	return cerc.getGlobalBounds().contains({ x, y });
}
sf::Vector2f Nod::GetNodPosition() const {
	return cerc.getPosition();
}

int Graf::VerificaNod(float x, float y) const {
	for (const auto& nod : noduri) {
		if (nod.VerificaClick(x, y)) {
			return nod.GetNodId();
		}
	}
	return -1;
}
void Graf::ResetVizitat() {
	for (const auto& i : vizitat) {
		if (i.second == 1) {
			noduri[i.first - 1].SetCuloareNod(NEVIZITAT);
		}
	}
	vizitat.clear();
}

void Nod::SetCuloareNod(CuloareNod color) {
	switch (color) {
	case NEUTRU:
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

Muchie::Muchie(sf::Vector2f poz1, sf::Vector2f poz2, int id1, int id2, int cost, const sf::Font& font) :
	costText(font), idNod1(id1), idNod2(id2), cost(cost) {
	float dx = poz2.x - poz1.x;
	float dy = poz2.y - poz1.y;
	float distanta = sqrt(dx * dx + dy * dy);

	linie.setSize({ distanta, grosime });
	linie.setOrigin({ 0.f, grosime / 2.0f });
	linie.setPosition(poz1);
	linie.setFillColor(sf::Color::Magenta);

	float unghiRadiani = std::atan2(dy, dx);
	linie.setRotation(sf::radians(unghiRadiani));

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