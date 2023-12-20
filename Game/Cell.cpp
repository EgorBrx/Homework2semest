#include "Cell.h"

void Cell::GetInformation(Field& field, int32_t myRow, int32_t myCols)
{
	int32_t maxRows           = field.getRows();
	int32_t maxCols           = field.getCols();
	int32_t flycatch_point    = 0;
	int32_t hogweeed_point    = 0;
	int32_t hogweeed_humadity = 0;
	int32_t flycatch_humadity = 0;
	std::vector<Cell*> neighbours = getNeighboursMura(field, myRow, myCols);

	for (auto it : neighbours)
	{

		if (dynamic_cast<Flycatcher_Cell*>(it) != nullptr)
		{
			++flycatch_point;
			flycatch_humadity += dynamic_cast<Flycatcher_Cell*>(it)->getHumidity();
		}
		if (dynamic_cast<Hogweed_Cell*>(it) != nullptr)
		{
			++hogweeed_point;
			hogweeed_humadity += dynamic_cast<Hogweed_Cell*>(it)->getHumidity();
		}
	}
	std::cout << "flycatch_neighbours_count= "    << flycatch_point    << std::endl;
	std::cout << "flycatch_humadity_neighbours= " << flycatch_humadity << std::endl;
	std::cout << "hogweeed_neighbours_count= "    << hogweeed_point    << std::endl;
	std::cout << "hogweeed_humadity_neighbours= " << hogweeed_humadity << std::endl;
	
	if ((flycatch_point == 0) && (hogweeed_point == 0))
	{
		std::cout << "CREATE NOTHING" << std::endl;
	}
	if ((flycatch_point > hogweeed_point) && flycatch_humadity > 20)
	{
		std::cout << "CREATE FLYCATCH" << std::endl;
	}
	if ((flycatch_point <= hogweeed_point) && hogweeed_humadity > 20)
	{
		std::cout << "CREATE HOGWEED" << std::endl;
	}
	std::cout << "---------------------------------------------------" << std::endl;
}
Cell* Cell::determineNextState(Field& field, int32_t myRow, int32_t myCols)
{
	/*
	Заметка:
	наверное надо собирать соседей в field, а то и в cellAuto, и передавать их сюда, это будет логичнее, но непонятно, как расширять, если хотим взять другое соседство
	*/
	int32_t maxRows = field.getRows();
	int32_t maxCols = field.getCols();
	return CreateNewCell();
	//return CreateNewCell();
	/*
	if (field.isBoard(myRow, myCols) &&( field.getCell(myRow, myCols - 1).GetState() == 1 || field.getCell(myRow, myCols + 1).GetState() == 1)) return 1;
	if (field.getCell(myRow - 1, myCols).GetState() == 1)
	{
		return 1;
	}
	if (field.getCell(myRow - 1, myCols).GetState() == 0 && GetState() == 1)
	{
		return 0;
	}
	*/
	
	return this;
}

int GetRandomInt(int min, int max)
{
	return min + (std::rand() % (max - min + 1));
}

Cell* CreateNewCell()
{
	int n = GetRandomInt(0, CELL_COUNT - 1);
	switch (n)
	{
	case 0:
		return new EmptyCell();
		break;
	case 1:
		return new Rock_Cell();
		break;
	case 2:
		return new Water_Cell();
		break;
	case 3:
		return new Earth_Cell();
		break;
	case 4:
		return new Hogweed_Cell();
		break;
	case 5:
		return new Flycatcher_Cell();
		break;
	default:
		return new Cell();
	}
}

std::vector<Cell*> getNeighboursMura(Field& field, int32_t myRow, int32_t myCols)
{
	std::vector<Cell*> neighbours;

	neighbours.push_back(&field.getCell(myRow - 1, myCols));
	neighbours.push_back(&field.getCell(myRow + 1, myCols));
	neighbours.push_back(&field.getCell(myRow, myCols - 1));
	neighbours.push_back(&field.getCell(myRow, myCols + 1));
	neighbours.push_back(&field.getCell(myRow - 1, myCols - 1));
	neighbours.push_back(&field.getCell(myRow - 1, myCols + 1));
	neighbours.push_back(&field.getCell(myRow + 1, myCols - 1));
	neighbours.push_back(&field.getCell(myRow + 1, myCols + 1));

	return neighbours;
}

