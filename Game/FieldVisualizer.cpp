#include "FieldVisualizer.h"

FieldVisualizer::FieldVisualizer(int32_t rows, int32_t cols)
{
    InitCells(rows, cols);
}
void FieldVisualizer::InitCells(int32_t rows, int32_t cols)
{
    cells.resize(rows);
    for (auto it = cells.begin(); it != cells.end(); ++it)
    {
        it->resize(cols);
    }
    for (int32_t i = 0; i < rows; i++) {
        for (int32_t j = 0; j < cols; j++) {
            cells[i][j].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cells[i][j].setPosition(j * CELL_SIZE, i * CELL_SIZE);
            cells[i][j].setFillColor(sf::Color::Black);
        }
    }
}
void FieldVisualizer::renderCells(sf::RenderWindow& window, Field& field)
{
   
   // auto start = std::chrono::high_resolution_clock::now();
    auto it_xField = field.getField().begin();
    for (auto it_x = cells.begin(); it_x != cells.end(); it_x++, it_xField++)
    {
        auto it_yField = it_xField->begin();
        for (auto it_y = it_x->begin(); it_y != it_x->end(); it_y++, it_yField++)
        {
            SetCellColor(*it_y, **it_yField);
            window.draw(*it_y);
        }
    }
   // auto end = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
   // std::cout << "RenderTimer : " << duration.count() << " ms" << std::endl;
}

const std::vector<std::vector<sf::RectangleShape>>& FieldVisualizer::getCells() const
{
    return cells;
}

void FieldVisualizer::renderCellsAndLines(sf::RenderWindow& window, Field& field, int32_t rows, int32_t cols) {
    
    window.clear(sf::Color::Black);
    this->renderCells(window, field);

    for (int32_t i = 0; i <= cols; i++) 
    {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(i * CELL_SIZE, 0)),
            sf::Vertex(sf::Vector2f(i * CELL_SIZE, window.getSize().y))
        };
    }

    for (int32_t i = 0; i <= rows; i++)
    {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0, i * CELL_SIZE)),
            sf::Vertex(sf::Vector2f(window.getSize().x, i * CELL_SIZE))
        };
    }
    window.display();
}
