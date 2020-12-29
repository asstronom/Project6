#pragma once


enum class Light {
	Red,
	Yellow,
	Green
};

class TrafficLight {
public:
	TrafficLight();
	TrafficLight(Light c_state);
	void Update_Cur_State(Light new_light);
	Light State();
private:
	Light cur_state;
};


class TrafficCounter {
public:
	TrafficCounter(size_t d, Light c_state, Light n_state);
	Light Count();
private:
	Light cur_state;
	Light next_state;
	size_t counter = 0;
	size_t delay;
};