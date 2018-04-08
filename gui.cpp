#include "gui.hpp"

button::button() { pressed=false; delay=0.1; pressed_up=true; }

void button::create(polygon p, bool b) { rect=p; is_checkbox=b; }

void button::update(vec2 mouse_pos, bool mouse_click)
{
	if(!is_checkbox)
	{
		checked=rect.isPointInside(mouse_pos);
		if((clock.getElapsedTime().asSeconds()>delay) && (checked and mouse_click))
		{
			clock.restart();
			pressed=true;
		}
		else pressed=false;
	}
	else
	{
		if((rect.isPointInside(mouse_pos) and mouse_click) && (clock.getElapsedTime().asSeconds()>delay)) 
		{
			if(pressed_up)
			{
				pressed=!pressed;
				clock.restart();
				pressed_up=false;
			}
		}
		if(!pressed_up) pressed_up=!mouse_click;
		checked=!pressed;
	}
}

bool button::isPressed() { return pressed; }

bool button::isChecked() { return checked; }

polygon button::getRect() { return rect; }

void button::setCaption(std::string s) { caption=s; }

std::string button::getCaption() { return caption; }

void button::setTextSize(int i) { text_size=i; }

int button::getTextSize() { return text_size; }

void button::setDelay(float f) { delay=f; }

button::~button() {}


memo::memo() {}

void memo::setPosition(float a, float b)
{
	x=a;
	y=b;
}

void memo::addLine(std::string s, int t_size)
{
	text.push_back(std::string());
	text[text.size()-1]=s;

	text_size.push_back(int());
	text_size[text_size.size()-1]=t_size;
}

void memo::clear() { text.clear(); text_size.clear(); }

void memo::eraseLine(int i)
{
	text.erase(text.begin()+i);
}

int memo::getLinesCount() { return text.size(); }

std::string memo::getLine(int i) 
{
	if(text.size()<i) return "";
	return text[i];
}

int memo::getTextSizeOnLine(int i)
{
	if(text_size.size()<i) return 0;
	return text_size[i];
}

polygon memo::getRect()
{
	vec2 size;

	int max=0;
	for(int i=0;i<text.size();i++) //i*3*size+i*size
		if(text[i].length()*3*text_size[i]+text[i].length()*text_size[i]>max) max=text[i].length()*3*text_size[i]+text[i].length()*text_size[i];
	size.x=max;
	size.y=0;
	for(int i=0;i<text_size.size();i++)
		size.y+=6*text_size[i];

	polygon rect;
	rect.setVertexCount(4);
	rect.setVertex(0, vec2(0.0, 0.0));
	rect.setVertex(1, vec2(size.x, 0.0));
	rect.setVertex(2, vec2(size.x, size.y));
	rect.setVertex(3, vec2(0.0, size.y));
	rect.setPosition(vec2(x,y));

	return rect;
}

void memo::setSize(vec2 s) { size=s; }

vec2 memo::getSize() { return size; }

float memo::getHeightToLine(int line)
{
	float size;
	size=0;
	for(int i=0;i<line;i++)
		size+=6*text_size[i];

	return size;
}

memo::~memo() {}


gui::gui() {}

std::map<std::string, button> *gui::getButtons() { return &buttons; }

void gui::addButton(std::string button_name, bool checkbox, float pos_x, float pos_y, float width, float height)
{
	buttons.insert(std::pair<std::string, button>(button_name, button()));

	polygon p;
	p.setVertexCount(4);
	p.setVertex(0, vec2(0.0, 0.0));
	p.setVertex(1, vec2(width, 0.0));
	p.setVertex(2, vec2(width, height));
	p.setVertex(3, vec2(0.0, height));
	p.setOrigin(vec2(0.0, 0.0));
	p.setPosition(vec2(pos_x, pos_y));

	buttons[button_name].create(p, checkbox);
}

void gui::setTextToButton(std::string button_name, std::string text, int text_size)
{
	if(buttons.find(button_name)!=buttons.end())
	{
		buttons[button_name].setCaption(text);
		buttons[button_name].setTextSize(text_size);
	}
}

void gui::deleteButton(std::string button_name)
{
	buttons.erase(button_name);
}

void gui::update(float mouse_x, float mouse_y, bool mouse_click)
{
	for(std::map<std::string, button>::iterator it=buttons.begin(); it!=buttons.end(); it++)
		it->second.update(vec2(mouse_x, mouse_y), mouse_click);
}

bool gui::isButtonPressed(std::string button_name)
{
	if(buttons.find(button_name)==buttons.end()) return false;
	return buttons[button_name].isPressed();
}

bool gui::isButtonChecked(std::string button_name)
{
	if(buttons.find(button_name)==buttons.end()) return false;
	return buttons[button_name].isChecked();
}

void gui::setButtonDelay(std::string button_name, float delay)
{
	if(buttons.find(button_name)!=buttons.end())
	{
		buttons[button_name].setDelay(delay);
	}
}

std::map<std::string, memo> *gui::getMemos() { return &memos; }

void gui::addMemo(std::string memo_name, float x, float y, float width, float height)
{
	memos.insert(std::pair<std::string, memo>(memo_name, memo()));
	memos[memo_name].setPosition(x,y);
	memos[memo_name].setSize(vec2(width, height));
}

void gui::addLineToMemo(std::string memo_name, std::string line, int text_size)
{
	if(memos.find(memo_name)!=memos.end())
		memos[memo_name].addLine(line, text_size);
}

void gui::clearMemo(std::string memo_name)
{
	if(memos.find(memo_name)!=memos.end())
		memos[memo_name].clear();
}

void gui::clear()
{
	memos.clear();
	buttons.clear();
}

gui::~gui() {}