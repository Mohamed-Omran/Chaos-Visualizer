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

    // potential energy
    double potential = -(m1 + m2) * g * l1 * cos(theta1) - m2 * g * l2 * cos(theta2);

    // Kinetic energy 
    double kinetic = 0.5 * m1 * l1 * l1 * omega1 * omega1 + 0.5 * m2 * ((l1 * l1 * omega1 * omega1) + (l2 * l2 * omega2 * omega2) + 2 * l1 * l2 * omega1 * omega2 * cos(theta1 - theta2));

    //displaying the kinetic, potential and total energy of the system.
    cout << kinetic << "  " << potential << "  " << kinetic + potential << endl;
    /////////////////////////////////////////////////////////////////////////////////////////////////

    // THE NEXT 16 VARIABLES ARE THE k's of Runge-Kutta for the 4 ODEs
    // All K1
    double dTheta1_1 = omega1;
    double dOmega1_1 = (-g * (2 * m1 + m2) * sin(theta1) - m2 * g * sin(theta1 - 2 * theta2) - 2 * sin(theta1 - theta2) * m2 * (pow(omega2, 2) * l2 + pow(omega1, 2) * l1 * cos(theta1 - theta2))) / (l1 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2)));
    double dTheta2_1 = omega2;
    double dOmega2_1 = (2 * sin(theta1 - theta2) * (pow(omega1, 2) * l1 * (m1 + m2) + g * (m1 + m2) * cos(theta1) + pow(omega2, 2) * l2 * m2 * cos(theta1 - theta2))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2)));

    // All K2
    double dTheta1_2 = omega1 + 0.5 * stepSize * dTheta1_1;
    double dOmega1_2 = (-g * (2 * m1 + m2) * sin(theta1 + 0.5 * stepSize * dTheta1_1) - m2 * g * sin((theta1 + 0.5 * stepSize * dTheta1_1) - 2 * (theta2 + 0.5 * stepSize * dTheta2_1)) - 2 * sin((theta1 + 0.5 * stepSize * dTheta1_1) - (theta2 + 0.5 * stepSize * dTheta2_1)) * m2 * (pow(omega2 + 0.5 * stepSize * dOmega2_1, 2) * l2 + pow(omega1 + 0.5 * stepSize * dOmega1_1, 2) * l1 * cos((theta1 + 0.5 * stepSize * dTheta1_1) - (theta2 + 0.5 * stepSize * dTheta2_1)))) / (l1 * (2 * m1 + m2 - m2 * cos(2 * (theta1 + 0.5 * stepSize * dTheta1_1) - 2 * (theta2 + 0.5 * stepSize * dTheta2_1))));
    double dTheta2_2 = omega2 + 0.5 * stepSize * dTheta2_1;
    double dOmega2_2 = (2 * sin((theta1 + 0.5 * stepSize * dTheta1_1) - (theta2 + 0.5 * stepSize * dTheta2_1)) * (pow(omega1 + 0.5 * stepSize * dOmega1_1, 2) * l1 * (m1 + m2) + g * (m1 + m2) * cos(theta1 + 0.5 * stepSize * dTheta1_1) + pow(omega2 + 0.5 * stepSize * dOmega2_1, 2) * l2 * m2 * cos((theta1 + 0.5 * stepSize * dTheta1_1) - (theta2 + 0.5 * stepSize * dTheta2_1)))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * (theta1 + 0.5 * stepSize * dTheta1_1) - 2 * (theta2 + 0.5 * stepSize * dTheta2_1))));

    // All K3
    double dTheta1_3 = omega1 + 0.5 * stepSize * dTheta1_2;
    double dOmega1_3 = (-g * (2 * m1 + m2) * sin(theta1 + 0.5 * stepSize * dTheta1_2) - m2 * g * sin((theta1 + 0.5 * stepSize * dTheta1_2) - 2 * (theta2 + 0.5 * stepSize * dTheta2_2)) - 2 * sin((theta1 + 0.5 * stepSize * dTheta1_2) - (theta2 + 0.5 * stepSize * dTheta2_2)) * m2 * (pow(omega2 + 0.5 * stepSize * dOmega2_2, 2) * l2 + pow(omega1 + 0.5 * stepSize * dOmega1_2, 2) * l1 * cos((theta1 + 0.5 * stepSize * dTheta1_2) - (theta2 + 0.5 * stepSize * dTheta2_2)))) / (l1 * (2 * m1 + m2 - m2 * cos(2 * (theta1 + 0.5 * stepSize * dTheta1_2) - 2 * (theta2 + 0.5 * stepSize * dTheta2_2))));
    double dTheta2_3 = omega2 + 0.5 * stepSize * dTheta2_2;
    double dOmega2_3 = (2 * sin((theta1 + 0.5 * stepSize * dTheta1_2) - (theta2 + 0.5 * stepSize * dTheta2_2)) * (pow(omega1 + 0.5 * stepSize * dOmega1_2, 2) * l1 * (m1 + m2) + g * (m1 + m2) * cos(theta1 + 0.5 * stepSize * dTheta1_2) + pow(omega2 + 0.5 * stepSize * dOmega2_2, 2) * l2 * m2 * cos((theta1 + 0.5 * stepSize * dTheta1_2) - (theta2 + 0.5 * stepSize * dTheta2_2)))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * (theta1 + 0.5 * stepSize * dTheta1_2) - 2 * (theta2 + 0.5 * stepSize * dTheta2_2))));

    // All K4
    double dTheta1_4 = omega1 + stepSize * dTheta1_3;
    double dOmega1_4 = (-g * (2 * m1 + m2) * sin(theta1 + stepSize * dTheta1_3) - m2 * g * sin((theta1 + stepSize * dTheta1_3) - 2 * (theta2 + stepSize * dTheta2_3)) - 2 * sin((theta1 + stepSize * dTheta1_3) - (theta2 + stepSize * dTheta2_3)) * m2 * (pow(omega2 + stepSize * dOmega2_3, 2) * l2 + pow(omega1 + stepSize * dOmega1_3, 2) * l1 * cos((theta1 + stepSize * dTheta1_3) - (theta2 + stepSize * dTheta2_3)))) / (l1 * (2 * m1 + m2 - m2 * cos(2 * (theta1 + stepSize * dTheta1_3) - 2 * (theta2 + stepSize * dTheta2_3))));
    double dTheta2_4 = omega2 + stepSize * dTheta2_3;
    double dOmega2_4 = (2 * sin((theta1 + stepSize * dTheta1_3) - (theta2 + stepSize * dTheta2_3)) * (pow(omega1 + stepSize * dOmega1_3, 2) * l1 * (m1 + m2) + g * (m1 + m2) * cos(theta1 + stepSize * dTheta1_3) + pow(omega2 + stepSize * dOmega2_3, 2) * l2 * m2 * cos((theta1 + stepSize * dTheta1_3) - (theta2 + stepSize * dTheta2_3)))) / (l2 * (2 * m1 + m2 - m2 * cos(2 * (theta1 + stepSize * dTheta1_3) - 2 * (theta2 + stepSize * dTheta2_3))));


    double theta1New = theta1 + (stepSize / 6.0) * (dTheta1_1 + 2 * dTheta1_2 + 2 * dTheta1_3 + dTheta1_4);
    double omega1New = omega1 + (stepSize / 6.0) * (dOmega1_1 + 2 * dOmega1_2 + 2 * dOmega1_3 + dOmega1_4);
    double theta2New = theta2 + (stepSize / 6.0) * (dTheta2_1 + 2 * dTheta2_2 + 2 * dTheta2_3 + dTheta2_4);
    double omega2New = omega2 + (stepSize / 6.0) * (dOmega2_1 + 2 * dOmega2_2 + 2 * dOmega2_3 + dOmega2_4);


    // updating variables 
    theta1 = theta1New;
    omega1 = omega1New;
    theta2 = theta2New;
    omega2 = omega2New;


}
void DoublePendulum::draw(Interface& interface) {
    interface.drawDP(m1, m2, l1, l2, theta1, theta2, pos);
	
}
