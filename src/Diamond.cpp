#pragma once

#include "Diamond.h"

const Vertex V0  (20, 20);
const Vertex V1  (25, 25);
const Vertex V2  (30, 20);
const Vertex V3  (25, 15);


Diamond::Diamond(const Vertex vertices[4])
	: m_top(vertices[0], vertices[2], vertices[1].m_row - vertices[2].m_row),
	m_bot(vertices[0], vertices[2],(vertices[2].m_row- vertices[3].m_row)*-1)

{
	//check if the values are valid- if not replace them
	if (!checkValid())
	{
		setDiamond();
	}
}


Diamond::Diamond(const IsoscelesTriangle& lower)
	: m_bot(lower), m_top(lower.getVertex(0), lower.getVertex(2), lower.getHeight()*-1)
{

	//check if the values are valid- if not replace them
	if (!checkValid())
	{
		setDiamond();
	}
}


double Diamond::getWidth() const
{
	//returs the value of the base of one of the triangle
	return m_top.getBaseLength();

}


double Diamond::getHeight()const
{
	//return the height of one of the triangle and double it
	return 2 * m_top.getHeight();
}


Vertex Diamond::getVertex(int index) const
{
	//check the number of the index anf calls the function get vertex of triangle
	if (index == 0)
	{
		return m_top.getVertex(0);
	}

	else if (index == 1)
	{
		return m_top.getVertex(1);
	}

	else if (index == 2)
	{
		return m_top.getVertex(2);
	}
	return m_bot.getVertex(1);


}


void Diamond::draw(Board& board) const
{
	//print the upper triangle and the lower one 
	m_bot.draw(board);
	m_top.draw(board);
}


double Diamond::getArea() const
{
	//gets the area of one trianle and double it
	return m_top.getArea() * 2;
}


Vertex  Diamond::getCenter()const
{
	//take the base and cut it to 2
	Vertex center;
	center.m_col = (m_top.getVertex(2).m_col + m_top.getVertex(0).m_col) / 2;
	center.m_row = (m_top.getVertex(2).m_row + m_top.getVertex(0).m_row) / 2;

	return center ;
}

double Diamond::getPerimeter()const
{
	//return one of the legs and doubles it 
	return m_bot.getLegLength() * 4;

}

bool Diamond::scale(double factor)
{	
	//return the values of the center
	Vertex center = this->getCenter();

	if (factor < 0)
		return false;


	Vertex v0, v1, v2, v3;

	Diamond d0 = *this;
	//calculate the new values of the vertecies with the factor in relation to the center
	v0.m_col = calculateVertex(factor, center.m_col, m_top.getVertex(0).m_col);
	v0.m_row = calculateVertex(factor, center.m_row, m_top.getVertex(0).m_row);

	v1.m_col = calculateVertex(factor, center.m_col, m_top.getVertex(1).m_col);
	v1.m_row = calculateVertex(factor, center.m_row, m_top.getVertex(1).m_row);

	v2.m_col = calculateVertex(factor, center.m_col, m_top.getVertex(2).m_col);
	v2.m_row = calculateVertex(factor, center.m_row, m_top.getVertex(2).m_row);

	v3.m_col = calculateVertex(factor, center.m_col, m_bot.getVertex(1).m_col);
	v3.m_row = calculateVertex(factor, center.m_row, m_bot.getVertex(1).m_row);

	Vertex vertecies[4] = { v0, v1, v2, v3 };

	//creates new diamond 
	Diamond d1(vertecies);

	*this = d1;
	//check the validtion of it 
	if (!checkValid())
	{
		*this = d0;
		return false;
	}
	return true;

}


double Diamond::calculateVertex(double factor, double center, double vertex)
{
	//calculte the value of the coordinates in relation to the center
	return center - ((center - vertex) * factor);
}





Rectangle Diamond::getBoundingRectangle()const
{
	//creates new vertex for the rectangle
	Vertex vBot, vTop;
	vBot.m_col = m_bot.getVertex(0).m_col;
	vBot.m_row = m_bot.getVertex(1).m_row;

	vTop.m_col = m_top.getVertex(2).m_col;
	vTop.m_row = m_top.getVertex(1).m_row;
	//c-tor of rectanlge
	Rectangle blockRec(vBot, vTop);
	return blockRec;

}


bool  Diamond::checkValid()
{
	//check if the y value of the lower triagle and the upper onr are equal - if so
	// need to create a deafult diamond
	if (doubleEqual(m_bot.getVertex(1).m_row,m_top.getVertex(1).m_row))
	{
		return false;
	}

	//check if the triangls not equal
	if (m_top.getLegLength() == m_bot.getLegLength())
	{
		return true;
	}
	return false;

}

void Diamond::setDiamond()
{
	//creates a default diamond
	Vertex vertices[4] = {V0,V1,V2, V3};
	Diamond d1(vertices);

	*this = d1;
}

void Diamond::setTri1( Vertex verticesTop[3], Vertex verticesBot[3])
{
	IsoscelesTriangle t1(verticesTop);
	m_top = t1;
	IsoscelesTriangle t2(verticesBot);
	m_bot = t2;
}

