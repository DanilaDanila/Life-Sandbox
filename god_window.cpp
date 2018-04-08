#include "god_window.hpp"
#include "renderer.hpp"
#include <GLUT/GLUT.h>
#include <SFML/System.hpp>

std::string code_to_fish_asm(float code)
{
	if(int(code)==code)
	{
		switch(int(code))
		{
			case 0: return "NONE("+std::to_string(0)+")";
			case 1: return "JMP("+std::to_string(1)+")";
			case 2: return "MOV("+std::to_string(2)+")";
			case 3: return "DEF("+std::to_string(3)+")";
			case 4: return "ADD("+std::to_string(4)+")";
			case 5: return "SUB("+std::to_string(5)+")";
			case 6: return "MULT("+std::to_string(6)+")";
			case 7: return "DIV("+std::to_string(7)+")";
			case 8: return "MIN("+std::to_string(8)+")";
			case 9: return "MAX("+std::to_string(9)+")";
			case 10: return "ADDN("+std::to_string(10)+")";
			case 11: return "SUBN("+std::to_string(11)+")";
			case 12: return "MULTN("+std::to_string(12)+")";
			case 13: return "DIVN("+std::to_string(13)+")";
			case 14: return "SIN("+std::to_string(14)+")";
			case 15: return "COS("+std::to_string(15)+")";
			case 16: return "TG("+std::to_string(16)+")";
			case 17: return "CTG("+std::to_string(17)+")";
			case 18: return "ASIN("+std::to_string(18)+")";
			case 19: return "ACOS("+std::to_string(19)+")";
			case 20: return "ATG("+std::to_string(20)+")";
			case 21: return "ACTG("+std::to_string(21)+")";
			case 22: return "JGZ("+std::to_string(22)+")";
			case 23: return "JEZ("+std::to_string(23)+")";
			case 24: return "JLZ("+std::to_string(24)+")";
			case 25: return "BREAK("+std::to_string(25)+")";
			default: return "UNONE("+std::to_string(code)+")";
		}
	}
	else return "UNONE("+std::to_string(code)+")";
	
}

bool is_number(const std::string& s)
{
    try
    {
        std::stod(s);
    }
    catch(...)
    {
        return false;
    }
    return true;
}

float fish_asm_to_command(std::string command)
{
	if(command=="NONE") return 0.0;
	if(command=="JMP") return 1.0;
	if(command=="MOV") return 2.0;
	if(command=="DEF") return 3.0;
	if(command=="ADD") return 4.0;
	if(command=="SUB") return 5.0;
	if(command=="MULT") return 6.0;
	if(command=="DIV") return 7.0;
	if(command=="MIN") return 8.0;
	if(command=="MAX") return 9.0;
	if(command=="ADDN") return 10.0;
	if(command=="SUBN") return 11.0;
	if(command=="MULTN") return 12.0;
	if(command=="DIVN") return 13.0;
	if(command=="SIN") return 14.0;
	if(command=="COS") return 15.0;
	if(command=="TG") return 16.0;
	if(command=="CTG") return 17.0;
	if(command=="ASIN") return 18.0;
	if(command=="ACOS") return 19.0;
	if(command=="ATG") return 20.0;
	if(command=="ACTG") return 21.0;
	if(command=="JGZ") return 22.0;
	if(command=="JEZ") return 23.0;
	if(command=="JLZ") return 24.0;
	if(command=="BREAK") return 25.0;
	if(is_number(command)) return std::stof(command);
	else return 0.0;
}

void god_window::updateMemos()
{
	interface.clearMemo("NUMS");
	interface.clearMemo("PROGRAM");

	for(int i=shift;i<49+shift;i++)
	{
		if(interface.isButtonPressed("EDIT"))
		{
			if(i!=shift+editing)
			{
				interface.addLineToMemo("NUMS", std::to_string(i), 2);
				interface.addLineToMemo("PROGRAM", code_to_fish_asm(program[i]), 2);
			}
			else
			{
				if(editing_now)
				{
					interface.addLineToMemo("NUMS", std::to_string(i), 3);
					interface.addLineToMemo("PROGRAM", command, 3);
				}
				else
				{
					interface.addLineToMemo("NUMS", std::to_string(i), 3);
					interface.addLineToMemo("PROGRAM", code_to_fish_asm(program[i]), 3);
				}
			}
		}
		else
		{
			interface.addLineToMemo("NUMS", std::to_string(i), 2);
			interface.addLineToMemo("PROGRAM", code_to_fish_asm(program[i]), 2);
		}
	}
}

