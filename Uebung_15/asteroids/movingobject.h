#pragma once
#include <ml5/ml5.h>

class movingobject : ml5::object {
public:
	movingobject(wxPoint pos, int size, std::string filelocation) : position{ pos }, size{ size }
	{
		wxImage::AddHandler(new wxPNGHandler);
		image.LoadFile(wxT("" + filelocation), wxBITMAP_TYPE_PNG);
		image.Rescale(size, size);
		boundingBox = wxRect(pos.x, pos.y, size, size);
		center = wxPoint(boundingBox.GetTopLeft().x + image.GetWidth() / 2, boundingBox.GetTopLeft().y + image.GetHeight() / 2);
	}

	movingobject(const movingobject& mo): position{mo.position}, size{mo.size}, image{mo.image}, center{mo.center}, speed{mo.speed}, boundingBox{mo.boundingBox}
	{
		
	}

	movingobject()
	{
		
	}

	wxImage getImage() {
		return image;
	}

	wxPoint getPosition() {
		return position;
	}

	void setPosition(wxPoint pos) {
		position = pos;
	}

	wxRect getBoundingBox() {
		return boundingBox;
	}

	wxRect setBoundingBox(wxRect rect) {
		boundingBox = rect;
	}

	wxPoint getCenter() {
		return center;
	}

	wxImage rotateImage(const double rad) {
		center = wxPoint(boundingBox.GetTopLeft().x + image.GetWidth() / 2, boundingBox.GetTopLeft().y + image.GetHeight() / 2);
		wxImage i = image.Rotate(rad, center);
		return i;
	}

	void increaseSpeed(int s) {
		speed += s;
	}

	void reduceSpeed(int s) {
		if (speed - s >= 0) {
			speed -= s;
		}
	}

	void move(const double rad) {
		const int dx = sin(rad) * speed;
		const int dy = cos(rad) * speed;
		wxPoint p(dx, dy);
		position += p;
		boundingBox = wxRect(position.x, position.y, size, size);
		center = wxPoint(boundingBox.GetTopLeft().x + image.GetWidth() / 2, boundingBox.GetTopLeft().y + image.GetHeight() / 2);
	}
//private:
protected:
	wxImage image{};
	wxPoint position{};
	wxRect boundingBox{};
	const int size = 200;
	int speed{ 0 };
	wxPoint center{};

//private:
//	wxImage image{};
//	wxPoint position{};
//	wxRect boundingBox{};
//	const int size = 200;
//	int speed{ 0 };
//protected:
//	wxPoint center{};
};