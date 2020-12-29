#include "Lane.h"
#include "Cell.h"
#include <algorithm>

using namespace std;

Lane::Lane(size_t len, Direction d, bool stopline) : length(len), direction(d), has_stopline(stopline) {
	if (length < 2) {
		throw invalid_argument("Wrong len of lane");
	}
	cells.resize(length);
	for (auto& i : cells) {
		i = make_shared<Cell>();
	}
	cells[0] = shared_ptr<Entrance>(new Entrance(direction));
	if (has_stopline) {
		cells[length - 1] = shared_ptr<Stopline>(new Stopline());
	}
}

bool Lane::InsertCar(Car c) {
	return cells[0]->InsertCar(make_unique<Car>(move(c)));
}

void Lane::MoveCars() {
	int idx_last_obst = (cells[length - 1]->IsEmpty()) ? length : length - 1;
	idx_last_obst = has_stopline ? idx_last_obst : numeric_limits<int>::max();
	cells[length - 1]->ExtractCar(7);


	for (int i = length - 2; i >= 0; i--) {
		if (cells[i]->IsEmpty()) {
			continue;
		}
		unique_ptr<Car> temp = cells[i]->ExtractCar(idx_last_obst - i - 1);
		idx_last_obst = i;
		if (i + temp->Speed() >= length) {
			continue;
		}
		cells[i + temp->Speed()]->InsertCar(move(temp));

	}
}

bool Lane::Link(shared_ptr<Cell> entr) {
	if (linked) {
		return false;
	}
	if (cells[length - 1]->IsEmpty()) {
		has_stopline = true;
		cells[length - 1] = shared_ptr<Stopline>(new Stopline(entr));
		linked = true;
		return true;
	}
	return false;
}

shared_ptr<Cell>& Lane::GetEntrance() {
	return cells[0];
}

vector<int> Lane::StringImage() {
	vector<int> result;
	for (auto& i : cells) {
		result.push_back(i->IsEmpty());
	}
	return result;
}