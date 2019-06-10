#include "GUI.h"
#include "Board.h"

struct Windows : Fl_Double_Window {
	Windows(Point topleft, int width, int height, string title)
	:
	board(new Board(10, 10)),
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
	void attach(Shape& s) { shapes.push_back(&s); }
	void draw() {
		Fl_Double_Window::draw();
		for(int i=0;i<shapes.size();i++)
			shapes[i]->draw();
		board->draw();
	}

	int handle(int event) {
		switch(event) {
			case FL_PUSH:
				std::cout << "FL_PUSH" << std::endl;
				break;
			case FL_RELEASE:
				std::cout << "FL_RELEASE" << std::endl;
				// only need to judge when it releases
				std::cout << "(" << Fl::event_x() << "," << Fl::event_y() << ")\n";
				board->tryPutChess(Fl::event_x(), Fl::event_y());
				break;
			default:
				break;

		}
	}
};
