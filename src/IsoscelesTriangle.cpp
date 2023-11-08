#pragma once
#include <IsoscelesTriangle.h>
#include <cmath>

const int num1 = 20;
const int num2 = 25;
const int num3 = 30;

IsoscelesTriangle::IsoscelesTriangle(const Vertex vertices[3])
	:m_botLeft(vertices[0]),m_top(vertices[1]), m_botRight(vertices[2])

{	// check if the triangle is valid
	checkValid();
}

IsoscelesTriangle::IsoscelesTriangle(const Vertex& left, const Vertex& right, double height)
	:m_botLeft(left), m_botRight(right)

{	//find the vertex at the top with the height
	m_top.m_col = (m_botLeft.m_col + m_botRight.m_col) / 2;
	height > 0 ? m_top.m_row = m_botRight.m_row + height : m_top.m_row = m_botRight.m_row + height; 
	checkValid();

}




double IsoscelesTriangle::getBaseLength() const
{
	//return the x value from right less x value from the left 

	return m_botRight.m_col - m_botLeft.m_col;
}



Vertex IsoscelesTriangle::getVertex(int index) const
{
	//check the index and returns its the vertex
	if (index == 0)
		return m_botLeft;
	else if (index == 1)
		return m_top;
	else
		return m_botRight;
}

double IsoscelesTriangle::getHeight()const
{
	return m_top.m_row - m_botLeft.m_row > 0 ? m_top.m_row - m_botLeft.m_row : m_botLeft.m_row - m_top.m_row; 
}

double IsoscelesTriangle::getLegLength() const
{
	return sqrt(pow(m_botRight.m_col - m_top.m_col, 2) + pow(m_botRight.m_row - m_top.m_row, 2));
}


bool  IsoscelesTriangle::checkValid()
{
	if (!m_botLeft.isValid() || !m_botRight.isValid() || !m_top.isValid())
	{
		setsVertex();
		return false;
	}
	if (m_botRight.m_row != m_botLeft.m_row)
	{
		setsVertex();
		return false;
	}
	if (checkLegs()) // if legs not equal
	{
		setsVertex();
		return false;
	}
	return true;

}


void IsoscelesTriangle::setsVertex()
{	
	m_botRight.m_col = num3;
	m_botLeft.m_col = num1;
	m_botRight.m_row= m_botLeft.m_row = num1;
	m_top.m_col = m_top.m_row = num2;

 }

bool IsoscelesTriangle::checkLegs()
{
	if (doubleEqual(distance(m_botLeft,m_top) , distance(m_botRight,m_top)))
		return false;
	return true;
}




double IsoscelesTriangle::getPerimeter()const 
{
	return getBaseLength() + 2 * getLegLength();
}

void IsoscelesTriangle::draw(Board& board) const 
{
	board.drawLine(m_botLeft, m_botRight);
	board.drawLine(m_botLeft, m_top);
	board.drawLine(m_top, m_botRight);
}

double IsoscelesTriangle::getArea() const
{
	return (getBaseLength() * getHeight()) / 2;
}


Vertex IsoscelesTriangle::getCenter()const
{
	Vertex center;
	center.m_col = (m_top.m_col + m_botLeft.m_col + m_botRight.m_col) / 3;
	center.m_row = (m_top.m_row + m_botLeft.m_row + m_botRight.m_row) / 3;
	return center;
}

bool  IsoscelesTriangle::scale(double factor)
{
	if (factor < 0)
		return false;
	

	Vertex center = getCenter();

	Vertex oldTop = m_top;
	Vertex oldLeft = m_botLeft;
	Vertex oldRight = m_botRight;


	m_top.m_col = calculateVertex(factor, center.m_col, m_top.m_col);
	m_top.m_row = calculateVertex(factor, center.m_row, m_top.m_row);
	m_botLeft.m_col = calculateVertex(factor, center.m_col, m_botLeft.m_col);
	m_botLeft.m_row = calculateVertex(factor, center.m_row, m_botLeft.m_row);
	m_botRight.m_col = calculateVertex(factor, center.m_col, m_botRight.m_col);
	m_botRight.m_row = calculateVertex(factor, center.m_row, m_botRight.m_row);

	if (!checkValid())
	{
		m_top = oldTop;
		m_botLeft = oldLeft;
		m_botRight = oldRight;

	}

}


double  IsoscelesTriangle::calculateVertex(double factor, double center, double vertex)
{
	return center - ((center - vertex) * factor);
}

double IsoscelesTriangle::getDistance(const Vertex v1, const Vertex v2)
{
	return sqrt(pow(v1.m_col - v2.m_col, 2) + pow(v1.m_row - v2.m_row, 2));
}



Rectangle IsoscelesTriangle::getBoundingRectangle()const
{	
	Vertex topRight, botLeft;

	if (m_top.isHigherThan(m_botLeft))
	{
		botLeft = m_botLeft;
		topRight.m_col = m_botRight.m_col;
		topRight.m_row = m_top.m_row;

	}
	else 
	{
		topRight = m_botRight;
		botLeft.m_col = m_botLeft.m_col;
		botLeft.m_row = m_top.m_row;
	}
	

	Rectangle rectangle(botLeft,topRight );
	return rectangle;

}