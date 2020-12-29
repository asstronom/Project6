#pragma once
#include "car.h"
#include "Cell.h"

#include <vector>


using namespace std;


class Lane {
public:
	Lane(size_t len, Direction d, bool stopline);
	bool InsertCar(Car c);
	void MoveCars();
	bool Link(shared_ptr<Cell> entr);
	shared_ptr<Cell>& GetEntrance();
	vector<int> StringImage();


private:
	bool linked = false;
	Direction direction;
	size_t length;
	bool has_stopline;
	std::vector<std::shared_ptr<Cell>> cells;
};