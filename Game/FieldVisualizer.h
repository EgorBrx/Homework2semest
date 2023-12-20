#pragma once
#include <iostream>
#include "Field.h"
#include <SFML/Graphics.hpp>
#include "Constant.h"
struct FieldVisualizer {
    std::vector<std::vector<sf::RectangleShape>> cells;
    FieldVisualizer(int32_t rows = 0, int32_t cols = 0);
    void InitCells(int32_t, int32_t);
    void renderCells(sf::RenderWindow& window, Field& field);
    const std::vector<std::vector<sf::RectangleShape>>& getCells() const;
    void renderCellsAndLines(sf::RenderWindow& window, Field& field, int32_t rows, int32_t cols);
    void SetCellColor(sf::RectangleShape& cellView, Cell& cell)
    {
        if (typeid(cell) == typeid(EmptyCell)) {
            // Visualization for AliveCell
            cellView.setFillColor(BLACK_SF);
        }
        else if (typeid(cell) == typeid(Rock_Cell)) {
            // Visualization for DeadCell
            cellView.setFillColor(GREY_SF);
        }
        else if (typeid(cell) == typeid(Water_Cell)) {
            // Visualization for AnotherCellType
            cellView.setFillColor(BLUE_SF);
        }
        else if (typeid(cell) == typeid(Earth_Cell)) {
            // Visualization for AnotherCellType
            cellView.setFillColor(BROWN_SF);
        }
        else if (typeid(cell) == typeid(Flycatcher_Cell)) {
            // Visualization for AnotherCellType
            cellView.setFillColor(RED_SF);
        }
        else if (typeid(cell) == typeid(Hogweed_Cell)) {
            // Visualization for AnotherCellType
            cellView.setFillColor(GREEN_SF);
        }
        else {
            // Default visualization
            cellView.setFillColor(GREY_SF);
        }
    }


};
class CellVisualizer {
private:
    class CellVisualizationStrategy {
    public:
        virtual ~CellVisualizationStrategy() {}
        virtual void visualize(sf::RectangleShape& shape) const = 0;
    };

    // Внутренний класс для конкретной стратегии визуализации
    class CellType1VisualizationStrategy : public CellVisualizationStrategy {
    public:
        void visualize(sf::RectangleShape& shape) const override {
            // Логика визуализации для CellType1
            shape.setFillColor(sf::Color::Red);
        }
    };

    class CellType2VisualizationStrategy : public CellVisualizationStrategy {
    public:
        void visualize(sf::RectangleShape& shape) const override {
            // Логика визуализации для CellType2
            shape.setFillColor(sf::Color::Green);
        }
    };

    // Указатель на текущую стратегию визуализации
    std::unique_ptr<CellVisualizationStrategy> visualizationStrategy;

public:
    void visualize(const Cell& cell, sf::RectangleShape& shape) const {
        if (visualizationStrategy) {
            visualizationStrategy->visualize(shape);
        }
    }

    void setVisualizationStrategy(std::unique_ptr<CellVisualizationStrategy> strategy) {
        visualizationStrategy = std::move(strategy);
    }
};