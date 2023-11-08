#pragma once
#include <Rectangle.h>

const int num1 = 10;
const int num2 = 20;
const int num3 = 30;


Rectangle::Rectangle(const Vertex& BottonLeft, const Vertex& TopRight)
		:m_BotLeft(BottonLeft), m_TopRight(TopRight)
{
	checkValid();
}


Rectangle::Rectangle(const Vertex vertices[2])
	: Rectangle(vertices[0],vertices[1])
{}

Rectangle::Rectangle(double x0, double y0, double x1, double y1)
	: m_BotLeft(x0,y0), m_TopRight(x1,y1)
{
	checkValid();
}


Rectangle::Rectangle(const Vertex& start, double width, double height)  
	:m_BotLeft(start),  m_TopRight(start.m_col + width, start.m_row + height)
{
	//m_TopRight.m_col = start.m_col + width;
	//m_TopRight.m_row = start.m_row + height;
	checkValid();

}


Vertex Rectangle::getBottomLeft()const
{
	return m_BotLeft;
}


Vertex Rectangle::getTopRight()const
{
	return m_TopRight;
}

double Rectangle::getWidth()const
{
	return m_TopRight.m_col - m_BotLeft.m_col;
}

double Rectangle::getHeight()const
{
	return m_TopRight.m_row - m_BotLeft.m_row;
}


bool Rectangle::checkValid ()
{
	if (!m_BotLeft.isValid() || !m_TopRight.isValid())
	{
		setVertex();
		return false;
	}
	if (m_BotLeft.isHigherThan(m_TopRight))
	{
		setVertex();
		return false;

	}
	if (m_BotLeft.isToTheRightOf(m_TopRight))
	{
		setVertex();
		return false;
	}
	return true;
}


void Rectangle::setVertex()
{
	
	m_BotLeft.m_col = num2; //20	
	m_BotLeft.m_row = num1; //10 
	m_TopRight.m_col = num3; // 30 
	m_TopRight.m_row = num2; // 20 

}


void Rectangle::draw(Board& board) const
{
	Vertex botRight;	
	botRight.m_col = m_TopRight.m_col;
	botRight.m_row = m_BotLeft.m_row;
	Vertex topLeft; 
	topLeft.m_col = m_BotLeft.m_col;
	topLeft.m_row = m_TopRight.m_row;

	board.drawLine(m_BotLeft, botRight);
	board.drawLine(botRight, m_TopRight);
	board.drawLine(m_TopRight,topLeft);
	board.drawLine(topLeft, m_BotLeft);


}

Rectangle Rectangle::getBoundingRectangle()const
{
	return *this;  

 }

double Rectangle::getArea() const
{
	//double width = getWidth();
	//double height = getHeight();
	return getWidth() * getHeight();
}

double Rectangle::getPerimeter()const
{
	double width = getWidth();
	double height = getHeight();
	return width * 2 + height * 2;
}

Vertex Rectangle::getCenter()const
{
	Vertex center;
	center.m_col = (m_TopRight.m_col + m_BotLeft.m_col) / 2;
	center.m_row = (m_BotLeft.m_row + m_TopRight.m_row) / 2;
	return center;
}


bool Rectangle::scale(double factor)
{
	if (factor < 0)
	{
		return false;
	}

	Vertex center = getCenter();
	Vertex oldBotLeft = m_BotLeft;
	Vertex oldTopRight= m_TopRight;

	m_BotLeft.m_col = (m_BotLeft.m_col - center.m_col) * factor + center.m_col;
	m_BotLeft.m_row = (m_BotLeft.m_row - center.m_row) * factor + center.m_row;

	m_TopRight.m_col = (m_TopRight.m_col - center.m_col) * factor + center.m_col;
	m_TopRight.m_row = (m_TopRight.m_row - center.m_row) * factor + center.m_row;

	if (!checkValid())
	{
		m_BotLeft = oldBotLeft;
		m_TopRight = oldTopRight;
		return false;
	 }
	return true;

}

