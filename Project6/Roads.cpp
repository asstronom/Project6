#include "Roads.h"



Road::Road(size_t len, Direction relative_to_intersect) : length(len),
	out(make_shared<Lane>(Lane{ len, relative_to_intersect, false })),
	into(make_shared<Lane>(Lane{ len, relative_to_intersect+2, true})) {
}

bool Road::LinkExit(shared_ptr<Cell> entrance) {
	return into->Link(entrance);
}

shared_ptr<Cell>& Road::LinkEntrance() {
	return out->GetEntrance();
}

bool Road::InsertCar(Car c) {
	return into->InsertCar(c);
}

void Road::MoveCars() {
	out->MoveCars();
	into->MoveCars();
}

pair<vector<int>, vector<int>> Road::Image() {
	return { out->StringImage(), into->StringImage() };
}