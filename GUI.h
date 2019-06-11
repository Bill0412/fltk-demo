#ifndef __GUI_H
#define __GUI_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int w{Fl::w()/2}, h{Fl::h()};
enum typeChess {empty, black, white};
enum GameStages {INITIAL_PAGE, SELECT_PAGE, AI_RIVAL_PAGE, HUMAN_RIVAL_PAGE, GAME_OVER_PAGE};

// This is a constant for development purpose
const GameStages InitialStage = HUMAN_RIVAL_PAGE;
// const GameStages InitialStage = GAME_OVER_PAGE;

#include "Point.h"
#include "Shape.h"
#include "Line.h"
#include "Circle.h"
#include "Text.h"
#include "Windows.h"
#include "Board.h"

#endif