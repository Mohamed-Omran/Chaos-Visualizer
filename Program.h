#pragma once
#include"DoublePendulum.h"

class Program {
private:
	Interface interface;
	DoublePendulum dp;

public:
	Program();

	void simulate();

	void updateInterface();
};

