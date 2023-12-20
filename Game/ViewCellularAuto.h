#pragma once
#include "FieldVisualizer.h"
#include <SFML/Graphics.hpp>
class ViewCellularAuto
{
private:
	sf::RenderWindow& window;
	FieldVisualizer fieldVisualizer;
public:
	ViewCellularAuto(sf::RenderWindow& window) : window(window) {}
	FieldVisualizer& GetFieldVisualizer() { return fieldVisualizer; }
	void renderCellsAndLines(Field& field,int32_t rows, int32_t cols)
	{
		fieldVisualizer.renderCellsAndLines(window, field, rows, cols);
	}
};

