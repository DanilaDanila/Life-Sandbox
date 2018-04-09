#include "main_window.hpp"
#include <GLUT/GLUT.h>
#include <SFML/System.hpp>

void main_window::createMenu()
{
	start_menu.addButton("START", false, WINDOW_WIDTH/2.0-50.0, WINDOW_HEIGHT/2.0-20.0-50, 100.0, 40.0);
	start_menu.setTextToButton("START", "START", 3);

	start_menu.addButton("GOD_MOD", true, WINDOW_WIDTH/2.0-50.0, WINDOW_HEIGHT/2.0-20.0, 100.0, 40.0);
	start_menu.setTextToButton("GOD_MOD", "GOD MOD", 3);

	start_menu.addButton("EVOLUTION", true, WINDOW_WIDTH/2.0-50.0, WINDOW_HEIGHT/2.0-20.0+50.0, 100.0, 40.0);
	start_menu.setTextToButton("EVOLUTION", "EVOLVE", 3);

	start_menu.addButton("INFO", false, WINDOW_WIDTH/2.0-50.0, WINDOW_HEIGHT/2.0-20.0+100.0, 100.0, 40.0);
	start_menu.setTextToButton("INFO", "INFO" , 3);

	start_menu.addButton("QUIT", false, WINDOW_WIDTH/2.0-50.0, WINDOW_HEIGHT/2.0-20.0+150.0, 100.0, 40.0);
	start_menu.setTextToButton("QUIT", "QUIT", 3);	

	start_menu.addMemo("INFO", 1.0, 1.0, 100.0, 20.0);
	start_menu.addLineToMemo("INFO", "CREATED BY MANAKOV DANILA", 4);
	start_menu.addLineToMemo("INFO", "07 APRIL 2018", 4);
	start_menu.getMemos()->at("INFO").setSize(vec2(start_menu.getMemos()->at("INFO").getRect().getVertex(1).x, start_menu.getMemos()->at("INFO").getRect().getVertex(2).y));



	info_menu.addButton("BACK", false, 10.0, 10, 100.0, 40.0);
	info_menu.setTextToButton("BACK", "BACK", 3);

	info_menu.addMemo("MEMO", 10.0, 60.0, 1004, 516);
	info_menu.addLineToMemo("MEMO", "I DO NOT KNOW WHAT YOU DO HERE. BUT IF YOU WANT, I TELL.", 4);
	info_menu.addLineToMemo("MEMO", "", 4);
	info_menu.addLineToMemo("MEMO", "Q: COULD YOU USE RUSSIAN?", 4);
	info_menu.addLineToMemo("MEMO", "A: %101101111101101ET!", 4);
	info_menu.addLineToMemo("MEMO", "", 4);
	info_menu.addLineToMemo("MEMO", "Q: CAN YOU USE OTHER SYMBOLS?", 4);
	info_menu.addLineToMemo("MEMO", "A: %011100100111000%101010000101010%110001001111000 %011100101100011%111000000000111%110001101001110", 4);
	info_menu.getMemos()->at("MEMO").setSize(vec2(info_menu.getMemos()->at("MEMO").getRect().getVertex(1).x, info_menu.getMemos()->at("MEMO").getRect().getVertex(2).y));
}

void main_window::createLake()
{
	lake.setLakeSize(vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	lake.setFoodCount(300.0);
	lake.setFirstGenerationFishesCount(20);
	lake.setDivineInterventionCount(20.0);
	lake.setMaxFishesCount(50);
	lake.setFirstGenerationProgramType(PROGRAM_RANDOM);
	lake.createFirstGeneration();
}

void main_window::createGodLake()
{
	lake.setLakeSize(vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
	lake.setFoodCount(300.0);
	lake.setFirstGenerationFishesCount(0);
	lake.setDivineInterventionCount(0.0);
	lake.setMaxFishesCount(10);
	lake.setFirstGenerationProgramType(PROGRAM_RANDOM);
	lake.createFirstGeneration();
}

main_window::main_window() {  }

void main_window::create()
{
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Life");
	window.setFramerateLimit(60.0);

	window.setActive(true);
	gluOrtho2D(0.0,1024.0,576.0,0.0);
	window.setActive(false);

	createMenu();
	menu=true;
	sandbox=false;
	evolution=false;
	info=false;
}

void main_window::createOneFish(float *prog)
{
	lake.ragnarok();
	lake.setFirstGenerationFishesCount(1);
	lake.setFirstGenerationProgramType(PROGRAM_INSTALLED);
	lake.setFirstGenerationProgram(prog);
	lake.createFirstGeneration();
}

float *main_window::getFish0Program()
{
	if(lake.getFish().size()!=0) return lake.getFish()[0].getProgram();
	else return nullptr;
}

void main_window::update(float time)
{
	if(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type==event.Closed) window.close();
		}
		window.clear();

		if(menu)
		{
			sf::Vector2i mpos=sf::Mouse::getPosition(window);
			bool click = sf::Mouse::isButtonPressed(sf::Mouse::Left);

			start_menu.update(float(mpos.x), float(mpos.y), click);
			drawGUI(&start_menu);

			if(start_menu.isButtonPressed("START"))
			{
				menu=false;

				if(start_menu.isButtonPressed("GOD_MOD"))
				{
					createGodLake();
					sandbox=true;
					evolution=true;
					info=false;
					
				}
				else
				{
					createLake();
					evolution=true;
					sandbox=false;
					info=false;
				}

				if(start_menu.isButtonPressed("EVOLUTION")) lake.setEvolve(true);
			}

			if(start_menu.isButtonPressed("INFO"))
			{
				evolution=false;
				sandbox=false;
				info=true;
				menu=false;
			}

			if(start_menu.isButtonPressed("QUIT")) window.close();
		}
		else
		if(evolution)
		{
			lake.update(time);

			window.setActive(true);
			drawLake(&lake);
			window.setActive(false);
		}
		else
		if(info)
		{
			sf::Vector2i mpos=sf::Mouse::getPosition(window);
			bool click = sf::Mouse::isButtonPressed(sf::Mouse::Left);
			info_menu.update(float(mpos.x), float(mpos.y), click);

			if(info_menu.isButtonPressed("BACK"))
			{
				evolution=false;
				sandbox=false;
				info=false;
				menu=true;
				start_menu.clear();
				info_menu.clear();
				this->createMenu();
			}

			drawGUI(&info_menu);
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			evolution=false;
			sandbox=false;
			info=false;
			menu=true;
			start_menu.clear();
			info_menu.clear();
			lake.ragnarok();
			this->createMenu();
		}

		window.display();
	}
}

bool main_window::isGodMode() { return sandbox; }

bool main_window::isOpen() { return window.isOpen(); }

void main_window::setActive(bool b) { window.setActive(b); }

main_window::~main_window() {}