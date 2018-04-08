#ifndef RENDERER_HPP
#define RENDERER_HPP
#include "lake.hpp"
#include "gui.hpp"

void drawGUI(gui*);

void drawButtonDefault(button*);

void drawButtonPressed(button*);

void drawButtonChecked(button*);

void drawMemo(memo*);

void drawLake(lake*);

void drawWhater(vec2 size);

void drawFood();

void drawFish();

#endif