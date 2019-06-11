#include "GUI.h"
#include "Board.h"

struct Windows : Fl_Double_Window {
	Windows(Point topleft, int width, int height, string title)
	:
	board(new Board(10, 10)),
	stage(InitialStage),
	prevStage(InitialStage),
	width(width),
	height(height),
	Fl_Double_Window(topleft.x, topleft.y, width, height, title.c_str()) {
		color(FL_DARK_GREEN);
		show();
	}
	~Windows()
	{
		delete board;
	}
	vector<Shape*> shapes;
	Board *board;
	int width, height;
	void attach(Shape& s) { shapes.push_back(&s); }
	void draw() {
		Fl_Double_Window::draw();
//		for(int i=0;i<shapes.size();i++)
//			shapes[i]->draw();

		switch(stage) {
			case HUMAN_RIVAL_PAGE:
				board->draw();
				break;
			case GAME_OVER_PAGE:
				onRenderGameOverPage();
				break;
		}

	}

	int handle(int event) {
		switch(stage) {
			case HUMAN_RIVAL_PAGE:
				onHandleHumanRivalPage(event);
				break;
			case GAME_OVER_PAGE:
				onHandleGameOverPage(event);
				break;

		}
	}

private:
	GameStages stage, prevStage;
	void onHandleHumanRivalPage(int event)
	{
		prevStage = stage;
		switch(event) {
			case FL_PUSH:
				// std::cout << "FL_PUSH" << std::endl;
				break;
			case FL_RELEASE:
				// std::cout << "FL_RELEASE" << std::endl;
				// only need to judge when it releases
				// std::cout << "(" << Fl::event_x() << "," << Fl::event_y() << ")\n";
				stage = board->tryPutChess(Fl::event_x(), Fl::event_y());
				break;
			default:
				break;
		}
		if(stage != prevStage) {
			Fl:redraw();
		}
	}

	void onHandleGameOverPage(int event)
	{
		return;
	}

	void onRenderGameOverPage()
	{
		Text text(Point(height/3, width/3), 50, 50, 2, "Game Over");
		text.draw();
	}
};