Cell* EmptyCell::determineNextState(Field& field, int32_t myRow, int32_t myCols)
{
	int32_t maxRows           = field.getRows();
	int32_t maxCols           = field.getCols();
	int32_t flycatch_point    = 0;
	int32_t hogweeed_point    = 0;
	int32_t hogweeed_humadity = 0;
	int32_t flycatch_humadity = 0;
	int32_t hogweeed_microelements = 0;
	int32_t flycatch_microelements = 0;
	std::vector<Cell*> neighbours = getNeighboursMura(field, myRow, myCols);

	for (auto it : neighbours)
	{
		
		if (dynamic_cast<Flycatcher_Cell*>(it) != nullptr)
		{
			++flycatch_point;
			flycatch_humadity += dynamic_cast<Flycatcher_Cell*>(it)->getHumidity()*GetRandomInt(1,3);
			flycatch_microelements += dynamic_cast<Flycatcher_Cell*>(it)->getMicroelements();
		}
		if (dynamic_cast<Hogweed_Cell*>(it) != nullptr)
		{
			++hogweeed_point;
			hogweeed_humadity += dynamic_cast<Hogweed_Cell*>(it)->getHumidity() * GetRandomInt(1, 3);
			hogweeed_microelements += dynamic_cast<Hogweed_Cell*>(it)->getMicroelements();
		}
	}
	//std::cout << "(" << flycatch_point << ", " << hogweeed_point << ") ";
	if ((flycatch_point == 0) && (hogweeed_point == 0))
	{
		return this;
	}
	if ((flycatch_point >= hogweeed_point) && flycatch_humadity > 35)
	{
		for (auto it : neighbours)
		{

			if (dynamic_cast<Flycatcher_Cell*>(it) != nullptr)
			{
				dynamic_cast<Flycatcher_Cell*>(it)->setMicroelements(dynamic_cast<Flycatcher_Cell*>(it)->getMicroelements() - 1);
			}

		}
		return new Flycatcher_Cell();
	}
	if ((flycatch_point <= hogweeed_point) && hogweeed_humadity > 35)
	{
		for (auto it : neighbours)
		{

			if (dynamic_cast<Hogweed_Cell*>(it) != nullptr)
			{
				dynamic_cast<Hogweed_Cell*>(it)->setMicroelements(dynamic_cast<Hogweed_Cell*>(it)->getMicroelements() - 1);
			}
		}
		return new Hogweed_Cell();
	}
	return this;

}

Cell* Hogweed_Cell::determineNextState(Field& field, int32_t myRow, int32_t myCols)
{
	int32_t maxRows = field.getRows();
	int32_t maxCols = field.getCols();
	int32_t hogweeed_count = 1;
	int32_t hogweeed_humadity = (this->getHumidity() - HOGWEED_HUMIDITY_LESS)/2;
	int32_t hogweeed_microelements= this->getMicroelements();
	std::vector<Cell*> neighbours = getNeighboursMura(field, myRow, myCols);

	for (auto it : neighbours)
	{

		if (dynamic_cast<Hogweed_Cell*>(it) != nullptr)
		{
			hogweeed_humadity      += dynamic_cast<Hogweed_Cell*>(it)->getHumidity()/2;
			hogweeed_count++;
		}
		if (dynamic_cast<Water_Cell*>(it) != nullptr)
		{
			hogweeed_humadity += dynamic_cast<Water_Cell*>(it)->getHumadity();
		}
		if (dynamic_cast<Flycatcher_Cell*>(it) != nullptr)
		{
			hogweeed_humadity -= FLYCATHER_HUMIDITY_SUCK;
		}
	}
	
	this->setHumidity(hogweeed_humadity / hogweeed_count);////
	this->setMicroelements(hogweeed_microelements-1);
	if (getHumidity() < 0 || getMicroelements() < 0)
		return new Earth_Cell();
	return this;

}

Cell* Earth_Cell::determineNextState(Field& field, int32_t myRow, int32_t myCols)
{
	int32_t maxRows           = field.getRows();
	int32_t maxCols           = field.getCols();
	int32_t flycatch_point    = 0;
	int32_t hogweeed_point    = 0;
	int32_t hogweeed_humadity = 0;
	int32_t flycatch_humadity = 0;

	std::vector<Cell*> neighbours = getNeighboursMura(field, myRow, myCols);

	for (auto it : neighbours)
	{

		if (dynamic_cast<Flycatcher_Cell*>(it) != nullptr)
		{
			++flycatch_point;
			flycatch_humadity += dynamic_cast<Flycatcher_Cell*>(it)->getHumidity();
		}
		if (dynamic_cast<Hogweed_Cell*>(it) != nullptr)
		{
			++hogweeed_point;
			hogweeed_humadity += dynamic_cast<Hogweed_Cell*>(it)->getHumidity();
		}
	}
	//std::cout << "(" << flycatch_point << ", " << hogweeed_point << ") ";
	if ((flycatch_point == 0) && (hogweeed_point == 0))
	{
		return this;
	}
	if ((flycatch_point >= hogweeed_point) && flycatch_humadity > 20)
	{

		return new Flycatcher_Cell(0, 0, GetFertility());
	}
	if ((flycatch_point <= hogweeed_point) && hogweeed_humadity > 20)
	{

		return new Hogweed_Cell(0,0, GetFertility());
	}
	return this;

}

Cell* Flycatcher_Cell::determineNextState(Field& field, int32_t myRow, int32_t myCols)
{
	int32_t maxRows = field.getRows();
	int32_t maxCols = field.getCols();
	int32_t flycatch_count = 1;
	int32_t flycatch_humadity = (this->getHumidity() - FLYCATHER_HUMIDITY_LESS) / 2;
	int32_t flycatch_microelements = this->getMicroelements();
	std::vector<Cell*> neighbours = getNeighboursMura(field, myRow, myCols);

	for (auto it : neighbours)
	{

		if (dynamic_cast<Flycatcher_Cell*>(it) != nullptr)
		{
			flycatch_humadity += dynamic_cast<Flycatcher_Cell*>(it)->getHumidity() / 2;
			flycatch_count++;
		}
		if (dynamic_cast<Water_Cell*>(it) != nullptr)
		{
			flycatch_humadity += dynamic_cast<Water_Cell*>(it)->getHumadity();
		}
		if (dynamic_cast<Hogweed_Cell*>(it) != nullptr)
		{
			flycatch_humadity += FLYCATHER_HUMIDITY_SUCK;
		}
	}

	this->setHumidity(flycatch_humadity / flycatch_count);////
	this->setMicroelements(flycatch_microelements - 1);
	if (getHumidity() < 0 || getMicroelements() < 0)
		return new Earth_Cell();
	return this;
}