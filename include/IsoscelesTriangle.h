#pragma once
#include "Utilities.h"
#include <Vertex.h>
#include <Board.h>
#include <Rectangle.h>




class IsoscelesTriangle
{
	public:

		//IsoscelesTriangle() = default;

		IsoscelesTriangle(const Vertex vertices[3]);
		IsoscelesTriangle(const Vertex& left, const Vertex& right, double height);


		Vertex getVertex(int index) const;
		double getLegLength() const;
		double getBaseLength()const;
		double getHeight()const;


		void draw(Board& board) const;
		double getArea() const;
		Vertex getCenter()const;
		double getPerimeter()const;
		bool scale(double factor);
		Rectangle getBoundingRectangle()const;


	private:


		bool  checkValid();
		void setsVertex();
		bool checkLegs();
		double getDistance(const Vertex v1, const Vertex v2);
		double  calculateVertex(double factor, double center, double vertex);

		Vertex m_top;
		Vertex m_botLeft;
		Vertex m_botRight;

};