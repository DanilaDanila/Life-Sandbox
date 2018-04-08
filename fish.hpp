#ifndef FISH_HPP
#define FISH_HPP

#include "Polygons.hpp"
#include <SFML/System.hpp>

#define PROGRAM_LEN 100

class fish
{
private:

	float *program;

	float speed_min;
	float speed_normal;
	float speed_max;
	float speed_current;

	float angle_deviation;

	vec2 position;
	float rotation;
	float d_angle;

	polygon head;
	polygon body;
	vec2 size;

	sf::Clock timer;
	float delay;

	void setTarget(float);

public:
	float health;

	fish();

	void setTimerDelay(float);

	void setLakeSize(vec2);

	polygon getHead();

	polygon getBody();

	void setPosition(vec2);

	vec2 getPosition();

	void setRotation(float);

	float getRotation();

	void setMaxAngleDeviation(float);

	float getMaxAngleDeviation();

	void setProgram(float*);

	float *getProgram();

	void writeToRegisters(vec2 nearest_food, vec2 nearest_herbivore, vec2 nearest_predator);

	void update(float time);

	bool isTimer();

	void restartTimer();

	bool isLife();

	~fish();
};

#endif