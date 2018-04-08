#ifndef GOD_WINDOW_HPP
#define GOD_WINDOW_HPP

#include <SFML/Graphics.hpp>
#include "gui.hpp"

class god_window
{
private:

	sf::RenderWindow ide;

	gui interface;

	int shift;
	int editing;
	int fish_count;
	bool upload;

	float *program;
	float *input_program;
	bool editing_now;
	std::string command;

	sf::Clock clock;
	float delay;

	void updateMemos();

public:
	god_window();

	void openWindow();

	void closeWindow();

	void update();

	bool isOpen();

	void setProgram(float *);

	bool uploadProgram();

	float *getUploadingProgram();

	~god_window();
};

#endif