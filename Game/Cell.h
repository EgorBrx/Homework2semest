#pragma once
#include "CA_Object.h"
#include <iostream>
#include <random>
#include "Field.h"
#include "onField.h"
#include "Constant.h"


class Field;

class Cell : public CA_Object
{
private:
	int32_t state = 0;
	onField* objOnCell = nullptr;
public:
	Cell() 
	{
		this->Randomize();
	}
	int32_t GetState() const
	{
		return state;
	}
	void SetState(int32_t newstate)
	{
		state = newstate;
	}
	void Randomize()
	{
		state = (rand() % 4);
	}
	virtual void GetInformation(Field& field, int32_t myRow, int32_t myCols);
	//virtual int32_t changeStateOnNext()
	virtual Cell* determineNextState(Field& field, int32_t, int32_t);
	Cell(Cell&& other) noexcept = default;
	Cell(const Cell& other)
	{
		state = other.state;
		if (other.objOnCell) {
			objOnCell = new onField(*other.objOnCell);
		}
		else {
			objOnCell = nullptr;
		}
	}
	virtual Cell& operator=(Cell&& other) noexcept
	{
		//std::cout << "==";
		if (this != &other)
		{
			delete objOnCell;

			state = std::move(other.state);
			objOnCell = std::move(other.objOnCell);

			other.objOnCell = nullptr;
		}
		return *this;
	}
	virtual ~Cell()
	{
		static int i = 0;
		++i;
		//std::cout << "destroy Cell " << i << std::endl;
		delete objOnCell;
	}
};
class EmptyCell : public Cell
{
private:
	int32_t state = 0;
public:
	EmptyCell()
	{
		this->Randomize();
	}
	 Cell* determineNextState(Field& field, int32_t myRow, int32_t myCols);
	~EmptyCell(){}
};
class Plant_Cell : public Cell
{
private:
	int32_t m_humidity = 0;
	int32_t m_sun = 0;
	int32_t m_microelements = 0;
public:
	int32_t getHumidity() { return m_humidity; }
	int32_t getMicroelements() { return m_microelements; }
	void setMicroelements(int32_t newvalue) { m_microelements = newvalue; }
	void setHumidity(int32_t newvalue) { m_humidity = newvalue; }
	
	void GetInformation(Field& field, int32_t myRow, int32_t myCols)
	{
		std::cout << "humidity = "        << m_humidity      << std::endl;
		std::cout << "m_sun = "           << m_sun           << std::endl;
		std::cout << "m_microelements = " << m_microelements << std::endl;
		std::cout << "-------------------------------------" << std::endl;
	}
	 virtual Cell* determineNextState(Field& field, int32_t myRow, int32_t myCols) = 0;
	 Plant_Cell(int32_t m_humidity = 0, int32_t m_sun = 0,int32_t m_microelements = 0): m_humidity(m_humidity), m_sun(m_sun), m_microelements(m_microelements){}
	~Plant_Cell() {}
};
class Hogweed_Cell : public Plant_Cell
{
private:
	int32_t state = 0;
public:

	Cell* determineNextState(Field& field, int32_t myRow, int32_t myCols);
	Hogweed_Cell(int32_t m_humidity = 0, int32_t m_sun = 0, int32_t m_microelements = 0) : Plant_Cell(m_humidity, m_sun, m_microelements){}
	~Hogweed_Cell() {}
};
class Flycatcher_Cell : public Plant_Cell
{
private:
	int32_t state = 0;
public:

	Cell* determineNextState(Field& field, int32_t myRow, int32_t myCols);
	Flycatcher_Cell(int32_t m_humidity = 0, int32_t m_sun = 0, int32_t m_microelements = 0) : Plant_Cell(m_humidity, m_sun, m_microelements) {}
	~Flycatcher_Cell() {}
};
class Barrier_Cell : public Cell
{
private:
	int32_t state = 0;
public:

	~Barrier_Cell()
	{
		//std::cout << "destroy Cell_type2 "<< std::endl;
	}
};
class Rock_Cell : public Barrier_Cell
{
private:
	int32_t state = 0;
public:
	Cell* determineNextState(Field& field, int32_t myRow, int32_t myCols)
	{
		return this;
	}
	~Rock_Cell()
	{
	}
};
class Water_Cell : public Barrier_Cell
{
private:
	int32_t m_humadity = 0;
public:
	Water_Cell(): m_humadity(GetRandomInt(0,100)){}
	int32_t getHumadity()
	{
		return m_humadity;
	}
	Cell* determineNextState(Field& field, int32_t myRow, int32_t myCols)
	{
		return this;
	}
	~Water_Cell()
	{
		//std::cout << "destroy Cell_type2 "<< std::endl;
	}
};
class Earth_Cell : public Barrier_Cell
{
private:
	int32_t m_fertility = 0;
public:
	Earth_Cell() : m_fertility(GetRandomInt(0, 100)) {}
	int32_t GetFertility() { return m_fertility; }
	Cell* determineNextState(Field& field, int32_t myRow, int32_t myCols);
	~Earth_Cell()
	{
		//std::cout << "destroy Cell_type2 "<< std::endl;
	}
};

Cell* CreateNewCell();

std::vector<Cell*> getNeighboursMura(Field& field, int32_t myRow, int32_t myCols);


