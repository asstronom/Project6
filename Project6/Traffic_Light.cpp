#include "Traffic_Light.h"
#include <algorithm>

TrafficLight::TrafficLight() : cur_state(Light::Green){}

TrafficLight::TrafficLight(Light c_state) : cur_state(c_state) {
}

void TrafficLight::Update_Cur_State(Light new_light) {
	cur_state = new_light;
}

Light TrafficLight::State() {
	return cur_state;
}

TrafficCounter::TrafficCounter(size_t d, Light c_state, Light n_state) : delay(d), cur_state(c_state), next_state(n_state) {
}

Light TrafficCounter::Count() {
	if (counter == delay - 1) {
		counter++;
		return Light::Yellow;
	}
	if (counter == delay) {
		std::swap(cur_state, next_state);
		counter = 0;
	}
	counter++;
	return cur_state;
}
