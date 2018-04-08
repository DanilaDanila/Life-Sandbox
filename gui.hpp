#ifndef GUI_HPP
#define GUI_HPP

#include "Polygons.hpp"
#include <string>
#include <map>
#include <vector>
#include <SFML/System.hpp>

class button
{
private:
	polygon rect;

	bool checked;
	bool pressed;

	std::string caption;
	int text_size;

	bool is_checkbox;
	bool pressed_up;

	float delay;
	sf::Clock clock;

public:
	button();

	void create(polygon, bool is_checkbox);

	void update(vec2 mouse_pos, bool mouse_click);

	bool isPressed();

	bool isChecked();

	void setCaption(std::string);

	std::string getCaption();

	polygon getRect();

	void setTextSize(int);

	int getTextSize();

	void setDelay(float);

	~button();
};

class memo
{
private:
	std::vector<std::string> text;

	std::vector<int> text_size;

	float x,y;
	vec2 size;

public:
	memo();

	void setPosition(float,float);

	void addLine(std::string, int text_size);

	void clear();

	void eraseLine(int);

	int getLinesCount();

	std::string getLine(int);

	int getTextSizeOnLine(int);

	polygon getRect();

	void setSize(vec2);

	vec2 getSize();

	float getHeightToLine(int);

	~memo();
};

class gui
{
private:
	std::map<std::string, button> buttons;
	std::map<std::string, memo> memos;
public:
	gui();

	std::map<std::string, button> *getButtons();

	void addButton(std::string button_name, bool checkbox, float pos_x, float pos_y, float width, float height);

	void setTextToButton(std::string button_name, std::string text, int text_size);

	void deleteButton(std::string button_name);

	void update(float mouse_x, float mouse_y, bool mouse_click);

	bool isButtonPressed(std::string button_name);

	bool isButtonChecked(std::string button_name);

	void setButtonDelay(std::string button_name, float delay);

	std::map<std::string, memo> *getMemos();

	void addMemo(std::string memo_name, float pos_x, float pos_y, float width, float height);

	void addLineToMemo(std::string memo_name, std::string line, int text_size);

	void clearMemo(std::string memo_name);

	void clear();

	~gui();
};

#endif