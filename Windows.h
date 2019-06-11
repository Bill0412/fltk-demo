#include "GUI.h"
#include "Board.h"


struct Windows : Fl_Double_Window {
	Windows(Point topleft, int width, int height, string title)
	:
	board(new Board(10, 10)),
	width(width),
	height(height),

	Fl_Double_Window(topleft.x, topleft.y, width, height, title.c_str())
	{
		// init window background
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

		switch(GameStage) {
			case INITIAL_PAGE:
				onRenderInitialPage();
				break;
			case HUMAN_RIVAL_PAGE:
				board->draw();
				break;
			case GAME_OVER_PAGE:
				onRenderGameOverPage();
				break;
		}

	}

	int handle(int event) {
		PrevGameStage = GameStage;
		switch(GameStage) {
			case INITIAL_PAGE:
				onHandleInitialPage(event);
				break;
			case HUMAN_RIVAL_PAGE:
				onHandleHumanRivalPage(event);
				break;
			case GAME_OVER_PAGE:
				onHandleGameOverPage(event);
				break;
		}
		if(PrevGameStage != GameStage) {
			Fl:redraw();
		}
	}

private:
	void onHandleInitialPage(int event)
	{
		switch(event)
		{
			case FL_RELEASE:
				// may be modified to login page later
				setStage(HUMAN_RIVAL_PAGE);
				break;
			default:
				break;
		}
	}

	void onHandleHumanRivalPage(int event)
	{
		switch(event) {
			case FL_PUSH:
				// std::cout << "FL_PUSH" << std::endl;
				break;
			case FL_RELEASE:
				// std::cout << "FL_RELEASE" << std::endl;
				// only need to judge when it releases
				// std::cout << "(" << Fl::event_x() << "," << Fl::event_y() << ")\n";
				board->tryPutChess(Fl::event_x(), Fl::event_y());
				break;
			default:
				break;
		}
	}

	void onHandleGameOverPage(int event)
	{
		return;
	}

	void onRenderInitialPage()
	{
		Text text(Point(width / 3, height / 3), 1, 100, FL_WHITE, "五子棋");
		Text text1(Point(width / 3 + 10, height / 3 + 60), 1, 25, FL_WHITE, "单击任何区域以开始游戏");
		text.draw();
		text1.draw();
	}

	void onRenderGameOverPage()
	{
		Text text(Point(width / 8, height / 3), 1, 100, FL_WHITE, "Game Over");

		Text text1(Point(width / 8 + 100 , height / 3 + 150), 1, 50, FL_WHITE, string(((board->getTurn() == 2)? "WHITE" : "BLACK")) + " " + string( "WINS!"));
		text.draw();
		text1.draw();
	}


};
