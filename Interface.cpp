#include "Interface.h"

Interface::Interface() {
	window.create(sf::VideoMode(800, 600), "MOHAMED");
}



void Interface:: control() {

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
}
void Interface::clear() {

	window.clear(sf::Color::Black);
}


void Interface::drawDP(double m1, double m2, double l1, double l2, double theta1, double theta2, sf::Vector2f pos) {

	double conv = 3.14192 / 180.0;
	sf::Vector2f center1 (pos.x + l1 * sin(theta1 ),(float) pos.y + l1 * cos(theta1 ) );
	sf::Vector2f center2 ( center1.x + l2 * sin(theta2 ), center1.y + l2 * cos(theta2));
	
	//cout << theta1 << "  " << theta2 << endl;
	 //cout << center1.x << "  " << center1.y << "  " << center2.x << "  " << center2.y << endl;
	

	sf::Vertex line1[] = { sf::Vertex(pos), sf::Vertex(center1) };

	window.draw(line1, 2, sf::Lines);


	sf::Vertex line2[] = { sf::Vertex(center1), sf::Vertex(center2) };

	window.draw(line2, 2, sf::Lines);
	 
	 // origin circle:
	sf::CircleShape origin(5.0);
	origin.setOrigin(5.0,5.0);
	origin.setPosition(pos);
	origin.setFillColor(sf::Color::Blue);
	window.draw(origin);

	// mass1 :
	sf::CircleShape mass1(10.0);
	mass1.setOrigin(10.0,10.0);
	mass1.setPosition(center1);
	mass1.setFillColor(sf::Color::Yellow);
	window.draw(mass1);


	sf::CircleShape mass2(10.0);
	mass2.setOrigin(10.0,10.0);
	mass2.setPosition(center2);
	mass2.setFillColor(sf::Color::Red);
	window.draw(mass2);
}

void Interface::display() {
	window.display();
}