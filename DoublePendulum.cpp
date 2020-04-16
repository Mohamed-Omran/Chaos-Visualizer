#include "DoublePendulum.h"

DoublePendulum::DoublePendulum(double m1, double m2, double l1, double l2, double theta1, double theta2,double omega1, double omega2, sf::Vector2f pos)
				:m1(m1), m2(m2), l1(l1), l2(l2), theta1(theta1), theta2(theta2),omega1(omega1), omega2(omega2), pos(pos)
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
	// defining some internal variables that won't make me write long lines.
	double I1_1 = -g * (2 * m1 + m2) * sin(theta1);
	double I1_2 = -m2 * g * sin(theta1 - 2 * theta2);
	double I1_3 = -2 * sin(theta1 - theta2) * m2 * (omega2 * omega2 * l2 + omega1 * omega1 * l1 * cos(theta1 - theta2));
	double I1_4 = l2 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2));

	double I2_1 = 2 * sin(theta1 - 2 * theta2);
	double I2_2 = (omega1 * omega1 * l1 * (m1 + m2))+g * (m1 + m2) * cos(theta1);
	double I2_3 = omega2 * omega2 * l2 * m2 * cos(theta1 -theta2);
	double I2_4 = l1 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2));

	// defining the angular acceleration for each mass acc1, acc2.
	
	double acc1 = (I1_1 + I1_2 + I1_3) / I1_4;
	double acc2 = I2_1 * (I2_2 + I2_3) / I2_4;


}
