#pragma once
#include <ml5/ml5.h>

#include "laser.h"
#include "movingobject.h"

class spaceship: public movingobject
{
public:
	spaceship(wxPoint pos, int size)
		:movingobject(pos, size, "D:\\FH\\Semester 3\\SWO3_UE\\Uebung_15\\images\\spaceship.png")
	{
		
	}

	void shoot(const double rad)
	{
		laser l{ center, 20, 10, rad};
		shots.push_back(l);
	}

	std::vector<laser> getShots()
	{
		return shots;
	}

	void moveShots()
	{
		for (auto& laser : shots) {
			laser.move();
		}
	}

private:
	std::vector<laser> shots {};
};
