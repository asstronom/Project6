#include "car.h"
#include "Lane.h"
#include "Intersection.h"

#include <iostream>

#include <stdlib.h>
#include <ctime>

using namespace std;





int main() {
	Intersection inter(TrafficCounter(3, Light::Red, Light::Green), 5);
	inter.InsertCar({ 1, 1, 1, Turn::Straight}, Direction::Down);
	inter.InsertCar({ 1, 1, 1, Turn::Left }, Direction::Right);
	inter.InsertCar({ 1, 1, 2, Turn::Right }, Direction::Up);
	while (true) {
		inter.MoveCarsOnIntersect();
		inter.MoveCarsOnRoads();
	}
	cout << "Sexxy";
}


