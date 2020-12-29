#pragma once

#include "Lane.h"


class Road {
public:
	Road(size_t len, Direction relative_to_intersect);
	bool LinkExit(shared_ptr<Cell> entrance);
	shared_ptr<Cell>& LinkEntrance();
	bool InsertCar(Car c);
	void MoveCars();
	
	pair<vector<int>, vector<int>> Image();

private:
	int length;
	shared_ptr<Lane> out;
	shared_ptr<Lane> into;
};