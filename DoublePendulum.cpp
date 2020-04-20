#include "DoublePendulum.h"

DoublePendulum::DoublePendulum(double m1, double m2, double l1, double l2, double theta1, double theta2,double omega1, double omega2, double stepSize, sf::Vector2f pos)
				:m1(m1), m2(m2), l1(l1), l2(l2), theta1(theta1), theta2(theta2),omega1(omega1), omega2(omega2), stepSize(stepSize), pos(pos)
{

}

void DoublePendulum::setPosition(sf::Vector2f pos) {
	this->pos = pos;

}

void DoublePendulum::which_H(double h) {
    double conv = 3.14192 / 180.0;
    // defining some internal variables that won't make me write long lines.
	double I1_1 = -g * (2 * m1 + m2) * sin(theta1 +h*stepSize);
	double I1_2 = -m2 * g * sin((theta1 + h * stepSize) - 2 * theta2);
	double I1_3 = -2 * sin(theta1 + h * stepSize - theta2) * m2 * (omega2 * omega2 * l2 + omega1 * omega1 * l1 * cos(theta1 - theta2));
	double I1_4 = l2 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2));

	double I2_1 = 2 * sin(theta1 - 2 * theta2);
	double I2_2 = (omega1 * omega1 * l1 * (m1 + m2)) + g * (m1 + m2) * cos(theta1);
	double I2_3 = omega2 * omega2 * l2 * m2 * cos(theta1 - theta2);
	double I2_4 = l1 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2));
	
	// defining the angular acceleration for each mass acc1, acc2.

	acc1 = (I1_1 + I1_2 + I1_3) / I1_4;
	acc2 = I2_1 * (I2_2 + I2_3) / I2_4;

}
// this function needs a thorough look for potential optimization
void DoublePendulum::update_RK4() {
	//where the magig happens

    // Calculate Omega1

    double I0 = (-g * (2 * m1 + m2) * sin(theta1) - m2 * g * sin(theta1 - 2 * theta2) - 2 * sin(theta1 - theta2) * m2 * (pow(omega2, 2) * l2 + pow(omega1, 2) * l1 * cos(theta1 - theta2))) / (l1 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2)));
    
    double I1 = (-g * (2 * m1 + m2) * sin(theta1 + stepSize * 0.5 * I0) - m2 * g * sin(theta1 + stepSize * 0.5 * I0 - 2 * theta2) - 2 * sin(theta1 + stepSize * 0.5 * I0 - theta2) * m2 * (pow(omega2, 2) * l2 + pow(omega1, 2) * l1 * cos(theta1 + stepSize * 0.5 * I0 - theta2))) / (l1 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2)));

    double I2 = (-g * (2 * m1 + m2) * sin(theta1 + stepSize * 0.5 * l1) - m2 * g * sin(theta1 + stepSize * 0.5 * l1 - 2 * theta2) - 2 * sin(theta1 + stepSize * 0.5 * l1 - theta2) * m2 * (pow(omega2, 2) * l2 + pow(omega1, 2) * l1 * cos(theta1 + stepSize * 0.5 * l1 - theta2))) / (l1 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2)));

    double I3 = (-g * (2 * m1 + m2) * sin(theta1 + stepSize * I2) - m2 * g * sin(theta1 + stepSize * I2 - 2 * theta2) - 2 * sin(theta1 + stepSize * I2 - theta2) * m2 * (pow(omega2, 2) * l2 + pow(omega1, 2) * l1 * cos(theta1 + stepSize * I2 - theta2))) / (l1 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2)));

    double u2soln = omega1 + (stepSize / 6.0) * (I0 + 2 * I1 + 2 * I2 + I3);

    // Calculate theta1
    double k0 = omega1;
    double k1 = omega1 + stepSize * 0.5 * k0;
    double k2 = omega1 + stepSize * 0.5 * k1;
    double k3 = omega1 + stepSize * k2;
    double u1soln = theta1 + (stepSize / 6.0) * (k0 + 2 * k1 + 2 * k2 + k3);

    // Calculate omega2
    double t0 = (2 * sin(theta1 - theta2) * (pow(omega1, 2) * l1 * (m1 + m2) + g * (m1 + m2) * cos(theta1) + pow(omega2, 2) * l2 * m2 * cos(theta1 - theta2))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2)));

    double t1 = (2 * sin(theta1 - theta2 + stepSize * 0.5 * t0) * (pow(omega1, 2) * l1 * (m1 + m2) + g * (m1 + m2) * cos(theta1) + pow(omega2, 2) * l2 * m2 * cos(theta1 - theta2 + stepSize * 0.5 * t0))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2 + stepSize * 0.5 * t0)));

    double t2 = (2 * sin(theta1 - theta2 + stepSize * 0.5 * t1) * (pow(omega1, 2) * l1 * (m1 + m2) + g * (m1 + m2) * cos(theta1) + pow(omega2, 2) * l2 * m2 * cos(theta1 - theta2 + stepSize * 0.5 * t1))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2 + stepSize * 0.5 * t1)));

    double t3 = (2 * sin(theta1 - theta2 + stepSize * t2) * (pow(omega1, 2) * l1 * (m1 + m2) + g * (m1 + m2) * cos(theta1) + pow(omega2, 2) * l2 * m2 * cos(theta1 - theta2 + stepSize * t2))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2 + stepSize * t2)));

    double u4soln = omega2 + (stepSize / 6.0) * (t0 + 2 * t1 + 2 * t2 + t3);

    // Calculate theta2
    double w0 = omega2;
    double w1 = omega2 + stepSize * 0.5 * w0;
    double w2 = omega2 + stepSize * 0.5 * w1;
    double w3 = omega2 + stepSize * w2;
    double u3soln = theta2 + (stepSize / 6.0) * (w0 + 2 * w1 + 2 * w2 + w3);

    theta1 = u1soln;
    omega1 = u2soln;
    theta2 = u3soln;
    omega2 = u4soln;


}

void DoublePendulum::draw(Interface& interface) {
    interface.drawDP(m1, m2, l1, l2, theta1, theta2, pos);
	
}
