#include "fish.hpp"
#include <cmath>

void fish::setTarget(float target)
{
	if(abs(target)>angle_deviation) d_angle=target/abs(target)*angle_deviation;
	else d_angle=target;
}

fish::fish()
{
	speed_min=1.0;
	speed_normal=2.0;
	speed_max=3.0;
	d_angle=0;

	angle_deviation=pi/32.0;

	speed_current=speed_normal;

	float a=4.0;
	head.setVertexCount(4);
	head.setVertex(0, vec2(-a/2.0, -a/2.0));
	head.setVertex(1, vec2(a/2.0, -a/2.0));
	head.setVertex(2, vec2(a/2.0, a/2.0));
	head.setVertex(3, vec2(-a/2.0, a/2.0));
	head.setOrigin(vec2(0.0, 0.0));

	float h=2.0*a;
	body.setVertexCount(3);
	body.setVertex(0, vec2(-a/2.0, -a/2.0));
	body.setVertex(1, vec2(-a/2.0, a/2.0));
	body.setVertex(2, vec2(-a/2.0-h, 0.0));
	body.setOrigin(vec2(0.0, 0.0));

	health=15.0;

	program = new float[PROGRAM_LEN];
}

void fish::setTimerDelay(float d) { delay=d; }

void fish::setLakeSize(vec2 s) { size=s; }

polygon fish::getHead() { return head; }

polygon fish::getBody() { return body; }

void fish::setPosition(vec2 p) { position=p; }

vec2 fish::getPosition() { return position; }

void fish::setRotation(float r) { rotation=r; }

float fish::getRotation() { return rotation; }

void fish::setMaxAngleDeviation(float a) { angle_deviation=a; }

float fish::getMaxAngleDeviation() { return angle_deviation; }

void fish::setProgram(float *p)
{
	for(int i=0;i<PROGRAM_LEN;i++)
		program[i]=p[i];
}

float *fish::getProgram()
{
	return program;
}

void fish::writeToRegisters(vec2 nearest_food, vec2 nearest_herbivore, vec2 nearest_predator)
{
	program[1]=health;
	program[2]=position.x;
	program[3]=position.y;
	program[4]=rotation;
	program[5]=angle_deviation;
	program[6]=nearest_food.x;
	program[7]=nearest_food.y;
	program[8]=nearest_herbivore.x;
	program[9]=nearest_herbivore.y;
	program[10]=nearest_predator.x;
	program[11]=nearest_predator.y;
}

void fish::update(float time)
{
	while(rotation>pi) rotation=-2*pi+rotation;
	while(rotation<-pi) rotation=2*pi+rotation;

	head.setPosition(position);
	body.setPosition(position);

	setTarget(program[12]);
	rotation+=d_angle*time;

	switch(int(program[13]))
	{
		case 0: speed_current=speed_min; break;
		case 2: speed_current=speed_max; break;
		default: speed_current=speed_normal; break;
	}

	position=position+vec2(cos(rotation),sin(rotation))*speed_current*time;

	if(position.x<0) position.x+=size.x;
	if(position.x>size.x) position.x-=size.x;
	if(position.y<0) position.y+=size.y;
	if(position.y>size.y) position.y-=size.y;

	if(health>20.0) health=20.0;
}

bool fish::isTimer() { return timer.getElapsedTime().asSeconds()>=delay; }

void fish::restartTimer() { timer.restart(); }

bool fish::isLife() { return health>0; }

fish::~fish() {}