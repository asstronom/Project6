#pragma once

#include "Traffic_Light.h"
#include "Lane.h"
#include "Roads.h"
#include "car.h"

#include <map>

struct Coord {
	int x;
	int y;
};

bool operator==(Coord l, Coord r);



class Intersection {
public:
	Intersection(TrafficCounter tr, size_t len);
	bool InsertCar(Car c, Direction relative_to_intersect);
	void MoveCarsOnIntersect();
	void MoveCarsOnRoads();
	string Image();

private:
	map<Direction, map<Turn, vector<Coord>>> InitRoutes();


	size_t length;
	TrafficCounter traff;
	map<Direction, shared_ptr<Road>> roads;
	vector<vector<shared_ptr<Cell>>> intersection;
	map<Direction, shared_ptr<Cell>> entrances;
	map<Direction, shared_ptr<Cell>> exits;
	map<Direction, map<Turn, vector<Coord>>> routes;
};


