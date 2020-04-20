#include "Program.h"

Program::Program(): dp(20.0, 15.0, 100.0, 120.0, pi / 2, pi / 2, 0, 0, 0.1, sf::Vector2f(400.0f, 300.0f)) {
}

void Program::simulate() {
	dp.update_RK4();

}

void Program::updateInterface(){
	interface.control();
	interface.clear();
	dp.draw(interface);
	interface.display();
}
