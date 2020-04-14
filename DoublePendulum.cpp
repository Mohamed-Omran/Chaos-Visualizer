#include "DoublePendulum.h"

DoublePendulum::DoublePendulum(double m1, double m2, double l1, double l2, double theta1, double theta2, sf::Vector2f pos)
				:m1(m1), m2(m2), l1(l1), l2(l2), theta1(theta1), theta2(theta2), pos(pos)
{
	window.create(sf::VideoMode(800, 600), "MOHAMED");
}

void DoublePendulum::setPosition(sf::Vector2f pos) {
	this->pos = pos;

}

void DoublePendulum::update_RK4() {
	//where the magig happens
}

void DoublePendulum::draw() {

}
