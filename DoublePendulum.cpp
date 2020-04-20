#include "DoublePendulum.h"

DoublePendulum::DoublePendulum(double m1, double m2, double l1, double l2, double theta1, double theta2,double omega1, double omega2, double stepSize, sf::Vector2f pos)
				:m1(m1), m2(m2), l1(l1), l2(l2), theta1(theta1), theta2(theta2),omega1(omega1), omega2(omega2), stepSize(stepSize), pos(pos)
{

}

void DoublePendulum::setPosition(sf::Vector2f pos) {
	this->pos = pos;

}


// this function needs a thorough look for potential optimization
void DoublePendulum::update_RK4() {
	//where the magig happens

    // Calculate Omega1

    double I0 = (-g * (2 * m1 + m2) * sin(theta1) - m2 * g * sin(theta1 - 2 * theta2) - 2 * sin(theta1 - theta2) * m2 * (pow(omega2, 2) * l2 + pow(omega1, 2) * l1 * cos(theta1 - theta2))) / (l1 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2)));
    
    double I1 = (-g * (2 * m1 + m2) * sin(theta1 + stepSize * 0.5 * I0) - m2 * g * sin(theta1 + stepSize * 0.5 * I0 - 2 * theta2) - 2 * sin(theta1 + stepSize * 0.5 * I0 - theta2) * m2 * (pow(omega2, 2) * l2 + pow(omega1, 2) * l1 * cos(theta1 + stepSize * 0.5 * I0 - theta2))) / (l1 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2)));

    double I2 = (-g * (2 * m1 + m2) * sin(theta1 + stepSize * 0.5 * l1) - m2 * g * sin(theta1 + stepSize * 0.5 * l1 - 2 * theta2) - 2 * sin(theta1 + stepSize * 0.5 * l1 - theta2) * m2 * (pow(omega2, 2) * l2 + pow(omega1, 2) * l1 * cos(theta1 + stepSize * 0.5 * l1 - theta2))) / (l1 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2)));

    double I3 = (-g * (2 * m1 + m2) * sin(theta1 + stepSize * I2) - m2 * g * sin(theta1 + stepSize * I2 - 2 * theta2) - 2 * sin(theta1 + stepSize * I2 - theta2) * m2 * (pow(omega2, 2) * l2 + pow(omega1, 2) * l1 * cos(theta1 + stepSize * I2 - theta2))) / (l1 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2)));

    double omega1New = omega1 + (stepSize / 6.0) * (I0 + 2 * I1 + 2 * I2 + I3);

    // Calculate theta1
    double k0 = omega1;
    double k1 = omega1 + stepSize * 0.5 * k0;
    double k2 = omega1 + stepSize * 0.5 * k1;
    double k3 = omega1 + stepSize * k2;
    double theta1New = theta1 + (stepSize / 6.0) * (k0 + 2 * k1 + 2 * k2 + k3);

    // Calculate omega2
    double t0 = (2 * sin(theta1 - theta2) * (pow(omega1, 2) * l1 * (m1 + m2) + g * (m1 + m2) * cos(theta1) + pow(omega2, 2) * l2 * m2 * cos(theta1 - theta2))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2)));

    double t1 = (2 * sin(theta1 - theta2 + stepSize * 0.5 * t0) * (pow(omega1, 2) * l1 * (m1 + m2) + g * (m1 + m2) * cos(theta1) + pow(omega2, 2) * l2 * m2 * cos(theta1 - theta2 + stepSize * 0.5 * t0))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2 + stepSize * 0.5 * t0)));

    double t2 = (2 * sin(theta1 - theta2 + stepSize * 0.5 * t1) * (pow(omega1, 2) * l1 * (m1 + m2) + g * (m1 + m2) * cos(theta1) + pow(omega2, 2) * l2 * m2 * cos(theta1 - theta2 + stepSize * 0.5 * t1))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2 + stepSize * 0.5 * t1)));

    double t3 = (2 * sin(theta1 - theta2 + stepSize * t2) * (pow(omega1, 2) * l1 * (m1 + m2) + g * (m1 + m2) * cos(theta1) + pow(omega2, 2) * l2 * m2 * cos(theta1 - theta2 + stepSize * t2))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2 + stepSize * t2)));

    double omega2New = omega2 + (stepSize / 6.0) * (t0 + 2 * t1 + 2 * t2 + t3);

    // Calculate theta2
    double w0 = omega2;
    double w1 = omega2 + stepSize * 0.5 * w0;
    double w2 = omega2 + stepSize * 0.5 * w1;
    double w3 = omega2 + stepSize * w2;
    double theta2New = theta2 + (stepSize / 6.0) * (w0 + 2 * w1 + 2 * w2 + w3);

    theta1 = theta1New;
    omega1 = omega1New;
    theta2 = theta2New;
    omega2 = omega2New;


}

void DoublePendulum::draw(Interface& interface) {
    interface.drawDP(m1, m2, l1, l2, theta1, theta2, pos);
	
}
