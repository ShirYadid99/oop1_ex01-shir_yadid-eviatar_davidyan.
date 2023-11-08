#pragma once
#include <Vertex.h>
#include <Board.h>


class Rectangle {
	public:
		//Rectangle() = default;

		Rectangle(const Vertex& BottonLeft, const Vertex& TopRight);
		Rectangle(const Vertex vertices[2]);
		Rectangle(double x0, double y0, double x1, double y1);
		Rectangle(const Vertex& start, double width, double height);


		Vertex getBottomLeft()const;
		Vertex getTopRight()const;
		double getWidth()const;
		double getHeight()const;

		void draw(Board& board) const;
		double getArea() const;
		Vertex getCenter()const;
		double getPerimeter()const;
		bool scale(double factor);
		Rectangle getBoundingRectangle()const;


	private:
		Vertex m_TopRight;
		Vertex m_BotLeft;


		bool checkValid();
		void setVertex();



};


