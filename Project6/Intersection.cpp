#include "Intersection.h"

bool operator==(Coord l, Coord r) {
	return (l.x == r.x) && (l.y == r.y);
}

Intersection::Intersection(TrafficCounter tr, size_t len) : traff(tr), length(len), routes(InitRoutes()) {
	for (int i = 0; i < 4; i++) {
		roads[static_cast<Direction>(i)] = shared_ptr<Road>(new Road(length, static_cast<Direction>(i)));
	}

	intersection.resize(2);
	for (int i = 0; i < 2; i++) {
		intersection[i].resize(2);
		for (int j = 0; j < 2; j++) {
			intersection[i][j] = shared_ptr<Cell>(new Cell());
		}
	}

	for (int i = 0; i < 4; i++) {
		entrances[static_cast<Direction>(i)] = shared_ptr<Entrance>(new Entrance(static_cast<Direction>(i) + 2));
		roads[static_cast<Direction>(i)]->LinkExit(entrances[static_cast<Direction>(i)]);
	}

	for (int i = 0; i < 4; i++) {
		exits[static_cast<Direction>(i)]
			= shared_ptr<Stopline>(new Stopline(roads[static_cast<Direction>(i)]->LinkEntrance()));
	}
}

bool Intersection::InsertCar(Car c, Direction relative_to_intersect) {
	return roads[relative_to_intersect]->InsertCar(c);
}

void Intersection::MoveCarsOnRoads() {
	for (auto& i : roads) {
		i.second->MoveCars();
	}
}

map<Direction, map<Turn, vector<Coord>>> Intersection::InitRoutes() {
	map<Direction, map<Turn, vector<Coord>>> result;
	result[Direction::Up][Turn::Right] = { {1,1} };
	result[Direction::Up][Turn::Straight] = { {1,1}, {0, 1} };
	result[Direction::Up][Turn::Left] = { {1,1}, {0, 1} };

	result[Direction::Right][Turn::Right] = { {1,0} };
	result[Direction::Right][Turn::Straight] = { {1,0}, {1, 1} };
	result[Direction::Right][Turn::Left] = { {1,0}, {1, 1} };

	result[Direction::Left][Turn::Right] = { {0,1} };
	result[Direction::Left][Turn::Straight] = { {0,1}, {0, 0} };
	result[Direction::Left][Turn::Left] = { {0,1}, {0, 0} };

	result[Direction::Down][Turn::Right] = { {0,0} };
	result[Direction::Down][Turn::Straight] = { {0,0}, {1, 0} };
	result[Direction::Down][Turn::Left] = { {0,0}, {1, 0} };

	return result;

};


void Intersection::MoveCarsOnIntersect() {

	for (auto& i : exits) {
		i.second->ExtractCar(7);
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			if (intersection[i][j]->IsEmpty()) continue;

			int dist_to_obstacle = 0;
			pair<Direction, Turn> car_info = intersection[i][j]->GetTurnAndDir();
			vector<Coord>& route = routes[car_info.first][car_info.second];

			if (route[0] == Coord{ i, j }) {

				if (route.size() == 1) {
					if (entrances[car_info.first]->IsEmpty()) {
						dist_to_obstacle++;
						unique_ptr<Car> temp =
							intersection[i][j]->ExtractCar(dist_to_obstacle);
						temp->TurnCar();
						exits[car_info.first]->InsertCar(move(temp));
					}
				}

				else if (intersection[route[1].x][route[1].y]->IsEmpty()
					&& entrances[car_info.first + 3]->IsEmpty()) {

					dist_to_obstacle++;

					if (car_info.second == Turn::Straight && exits[car_info.first]->IsEmpty()) {
						dist_to_obstacle++;
						unique_ptr<Car> temp =
							intersection[i][j]->ExtractCar(dist_to_obstacle);
						temp->TurnCar();
						exits[car_info.first]->InsertCar(move(temp));
					}
					else {
						unique_ptr<Car> temp =
							intersection[i][j]->ExtractCar(dist_to_obstacle);
						temp->TurnCar();
						intersection[route[1].x][route[1].y]->InsertCar(move(temp));
					}
				}
			}
		}
	}



	for (int i = 0; i < 4; i++) {
		if (entrances[static_cast<Direction>(i)]->IsEmpty()) continue;
		int dist_to_obstacle = 0;
		pair<Direction, Turn> car_info = entrances[static_cast<Direction>(i)]->GetTurnAndDir();
		vector<Coord>& route = routes[car_info.first][car_info.second];
		if (intersection[route[0].x][route[0].y]->IsEmpty()) {
			dist_to_obstacle++;

			if (car_info.second == Turn::Right) {
			}

			else {
				if (intersection[route[1].x][route[1].y]->IsEmpty()
					&& entrances[car_info.first + 3]->IsEmpty()) {
					dist_to_obstacle++;
				}
			}




			unique_ptr<Car> temp =
				entrances[static_cast<Direction>(i)]->ExtractCar(dist_to_obstacle);
			temp->TurnCar();
			intersection[route[dist_to_obstacle - 1].x][route[dist_to_obstacle - 1].y]
				->InsertCar(move(temp));
		}
	}



}


string Intersection::Image() {
	auto uproad = roads[Direction::Up]->Image();
	string result = "";
	for (int j = 0; j < length; j++) {
		for (int i = 0; i < length + 1; i++) {
			result += "/";
		}
		result += uproad.second[j]; +uproad.first[j];
	}
	return result;
}