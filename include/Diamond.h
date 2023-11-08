#pragma once 

#include <Vertex.h>
#include <Board.h>
#include <IsoscelesTriangle.h>
#include <Rectangle.h>



class Diamond {
	public:
	Diamond(const Vertex vertices[4]);
	Diamond(const IsoscelesTriangle& lower);


	double getWidth() const;
	double getHeight()const;
	Vertex getVertex(int index) const;




	void draw(Board& board) const;
	double getArea() const;
	Vertex getCenter()const;
	double getPerimeter()const;
	bool scale(double factor);
	Rectangle getBoundingRectangle()const;
	double calculateVertex(double factor, double center, double vertex);



private:


	IsoscelesTriangle m_top;
	IsoscelesTriangle m_bot;


	void setDiamond();
	bool checkValid();
	void setTri1(Vertex verticesTop[3], Vertex verticesBot[3]);
	void setTri2(const Vertex& left, const Vertex& right, double height);
};