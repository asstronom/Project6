#pragma once


using namespace std;

enum class Direction {
	Up,
	Left,
	Down,
	Right,
};

enum class Turn {
	Straight,
	Right,
	Left,
};

Direction operator+(Direction d, int i);

Direction operator+(Direction d, Turn t);

class Car {
public:
	Car(int sp, int max_sp, int chance, Turn t);
	int Next_Speed(int dist_to_obstacle);
	void ChangeDirection(Direction direction);
	int Speed();
	void TurnCar();
	Direction GetDirection();
	Turn GetTurn();
	//~Car();
private:
	int speed;
	int max_speed;
	int p;
	Direction dir;
	Turn turn;

	void Gas();
	void Avoid_Crash_Speed(int dist_to_obstacle);
	void RandomizeSpeed();
};