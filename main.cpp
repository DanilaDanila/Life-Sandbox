#include <SFML/Graphics.hpp>
#include <GLUT/GLUT.h>
#include "main_window.hpp"
#include "god_window.hpp"

int main()
{
	srand(time(0));

	sf::Clock clock;
	float time;
	
	bool running=true;

	main_window world;
	world.create();

	god_window console;
	bool god_mode=false;

	while(running)
	{
		time=clock.getElapsedTime().asMilliseconds()/10.0;
		clock.restart();

		if(!god_mode)
		{
			if(console.isOpen()) console.closeWindow();
			god_mode=world.isGodMode();
			if(god_mode) console.openWindow();
		}

		god_mode=world.isGodMode();

		if(god_mode) 
		{
			console.setProgram(world.getFish0Program());
			console.update();
		}

		running=world.isOpen();

		if(console.uploadProgram())
		{
			world.createOneFish(console.getUploadingProgram());
		}

		world.update(time);
	}
	if(god_mode) console.closeWindow();

	return 0;
}