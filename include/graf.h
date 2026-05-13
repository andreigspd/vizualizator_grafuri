#pragma once
#include "../include/nod.h"
#include "../include/muchie.h"
#include <SFML/Graphics.hpp>
#include <queue>
#include <SFML/System.hpp>
struct compareCost {
	bool operator()(std::pair<int, int> a, std::pair<int, int> b) {
		if (a.second == b.second) return a.first < b.first;
		return a.second > b.second;
	}
};


class Graf {
protected:
	StareAplicatie StareCurenta;
	int nrNoduri, nrMuchii;
	std::vector<Nod> noduri;
	std::unordered_map<int, int>vizitat;
	std::vector<Muchie> muchii;
	int nodStart, nodEnd;

	std::vector<std::vector<std::pair<int, int>>> matrix;
	std::priority_queue < std::pair<int, int>, std::vector<std::pair<int, int> >, compareCost> pq;
	std::vector<int> distantaDijkstra;

	sf::RenderWindow& window;
	const sf::Font& font;
	sf::FloatRect BlackScreen;
	sf::Text mesajEroare;
	

public:
	Graf(sf::RenderWindow& window, const sf::Font& font, const Layout& layout);
	virtual ~Graf() = default;
	void AdaugaNod(float x, float y);
	void StergeNod(int id);
	virtual void AdaugaMuchie(int idNod1, int idNod2, int cost) = 0;
	void DFS(int startNod, const std::function<void()>& renderScene);
	void BFS(int startNod, const std::function<void()>& renderScene);
	void Dijkstra(int startNod, const std::function<void()>& renderScene);
	void Draw() const;
	bool VerificaClick(float x, float y) const;
	int VerificaNod(float x, float y) const;
	void SetStare(StareAplicatie stare);
	void SetNodStart(int id);
	void SetNodEnd(int id);
	void SetMesajEroare(std::string);
	int GetNodStart() const;
	int GetNodEnd() const;
	void ColoreazaNod(int id, CuloareNod color);
	StareAplicatie GetStare() const;
	void ResetVizitat();
};

class GrafNeorientat : public Graf {
public:
	GrafNeorientat(sf::RenderWindow& window, sf::Font& font, const Layout& layout);
	void AdaugaMuchie(int idNod1, int idNod2, int cost) override;
};

class GrafOrientat : public Graf {
public:
	GrafOrientat(sf::RenderWindow& window, sf::Font& font, const Layout& layout);
	void AdaugaMuchie(int idNod1, int idNod2, int cost) override;
};