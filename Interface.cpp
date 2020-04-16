#include "Interface.h"

Interface::Interface() {
	window.create(sf::VideoMode(800, 600), "MOHAMED");
}

void Interface::clear() {
	window.clear();
}

void Interface::display() {
	window.display();
}

void Interface::drawDP(double m1, double m2, double l1, double l2, double theta1, double theta2, sf::Vector2f pos) {
}
