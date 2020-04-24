#pragma once
#include"DoublePendulum.h"

class Program {
private:
	Interface interface;
	DoublePendulum dp1,dp2;
	sf::Vector2f pos;

public:
	Program();

	void simulate();

	void updateInterface();
};

