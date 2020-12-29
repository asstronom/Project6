#include "car.h"

#include <stdlib.h>
#include <ctime>
#include <stdexcept>
#include <iostream>

using namespace std;

Direction operator+(Direction d, int i) {
	int temp = static_cast<int>(d);
	return static_cast<Direction>((temp + i) % 4);
}

Direction operator+(Direction d, Turn t) {
	return d + static_cast<int>(t);
}

Car::Car(int sp, int max_sp, int chance, Turn t) : speed(sp), max_speed(max_sp), p(chance), turn(t) {
	if (p < 1 || p > 100) {
		throw invalid_argument("Incorrect chance for the car");
	}
	if (speed > max_speed || speed < 0 || max_speed < 0) {
		throw invalid_argument("Incorrect speed for the car");
	}

}

void Car::Gas() {
	speed++;
	if (speed > max_speed) {
		speed = max_speed;
	}
}

void Car::Avoid_Crash_Speed(int dist_to_obstacle) {
	if (speed > dist_to_obstacle) {
		speed = dist_to_obstacle;
	}
}

void Car::RandomizeSpeed() {
	if (speed < 1) {
		return;
	}
	int randomNumber = (rand() % 100) + 1;
	if (randomNumber <= p) {
		speed--;
	}
}


int Car::Next_Speed(int dist_to_obstacle) {
	//Step 1: acceleration
	this->Gas();
	//Step 2: deceleration
	this->Avoid_Crash_Speed(dist_to_obstacle);
	//Step 3: randomization
	this->RandomizeSpeed();
	return speed;
}

void Car::ChangeDirection(Direction direction) {
	dir = direction;
}

int Car::Speed() {
	return speed;
}

//Car::~Car() {
//	cerr << endl << "Car Extracted, direction: " << static_cast<int>(dir) << " speed: " << speed << endl;
//}

void Car::TurnCar() {
	dir = dir + turn;
	turn = Turn::Straight;
}

Turn Car::GetTurn() {
	return turn;
}

Direction Car::GetDirection() {
	return dir;
}
