#pragma once

enum StareAplicatie {
	NEUTRU,
	NEUTRU_BUTON,
	ADAUGA_NOD,
	ADAUGA_MUCHIE,
	ADAUGA_COST,
	ASTEAPTA_COST,
	START_DFS,
	START_BFS,
	DIJKSTRA,
	ALEGE_ORIENTAT,
	ALEGE_NEORIENTAT
};


enum CuloareNod {
	NEVIZITAT,
	SELECTAT,
	CURENT,
	VIZITAT
};
enum CuloareButon {
	ACTIV,
	INACTIV
};

struct Layout {
	float screenWidth;
	float screenHeight;
	float leftMenuWidth;
	float rightMenuWidth;
	Layout(float width, float height, float leftwidth, float rightwidth) : screenWidth(width), screenHeight(height),
		leftMenuWidth(leftwidth), rightMenuWidth(rightwidth) {
	}
	float GetCanvasX() const {
		return leftMenuWidth;
	}
	float GetCanvasWidth() const {
		return screenWidth - leftMenuWidth - rightMenuWidth;
	}
};
