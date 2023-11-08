#pragma once


#include <Vertex.h>
#include <Board.h>
#include <Rectangle.h>



class Window {
public:
	Window(const Rectangle& rectangle, const Vertex& point);
	Window(const Vertex& start, double width, double height, const Vertex& point);


	Vertex getBottomLeft()const;
	Vertex getTopRight()const;
	Vertex getPoint()const;




	void draw(Board& board) const;
	double getArea() const;
	Vertex getCenter()const;
	double getPerimeter()const;
	bool scale(double factor);
	Rectangle getBoundingRectangle()const;


private:

	Rectangle m_Rec;
	Vertex m_Point;

	Vertex m_Right, m_Left, m_Up, m_Down;


	bool checkValid();
	void setVertcies();

	double calculateVertex(double factor, double distance, double point);

};

