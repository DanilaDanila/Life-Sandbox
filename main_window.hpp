#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 576

#include <SFML/Graphics.hpp>
#include "lake.hpp"
#include "renderer.hpp"
#include "gui.hpp"

class main_window
{
private:

	sf::RenderWindow window;

	gui start_menu;

	lake lake;
	
	bool sandbox;
	bool menu;
	bool evolution;

	void createMenu();
	void createLake();
	void createGodLake();

public:
	main_window();

	void create();

	void createOneFish(float*);

	float *getFish0Program();

	void update(float time);

	bool isGodMode();

	bool isOpen();

	void setActive(bool);

	~main_window();
};

#endif