god_window::god_window() 
{
	program = new float[PROGRAM_LEN];
	for(int i=0;i<PROGRAM_LEN;i++)
		program[i]=0.0;

	input_program = new float[PROGRAM_LEN];
	for(int i=0;i<PROGRAM_LEN;i++)
		input_program[i]=0.0;

	shift=0;
	editing=0;
	delay=0.1;
	editing_now=false;

	interface.addButton("UPLOAD", false, 10.0, 10.0, 70.0, 20.0);
	interface.setTextToButton("UPLOAD", "UPLOAD", 2);
	interface.setButtonDelay("UPLOAD", 1.0);

	interface.addButton("EDIT", true, 90.0, 10.0, 90.0, 20.0);
	interface.setTextToButton("EDIT", "GO EDITING", 2);
	interface.setButtonDelay("EDIT", 0.0);

	interface.addButton("TRACK", true, 190.0, 10.0, 90.0, 20.0);
	interface.setTextToButton("TRACK", "TRACKING", 2);
	interface.setButtonDelay("TRACK", 0.0);

	interface.addMemo("NUMS", 10.0, 40.0, 40.0, 597.0);
	interface.addMemo("PROGRAM", 50.0, 40.0, 260.0, 597.0);
}

void god_window::openWindow()
{
	ide.create(sf::VideoMode(320, 640), "IDE");
	ide.setFramerateLimit(60);

	ide.setActive(true);
	gluOrtho2D(0.0, 320.0, 640.0, 0.0);
	ide.setActive(false);

	updateMemos();
}

void god_window::closeWindow() { ide.close(); }

void god_window::update()
{
	if(ide.isOpen())
	{
		sf::Event event;
		while(ide.pollEvent(event))
		{
			if(event.type==event.Closed) ide.close();
		}
		ide.pushGLStates();
		ide.clear();
		ide.popGLStates();

		sf::Vector2i mpos=sf::Mouse::getPosition(ide);
		bool click = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		if((interface.isButtonPressed("EDIT")) && (clock.getElapsedTime().asSeconds()>delay))
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if(editing<48) editing++;
				else
					if(shift<PROGRAM_LEN-49) shift++;

				clock.restart();
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if(editing>0) editing--;
				else
					if(shift>0) shift--;

				clock.restart();
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				editing=shift=0;

				clock.restart();
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				editing=48;
				shift=PROGRAM_LEN-49;

				clock.restart();
			}

			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Slash))
				{
					command="";
					editing_now=true;

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					editing_now=false;
					if(command!="") program[shift+editing]=fish_asm_to_command(command);

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					if((editing_now) && (command.length()>0)) command.erase(command.end()-1);

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					if(editing_now) command+="A";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
				{
					if(editing_now) command+="B";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
				{
					if(editing_now) command+="C";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					if(editing_now) command+="D";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
					if(editing_now) command+="E";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
				{
					if(editing_now) command+="F";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
				{
					if(editing_now) command+="G";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
				{
					if(editing_now) command+="H";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
				{
					if(editing_now) command+="I";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
				{
					if(editing_now) command+="J";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
				{
					if(editing_now) command+="K";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
				{
					if(editing_now) command+="L";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
				{
					if(editing_now) command+="M";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
				{
					if(editing_now) command+="N";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
				{
					if(editing_now) command+="O";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				{
					if(editing_now) command+="P";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				{
					if(editing_now) command+="Q";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					if(editing_now) command+="R";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					if(editing_now) command+="S";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
				{
					if(editing_now) command+="T";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
				{
					if(editing_now) command+="U";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
				{
					if(editing_now) command+="V";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					if(editing_now) command+="W";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
				{
					if(editing_now) command+="X";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
				{
					if(editing_now) command+="Y";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{
					if(editing_now) command+="Z";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSlash))
				{
					if(editing_now) command+="-";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
				{
					if(editing_now) command+="0";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
				{
					if(editing_now) command+="1";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
				{
					if(editing_now) command+="2";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
				{
					if(editing_now) command+="3";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
				{
					if(editing_now) command+="4";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
				{
					if(editing_now) command+="5";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
				{
					if(editing_now) command+="6";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
				{
					if(editing_now) command+="7";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
				{
					if(editing_now) command+="8";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
				{
					if(editing_now) command+="9";

					clock.restart();
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
				{
					if(editing_now) command+=".";

					clock.restart();
				}
			}
		}

		if(interface.isButtonPressed("TRACK"))
		{
			for(int i=0; i<PROGRAM_LEN; i++)
				program[i]=input_program[i];
		}

		updateMemos();
		interface.update(mpos.x, mpos.y, click);

		ide.setActive(true);
		drawGUI(&interface);
		ide.setActive(false);

		upload=interface.isButtonPressed("UPLOAD");

		ide.pushGLStates();
		ide.display();
		ide.popGLStates();
	}
}

bool god_window::isOpen() { return ide.isOpen(); }

void god_window::setProgram(float *pr)
{
	if(pr!=nullptr)
	{
		for(int i=0;i<PROGRAM_LEN;i++)
			input_program[i]=pr[i];
	}
}

bool god_window::uploadProgram() { return upload; }

float *god_window::getUploadingProgram() { return program; }

god_window::~god_window() {}