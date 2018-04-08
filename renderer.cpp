#include "renderer.hpp"
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <map>
#include "my_text.hpp"

void drawGUI(gui *g)
{
	for(std::map<std::string, memo>::iterator it=g->getMemos()->begin(); it!=g->getMemos()->end(); it++)
		drawMemo(&it->second);

	for(std::map<std::string, button>::iterator it=g->getButtons()->begin(); it!=g->getButtons()->end(); it++)
		if(it->second.isPressed()) drawButtonPressed(&it->second);
	else
		if(it->second.isChecked()) drawButtonChecked(&it->second);
	else drawButtonDefault(&it->second);
}

void drawButtonDefault(button *b)
{
	polygon rect = b->getRect();

	glPushMatrix();
	glTranslatef(rect.getPosition().x, rect.getPosition().y, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(rect.getVertex(0).x, rect.getVertex(0).y);
	glVertex2f(rect.getVertex(1).x, rect.getVertex(1).y);

	glVertex2f(rect.getVertex(1).x, rect.getVertex(1).y);
	glVertex2f(rect.getVertex(2).x, rect.getVertex(2).y);

	glVertex2f(rect.getVertex(2).x, rect.getVertex(2).y);
	glVertex2f(rect.getVertex(3).x, rect.getVertex(3).y);

	glVertex2f(rect.getVertex(3).x, rect.getVertex(3).y);
	glVertex2f(rect.getVertex(0).x, rect.getVertex(0).y);
	glEnd();
	glPopMatrix();

	my_text text;
	text.setSize(b->getTextSize());
	text.setString(b->getCaption());
	text.setColor(1.0, 1.0, 1.0);

	vec2 size = text.getRectSize();
	vec2 button_size = vec2(rect.getVertex(1).x, rect.getVertex(2).y);

	text.setPosition(rect.getPosition().x+(button_size.x-size.x)/2.0, rect.getPosition().y+(button_size.y-size.y)/2.0);

	text.draw();
}

void drawButtonPressed(button *b)
{
	polygon rect = b->getRect();

	glPushMatrix();
	glTranslatef(rect.getPosition().x, rect.getPosition().y, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(rect.getVertex(0).x, rect.getVertex(0).y);
	glVertex2f(rect.getVertex(1).x, rect.getVertex(1).y);

	glVertex2f(rect.getVertex(1).x, rect.getVertex(1).y);
	glVertex2f(rect.getVertex(2).x, rect.getVertex(2).y);

	glVertex2f(rect.getVertex(2).x, rect.getVertex(2).y);
	glVertex2f(rect.getVertex(3).x, rect.getVertex(3).y);

	glVertex2f(rect.getVertex(3).x, rect.getVertex(3).y);
	glVertex2f(rect.getVertex(0).x, rect.getVertex(0).y);
	glEnd();
	glPopMatrix();

	my_text text;
	text.setSize(b->getTextSize());
	text.setString(b->getCaption());
	text.setColor(1.0, 1.0, 1.0);

	vec2 size = text.getRectSize();
	vec2 button_size = vec2(rect.getVertex(1).x, rect.getVertex(2).y);

	text.setPosition(rect.getPosition().x+(button_size.x-size.x)/2.0, rect.getPosition().y+(button_size.y-size.y)/2.0);

	text.draw();
}

void drawButtonChecked(button *b)
{
	polygon rect = b->getRect();

	glPushMatrix();
	glTranslatef(rect.getPosition().x, rect.getPosition().y, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(rect.getVertex(0).x, rect.getVertex(0).y);
	glVertex2f(rect.getVertex(1).x, rect.getVertex(1).y);

	glVertex2f(rect.getVertex(1).x, rect.getVertex(1).y);
	glVertex2f(rect.getVertex(2).x, rect.getVertex(2).y);

	glVertex2f(rect.getVertex(2).x, rect.getVertex(2).y);
	glVertex2f(rect.getVertex(3).x, rect.getVertex(3).y);

	glVertex2f(rect.getVertex(3).x, rect.getVertex(3).y);
	glVertex2f(rect.getVertex(0).x, rect.getVertex(0).y);
	glEnd();
	glPopMatrix();

	my_text text;
	text.setSize(b->getTextSize());
	text.setString(b->getCaption());
	text.setColor(1.0, 1.0, 1.0);

	vec2 size = text.getRectSize();
	vec2 button_size = vec2(rect.getVertex(1).x, rect.getVertex(2).y);

	text.setPosition(rect.getPosition().x+(button_size.x-size.x)/2.0, rect.getPosition().y+(button_size.y-size.y)/2.0);

	text.draw();
}

void drawMemo(memo *m)
{
	vec2 pos = m->getRect().getPosition();
	vec2 size=m->getSize();

	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(size.x, 0.0);

	glVertex2f(size.x, 0.0);
	glVertex2f(size.x, size.y);

	glVertex2f(size.x, size.y);
	glVertex2f(0.0, size.y);

	glVertex2f(0.0, size.y);
	glVertex2f(0.0, 0.0);
	glEnd();
	glPopMatrix();

	my_text text;
	for(int i=0;i<m->getLinesCount();i++)
	{
		text.setSize(m->getTextSizeOnLine(i));
		text.setString(m->getLine(i));
		text.setColor(1.0, 1.0, 1.0);
		text.setPosition(pos.x+1, pos.y+m->getHeightToLine(i)+2);
		text.draw();
	}

}

void drawLake(lake *l)
{
	drawWhater(l->getLakeSize());

	for(int i=0;i<l->getFood().size();i++)
	{
		glPushMatrix();
		glTranslatef(l->getFood()[i].x, l->getFood()[i].y, 0.0);
		glColor3f(1.0, 1.0, 1.0);
		drawFood();
		glPopMatrix();
	}

	for(int i=0;i<l->getFish().size();i++)
	{
		glPushMatrix();
		glTranslatef(l->getFish()[i].getPosition().x, l->getFish()[i].getPosition().y, 0.0);
		glRotatef(l->getFish()[i].getRotation()/pi*180, 0.0, 0.0, 1.0);
		if(l->getFish()[i].getProgram()[0]==0) glColor3f(0.6, 1.0, 0.6);
		else glColor3f(1.0, 0.6, 0.6);
		drawFish();
		glPopMatrix();
	}
}

void drawWhater(vec2 size)
{
	/*glPushMatrix();
	glColor3f(0.3,0.3,1.0);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(size.x, 0.0);
	glVertex2f(size.x, size.y);
	glVertex2f(0.0, size.y);
	glEnd();
	glPopMatrix();*/
}

void drawFood()
{
	glBegin(GL_POINTS);
	glVertex2f(0.0,0.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(-1.0, 0.0);
	glVertex2f(0.0, 1.0);
	glVertex2f(0.0, -1.0);
	glEnd();
}

void drawFish()
{
	float a=4.0;
	float h=2.0*a;

	glBegin(GL_LINES);
	// head
	glVertex2f(-a/2.0, -a/2.0);
	glVertex2f(a/2.0, -a/2.0);

	glVertex2f(a/2.0, -a/2.0);
	glVertex2f(a/2.0, a/2.0);

	glVertex2f(a/2.0, a/2.0);
	glVertex2f(-a/2.0, a/2.0);

	glVertex2f(-a/2.0, a/2.0);
	glVertex2f(-a/2.0, -a/2.0);

	// body
	glVertex2f(-a/2.0-h, 0.0);
	glVertex2f(-a/2.0, -a/2.0);

	glVertex2f(-a/2.0-h, 0.0);
	glVertex2f(-a/2.0, a/2.0);
	glEnd();
}