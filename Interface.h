#pragma once

#include<iostream>
#include <cmath>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"

using namespace std;

class Interface {
private:
	sf::RenderWindow window;
	

public:
	// setting up the program window
	Interface();

	// Clears the frame (first step in rendering a new frame)
	void clear();


	void control();
	// Displays the frame (last step in rendering a new frame)
	void display();

	// draws a double Pendulum
	void drawDP(double m1, double m2, double l1, double l2, double theta1, double theta2, sf::Vector2f pos);


};

