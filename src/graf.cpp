#include "../include/graf.h"

Graf::Graf(sf::RenderWindow& window, const sf::Font& font, const Layout& layout) : window(window), font(font){
	nrNoduri = 0;
	nrMuchii = 0;
	StareCurenta = NEUTRU;
	BlackScreen = sf::FloatRect(
		{ layout.GetCanvasX(), 0.f },
		{ layout.GetCanvasWidth(), layout.screenHeight }
	);
}
bool Graf::VerificaClick(float x, float y) {
	return BlackScreen.contains({ x, y });
}
void Graf::AdaugaNod(float x, float y) {
	if (VerificaClick(x, y) == 0) return;
	noduri.emplace_back(x, y, nrNoduri + 1, font);
	nrNoduri++;
}
void Graf::Draw() {
	for (const auto& nod : noduri) {
		window.draw(nod);
	}
}
void Graf::SetStare(StareAplicatie stare) {
	StareCurenta = stare;
}
StareAplicatie Graf::GetStare() {
	return StareCurenta;
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
