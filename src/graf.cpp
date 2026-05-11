#include "../include/graf.h"
#include "../include/util.h"
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

void Graf::Dijkstra(int startNod, const std::function<void()>& renderScene) {
	distantaDijkstra.assign(nrNoduri + 1, INT_MAX);
	for (int i = 0; i < nrNoduri; ++i) {
		noduri[i].SetCuloareNod(NEVIZITAT);
		noduri[i].SetTextCost(INT_MAX);
	}
	noduri[startNod - 1].SetTextCost(0);
	distantaDijkstra[startNod] = 0;
	noduri[startNod - 1].SetCuloareNod(SELECTAT);
	renderScene();
	sf::sleep(sf::milliseconds(500));
	pq.push({ startNod, 0});
	while (!pq.empty()) {
		int nodCurent = pq.top().first;
		int costCurent = pq.top().second;
		noduri[nodCurent - 1].SetCuloareNod(CURENT);
		renderScene();
		sf::sleep(sf::milliseconds(500));
		pq.pop();
		if (costCurent > distantaDijkstra[nodCurent]) {
			noduri[nodCurent - 1].SetCuloareNod(VIZITAT);
			continue;
		}
		for (const auto& i : matrix[nodCurent]) {
			int nodVecin = i.first;
			int costVecin = i.second;
			if (distantaDijkstra[nodCurent] + costVecin < distantaDijkstra[nodVecin]) {
				noduri[nodVecin - 1].SetTextCost(distantaDijkstra[nodCurent] + costVecin);
				distantaDijkstra[nodVecin] = distantaDijkstra[nodCurent] + costVecin;
				pq.push({ nodVecin, distantaDijkstra[nodVecin] });
				noduri[nodVecin - 1].SetCuloareNod(SELECTAT);
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
	for (auto& i : noduri) {
		i.SetCuloareNod(NEVIZITAT);
		i.SetTextCost(-1);
	}
	vizitat.clear();
	pq = std::priority_queue < std::pair<int, int>, std::vector<std::pair<int, int> >, compareCost>();

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


