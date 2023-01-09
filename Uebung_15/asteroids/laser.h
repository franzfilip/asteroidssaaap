#pragma once
#include <ml5/ml5.h>
#include "movingobject.h"

class laser : public movingobject {
public:
	laser(wxPoint pos, int size, int s, double r)
		:movingobject(pos, size, "D:\\FH\\Semester 3\\SWO3_UE\\Uebung_15\\images\\laser.png"), rad{r}
	{
		speed = s;
	}

	laser(const laser& l)
		:movingobject(l)
	{
		
	}

	void move()
	{
		const int dx = sin(rad) * speed;
		const int dy = cos(rad) * speed;
		wxPoint p(dx, dy);
		position += p;
		boundingBox = wxRect(position.x, position.y, size, size);
		center = wxPoint(boundingBox.GetTopLeft().x + image.GetWidth() / 2, boundingBox.GetTopLeft().y + image.GetHeight() / 2);
	}
private:
	double rad{ 0 };
};
