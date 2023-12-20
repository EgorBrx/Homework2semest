#include "Field.h"
#include <cmath>
#include <chrono>
Field::Field(size_t rows, size_t cols)
{
	field.resize(rows);
	for (auto it = field.begin(); it != field.end(); ++it)
	{
		it->resize(cols);
		for (auto& cell : *it) {
			cell = CreateNewCell();
		}
	}
}

size_t Field::getRows() const { return field.size(); }

size_t Field::getCols() const { return field[0].size(); }

void Field::print()
{
	for (auto it_x = field.begin(); it_x != field.end(); it_x++)
	{
		for (auto it_y = it_x->begin(); it_y != it_x->end(); it_y++)
			std::cout << (*it_y)->GetState() << " ";//;
		std::cout << std::endl;
	}
}

std::vector<std::vector<Cell*>>& Field::getField()
{
	return field;
}

Cell& Field::getCell(int32_t n, int32_t m, bool board)
{
	int32_t cols = this->getCols();
	int32_t rows = this->getRows();

	if (board == false)
		return *getField()[((n % rows) + rows) % rows][((m % cols) + cols) % cols];
	return *getField()[((n % rows) + rows) % rows][((m % cols) + cols) % cols];
}

void Field::Mix()
{

	size_t rows = getRows();
	size_t cols = getCols();
	std::vector<std::vector<Cell*>> newStateField(rows);
	for (size_t n = 0; n < rows; ++n)
	{
		newStateField[n].resize(cols);
		for (size_t m = 0; m < cols; ++m)
		{
			newStateField[n][m] = CreateNewCell();
		}
	}
	std::lock_guard<std::mutex> lock(mutex);
	for (auto& row : field)
	{
		for (auto& cell : row)
		{
				delete cell;
		}
		row.clear();
	}
	field.clear();


	field = std::move(newStateField);
	//
	//
}


/*
size_t rows = getRows();
size_t cols = getCols();

for (size_t n = 0; n < rows; ++n)
{
	for (size_t m = 0; m < cols; ++m)
	{
		ChangeCell(getCell(n, m), newFieldState[n][m]);
	}
}
*/
void Field::ChangeAllState(std::vector<std::vector<Cell*>>& newFieldState)
{
	std::lock_guard<std::mutex> lock(mutex);
	size_t rows = this->getRows();
	size_t cols = this->getCols();

	std::vector<std::thread> threads(2);

	for (int i = 0; i < 2; ++i)
	{
		threads[i] = std::thread([ this, &newFieldState, rows, cols, i]() {
			size_t startRow = (rows / 2) * i;
			size_t endRow = (i == 1) ? rows : (rows / 2) * (i + 1);
		    for (size_t row = startRow; row < endRow; ++row)
			{
				for (size_t col = 0; col < cols; ++col)
				{
					if (field[row][col] != newFieldState[row][col])
						delete field[row][col];
				}
				field[row].clear();
			}
			});
	}

	for (auto& thread : threads)
	{
		thread.join();
	}
	field.clear();

	field = std::move(newFieldState);
}
void Field::ChangeCell(Cell& cell, Cell& cellnew)
{

}
