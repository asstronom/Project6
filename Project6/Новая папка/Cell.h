#pragma once
#include "car.h"
#include "Traffic_Light.h"

#include <iostream>



class Cell {
public:
	virtual bool InsertCar(std::unique_ptr<Car> c);
	virtual std::unique_ptr<Car> ExtractCar(int dist_to_obstacle);
	virtual bool IsEmpty();
	virtual int CallNextSpeed(int dist_to_obstacle);
	virtual pair<Direction, Turn> GetTurnAndDir();
protected:
	std::unique_ptr<Car> car;
};

class Entrance : public Cell {
public:
	Entrance(Direction d);
	virtual Direction GetDirection() const;
	virtual bool InsertCar(std::unique_ptr<Car> c) override;
protected:
	Direction direction;
};



//class Exit : public Cell {
//public:
//	virtual std::unique_ptr<Car> ExtractCar() override;
//	virtual bool CanExtract() override;
//protected:
//
//};


class Stopline : public Cell {
public:
	virtual std::unique_ptr<Car> ExtractCar(int dist_to_obstacle) override;
	Stopline();
	Stopline(shared_ptr<Cell> c);
private:
	std::shared_ptr<Cell> entrance;
	TrafficLight traffic;
};
