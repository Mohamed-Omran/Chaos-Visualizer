#include "Program.h"

Program::Program(): dp1(30.0, 15.0, 100.0, 150.0, pi/2.0, pi/2.0, 0, 0, 0.02, sf::Vector2f(400.0f, 300.0f))
				   ,dp2(30.0, 15.0, 100.0, 150.0, pi/2.0, pi/2.0, 0, 0, 0.02, sf::Vector2f(400.0f, 300.0f))
{}

void Program::simulate() {
	dp1.update_RK4();
	dp2.update_RK4();

}

void Program::updateInterface(){
	interface.control();
	interface.clear();
	dp1.draw(interface);
	dp2.draw(interface);
	interface.display();
}
