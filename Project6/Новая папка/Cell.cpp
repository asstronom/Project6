#include "Cell.h"
#include "car.h"

using namespace std;

bool Cell::InsertCar(unique_ptr<Car> c) {
	if (car == nullptr) {
		car = move(c);
		return true;
	}
	else {
		return false;
	}
}

bool Cell::IsEmpty() {
	return car == nullptr;
}

unique_ptr<Car> Cell::ExtractCar(int dist_to_obstacle) {
	if (car == nullptr) {
		return nullptr;
	}
	car->Next_Speed(dist_to_obstacle);
	return move(car);
}

int Cell::CallNextSpeed(int dist_to_obstacle) {
	return car->Next_Speed(dist_to_obstacle);
}

pair<Direction, Turn> Cell::GetTurnAndDir() {
	if (car == nullptr) {
		return { Direction::Left, Turn::Right };
	}
	return {car->GetDirection(), car->GetTurn()};
}


Entrance::Entrance(Direction d) : direction(d) {
}

Direction Entrance::GetDirection() const {
	return direction;
}

bool Entrance::InsertCar(std::unique_ptr<Car> c) {
	if (car == nullptr) {
		c->ChangeDirection(direction);
		car = move(c);
		return true;
	}
	else {
		return false;
	}
}

//unique_ptr<Car> Exit::ExtractCar() {
//	if (entrance == nullptr) {
//		car.reset();
//		cerr << "Extracted";
//	}
//	else if (entrance->IsEmpty()) {
//		entrance->InsertCar(move(car));
//		return nullptr;
//	}
//	return move(car);
//}

unique_ptr<Car> Stopline::ExtractCar(int dist_to_obstacle) {
	if (car == nullptr) {
		return nullptr;
	}
	if (entrance == nullptr) {
		car.reset();
	}
	else if (entrance->IsEmpty() && traffic.State() == Light::Green) {
		car->Next_Speed(1);
		entrance->InsertCar(move(car));
		
	}
	return nullptr;
}

Stopline::Stopline(shared_ptr<Cell> c) {
	entrance = c;
}

Stopline::Stopline(){}