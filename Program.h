#pragma once
#include"DoublePendulum.h"

class Program {
private:
	Interface interface;
	DoublePendulum dp;
	sf::Vector2f pos;

public:
	Program();

	void simulate();

	void updateInterface();
};

