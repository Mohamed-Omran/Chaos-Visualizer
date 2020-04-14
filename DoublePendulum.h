#pragma once

#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"

using namespace std;

class DoublePendulum {
private:
	double m1, m2, l1, l2, theta1, theta2, g=9.81;  // the main characterstics and initial conditions for the angles.
	sf::Window window;
	sf::Vector2f pos;
public:
	// initializing the characteristics of the system. 
	DoublePendulum(double m1 , double m2 , double l1 , double l2, double theta1, double theta2, sf::Vector2f pos);

	//  sets the position of the pivot point on canvas
	void setPosition(sf::Vector2f pos );

	// calculates the pendulum's next position based 4th Runge-Kutta method.
	void update_RK4();

	// you guessed it!
	void draw();
};