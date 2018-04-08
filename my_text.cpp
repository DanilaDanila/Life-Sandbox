#include "my_text.hpp"
#include <GLUT/GLUT.h>

void drawSquare(int size, int x, int y)
{
	glBegin(GL_QUADS);
	glVertex2f(x,y);
	glVertex2f(x+size,y);
	glVertex2f(x+size,y+size);
	glVertex2f(x,y+size);
	glEnd();
}

void my_text::drawLetter(letter *l)
{
	for(int i=0;i<3;i++)
		for(int j=0;j<5;j++)
			if(l->bitmap[i][j])
				drawSquare(size, i*size, j*size);
}

my_text::my_text() 
{
	font.insert(std::pair<char, letter>('0', letter()));
	font['0']=letter(1,1,1,
					 1,0,1,
					 1,0,1,
					 1,0,1,
					 1,1,1);

	font.insert(std::pair<char, letter>('1', letter()));
	font['1']=letter(0,0,1,
					 0,1,1,
					 0,0,1,
					 0,0,1,
					 0,0,1);

	font.insert(std::pair<char, letter>('2', letter()));
	font['2']=letter(1,1,1,
					 0,0,1,
					 1,1,1,
					 1,0,0,
					 1,1,1);

	font.insert(std::pair<char, letter>('3', letter()));
	font['3']=letter(1,1,1,
					 0,0,1,
					 1,1,1,
					 0,0,1,
					 1,1,1);

	font.insert(std::pair<char, letter>('4', letter()));
	font['4']=letter(1,0,1,
					 1,0,1,
					 1,1,1,
					 0,0,1,
					 0,0,1);

	font.insert(std::pair<char, letter>('5', letter()));
	font['5']=letter(1,1,1,
					 1,0,0,
					 1,1,1,
					 0,0,1,
					 1,1,1);

	font.insert(std::pair<char, letter>('6', letter()));
	font['6']=letter(1,1,1,
					 1,0,0,
					 1,1,1,
					 1,0,1,
					 1,1,1);

	font.insert(std::pair<char, letter>('7', letter()));
	font['7']=letter(1,1,1,
					 0,0,1,
					 0,0,1,
					 0,0,1,
					 0,0,1);

	font.insert(std::pair<char, letter>('8', letter()));
	font['8']=letter(1,1,1,
					 1,0,1,
					 1,1,1,
					 1,0,1,
					 1,1,1);

	font.insert(std::pair<char, letter>('9', letter()));
	font['9']=letter(1,1,1,
					 1,0,1,
					 1,1,1,
					 0,0,1,
					 1,1,1);

	font.insert(std::pair<char, letter>('!', letter()));
	font['!']=letter(0,1,0,
					 0,1,0,
					 0,1,0,
					 0,0,0,
					 0,1,0);

	font.insert(std::pair<char, letter>('.', letter()));
	font['.']=letter(0,0,0,
					 0,0,0,
					 0,0,0,
					 0,0,0,
					 0,1,0);

	font.insert(std::pair<char, letter>(',', letter()));
	font[',']=letter(0,0,0,
					 0,0,0,
					 0,0,0,
					 0,1,1,
					 0,0,1);

	font.insert(std::pair<char, letter>(':', letter()));
	font[':']=letter(0,0,0,
					 0,1,0,
					 0,0,0,
					 0,0,0,
					 0,1,0);

	font.insert(std::pair<char, letter>('(', letter()));
	font['(']=letter(0,1,0,
					 1,0,0,
					 1,0,0,
					 1,0,0,
					 0,1,0);

	font.insert(std::pair<char, letter>(')', letter()));
	font[')']=letter(0,1,0,
					 0,0,1,
					 0,0,1,
					 0,0,1,
					 0,1,0);

	font.insert(std::pair<char, letter>('-', letter()));
	font['-']=letter(0,0,0,
					 0,0,0,
					 1,1,1,
					 0,0,0,
					 0,0,0);

	font.insert(std::pair<char, letter>('A', letter()));
	font['A']=letter(0,1,0,
					 1,1,1,
					 1,0,1,
					 1,1,1,
					 1,0,1);

	font.insert(std::pair<char, letter>('B', letter()));
	font['B']=letter(1,1,1,
					 1,0,1,
					 1,1,0,
					 1,0,1,
					 1,1,1);

	font.insert(std::pair<char, letter>('C', letter()));
	font['C']=letter(1,1,1,
					 1,0,0,
					 1,0,0,
					 1,0,0,
					 1,1,1);

	font.insert(std::pair<char, letter>('D', letter()));
	font['D']=letter(1,1,0,
					 1,0,1,
					 1,0,1,
					 1,0,1,
					 1,1,0);

	font.insert(std::pair<char, letter>('E', letter()));
	font['E']=letter(1,1,1,
					 1,0,0,
					 1,1,1,
					 1,0,0,
					 1,1,1);

	font.insert(std::pair<char, letter>('F', letter()));
	font['F']=letter(1,1,1,
					 1,0,0,
					 1,1,1,
					 1,0,0,
					 1,0,0);

	font.insert(std::pair<char, letter>('G', letter()));
	font['G']=letter(1,1,1,
					 1,0,0,
					 1,0,1,
					 1,0,1,
					 1,1,1);

	font.insert(std::pair<char, letter>('H', letter()));
	font['H']=letter(1,0,0,
					 1,0,0,
					 1,1,1,
					 1,0,1,
					 1,0,1);

	font.insert(std::pair<char, letter>('I', letter()));
	font['I']=letter(1,1,1,
					 0,1,0,
					 0,1,0,
					 0,1,0,
					 1,1,1);

	font.insert(std::pair<char, letter>('J', letter()));
	font['J']=letter(0,0,1,
					 0,0,1,
					 0,0,1,
					 1,0,1,
					 0,1,0);

	font.insert(std::pair<char, letter>('K', letter()));
	font['K']=letter(1,0,1,
					 1,0,1,
					 1,1,0,
					 1,0,1,
					 1,0,1);

	font.insert(std::pair<char, letter>('L', letter()));
	font['L']=letter(1,0,0,
					 1,0,0,
					 1,0,0,
					 1,0,0,
					 1,1,1);

	font.insert(std::pair<char, letter>('M', letter()));
	font['M']=letter(1,0,1,
					 1,1,1,
					 1,0,1,
					 1,0,1,
					 1,0,1);

	font.insert(std::pair<char, letter>('N', letter()));
	font['N']=letter(0,0,0,
					 1,1,1,
					 1,0,1,
					 1,0,1,
					 1,0,1);

	font.insert(std::pair<char, letter>('O', letter()));
	font['O']=letter(0,0,0,
					 1,1,1,
					 1,0,1,
					 1,0,1,
					 1,1,1);

	font.insert(std::pair<char, letter>('P', letter()));
	font['P']=letter(1,1,1,
					 1,0,1,
					 1,1,1,
					 1,0,0,
					 1,0,0);

	font.insert(std::pair<char, letter>('Q', letter()));
	font['Q']=letter(1,1,1,
					 1,0,1,
					 1,0,1,
					 1,1,1,
					 0,0,1);

	font.insert(std::pair<char, letter>('R', letter()));
	font['R']=letter(1,1,1,
					 1,0,1,
					 1,1,1,
					 1,1,0,
					 1,0,1);

	font.insert(std::pair<char, letter>('S', letter()));
	font['S']=letter(0,1,1,
					 1,0,0,
					 1,1,1,
					 0,0,1,
					 1,1,0);

	font.insert(std::pair<char, letter>('T', letter()));
	font['T']=letter(1,1,1,
					 0,1,0,
					 0,1,0,
					 0,1,0,
					 0,1,0);

	font.insert(std::pair<char, letter>('U', letter()));
	font['U']=letter(1,0,1,
					 1,0,1,
					 1,0,1,
					 1,0,1,
					 1,1,1);

	font.insert(std::pair<char, letter>('V', letter()));
	font['V']=letter(1,0,1,
					 1,0,1,
					 1,0,1,
					 1,0,1,
					 0,1,0);

	font.insert(std::pair<char, letter>('W', letter()));
	font['W']=letter(1,0,1,
					 1,0,1,
					 1,0,1,
					 1,1,1,
					 1,0,1);

	font.insert(std::pair<char, letter>('X', letter()));
	font['X']=letter(1,0,1,
					 1,0,1,
					 0,1,0,
					 1,0,1,
					 1,0,1);

	font.insert(std::pair<char, letter>('Y', letter()));
	font['Y']=letter(1,0,1,
					 1,0,1,
					 1,1,1,
					 0,1,0,
					 0,1,0);

	font.insert(std::pair<char, letter>('Z', letter()));
	font['Z']=letter(1,1,1,
					 0,0,1,
					 0,1,0,
					 1,0,0,
					 1,1,1);
}

void my_text::setSize(int i) { size=i; }

void my_text::setPosition(int a, int b) { x=a; y=b; }

void my_text::setColor(float a0, float a1, float a2) { r=a0; g=a2; b=a2; }

void my_text::setString(std::string str) { s=str; }

void my_text::draw()
{
	glColor3f(r, g, b);
	for(int i=0;i<s.length();i++)
		if(font.find(s[i])!=font.end())
		{
			glPushMatrix();
			glTranslatef(x+i*3*size+i*size, y, 0.0);
			drawLetter(&font[s[i]]);
			glPopMatrix();
		}
}

vec2 my_text::getRectSize()
{
	vec2 rect_size;
	rect_size.x=s.length()*3*size+s.length()*size;
	rect_size.y=5*size;

	return rect_size;
}

my_text::~my_text() {}