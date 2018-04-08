#ifndef MY_TEXT_HPP
#define MY_TEXT_HPP

#include <string>
#include <map>
#include "Polygons.hpp"

struct letter
{
public:
	bool bitmap[3][5];

	letter() {}

	letter(bool x0_y0, bool x1_y0, bool x2_y0, bool x0_y1, bool x1_y1, bool x2_y1, bool x0_y2, bool x1_y2, bool x2_y2, bool x0_y3, bool x1_y3, bool x2_y3, bool x0_y4, bool x1_y4, bool x2_y4)
	{
		bitmap[0][0]=x0_y0; bitmap[1][0]=x1_y0; bitmap[2][0]=x2_y0; 
		bitmap[0][1]=x0_y1; bitmap[1][1]=x1_y1; bitmap[2][1]=x2_y1; 
		bitmap[0][2]=x0_y2; bitmap[1][2]=x1_y2; bitmap[2][2]=x2_y2; 
		bitmap[0][3]=x0_y3; bitmap[1][3]=x1_y3; bitmap[2][3]=x2_y3; 
		bitmap[0][4]=x0_y4; bitmap[1][4]=x1_y4; bitmap[2][4]=x2_y4;
	}

	~letter() {}
};

class my_text
{
private:
	std::map<char, letter> font;

	std::string s;
	int size;
	int x;
	int y;
	float r,g,b;

	void drawLetter(letter*);

public:
	my_text();

	void setSize(int);

	void setPosition(int,int);

	void setColor(float,float,float);

	void setString(std::string);

	void draw();

	vec2 getRectSize();

	~my_text();
};

#endif