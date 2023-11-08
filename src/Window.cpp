#pragma once 

#include <Window.h>

const Vertex leftBot  (20, 10);
const Vertex rightTop  (30, 20);
const Vertex the_Point  (25, 15);



Window::Window(const Rectangle& rectangle, const Vertex& point)
	: m_Point(point), m_Rec(rectangle)
{
	checkValid();
	setVertcies();
}



Window::Window(const Vertex& start, double width, double height, const Vertex& point)
	:Window(Rectangle(start, width, height), point)
{		
}


Vertex Window::getBottomLeft()const
{
	return m_Rec.getBottomLeft();

}

Vertex Window::getTopRight()const
{
	return m_Rec.getTopRight();
}

Vertex  Window::getPoint()const 
{
	return m_Point;
}


void Window::draw(Board& board) const
{
	m_Rec.draw(board);
	board.drawLine(m_Point, m_Down);
	board.drawLine(m_Point, m_Left);
	board.drawLine(m_Point, m_Right);
	board.drawLine(m_Point, m_Up);
}


double Window::getArea() const
{	
	return m_Rec.getArea();
}

Vertex Window::getCenter()const
{
	return m_Rec.getCenter();
}

double  Window::getPerimeter()const
{
	return m_Rec.getPerimeter();
}


bool Window::scale(double factor)
{
	
	if (!m_Rec.scale(factor))
		return false;
	Vertex center = m_Rec.getCenter();

	Vertex oldRight = m_Right, oldLeft = m_Left, oldUp= m_Up, oldDown= m_Down, oldp= m_Point;
	m_Right.m_col = calculateVertex(factor, center.m_col, m_Right.m_col);
	m_Right.m_row = calculateVertex(factor, center.m_row, m_Right.m_row);
	m_Left.m_col = calculateVertex(factor, center.m_col, m_Left.m_col);
	m_Left.m_row = calculateVertex(factor, center.m_row, m_Left.m_row);
	m_Up.m_col =  calculateVertex(factor, center.m_col, m_Up.m_col);
	m_Up.m_row = calculateVertex(factor, center.m_row, m_Up.m_row);
	m_Down.m_col= calculateVertex(factor, center.m_col, m_Down.m_col);
	m_Down.m_row = calculateVertex(factor, center.m_row, m_Down.m_row);
	

	m_Point.m_col = calculateVertex(factor, center.m_col, m_Point.m_col);
	m_Point.m_row = calculateVertex(factor, center.m_row, m_Point.m_row);




	if (!checkValid())
	{
		m_Right = oldRight;
		m_Left = oldLeft;
		m_Up = oldUp;
		m_Down = oldDown;
		m_Point = oldp;
		return false;
	}
	return true;

}


double Window::calculateVertex(double factor, double center, double vertex)
{
	return center - ((center - vertex) * factor);
}


Rectangle Window::getBoundingRectangle()const
{
	return m_Rec;
}



bool Window::checkValid()
{
	
	Vertex bLeft =m_Rec.getBottomLeft();
	Vertex tRight = m_Rec.getTopRight();

	if (m_Point.m_col > tRight.m_col || m_Point.m_col<bLeft.m_col || m_Point.m_row>tRight.m_row || m_Point.m_row < bLeft.m_row)
	{
		m_Point = the_Point;
		return false;
	}
	return true;
}



void Window::setVertcies()
{
	Vertex s = m_Rec.getBottomLeft();
	Vertex t = m_Rec.getTopRight();
	//left v:
	m_Left.m_col = s.m_col;
	m_Left.m_row = m_Point.m_row;
	//up v:
	m_Up.m_col = m_Point.m_col;
	m_Up.m_row = t.m_row;
	//right v:
	m_Right.m_col = t.m_col;
	m_Right.m_row = m_Point.m_row;
	//down v:
	m_Down.m_col = m_Point.m_col;
	m_Down.m_row = s.m_row;
}
