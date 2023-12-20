#pragma once
#include "Cell.h"
#include <vector>
#include <iostream>
#include <mutex>
class Cell;

class Field
{
private:
	std::vector<std::vector<Cell*>> field;
public:
	std::mutex mutex;
	Field(size_t rows, size_t cols);
	//Field(const Field&& field) = default;
	size_t getRows() const;
	size_t getCols() const;
	void print();
	std::vector<std::vector<Cell*>>& getField();
	
	Cell& getCell(int32_t n, int32_t m, bool = false);
	void Mix();
	void ChangeAllState(std::vector<std::vector<Cell*>>& newFieldState);
	void ChangeCell(Cell& cell, Cell& cellnew);
	bool isBoard(int32_t n, int32_t m)
	{
		int32_t maxRow = getRows();
		int32_t maxCol = getCols();

		if (n == maxRow - 1 || n == 0) return true;
		if (m == maxCol - 1 || m == 0) return true;
		return false;
	}
};

