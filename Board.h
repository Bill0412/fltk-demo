//
// Created by Fenghe Xu on 2019-06-11.
//

#ifndef RENJU_BOARD_H
#define RENJU_BOARD_H
#include "GUI.h"

class Board: public Shape
        {
    private:
        int line_width, line_color;
        typeChess* board; // 0 for black, 1 for white
        int numCol, numRow;
        vector<Line*> lines;
        int title_placeholder, box_edge;
        vector<Circle*> chesses;
        int chessRadius;

        typeChess getBoard(int row, int col)
        {
            return board[row * numCol + col];
        }

        void setBoard(int row, int col, typeChess type)
        {
            board[row * numCol + col] = type;

            if(type == empty) {
                return;
            }
            // set graphically
            int color = FL_BLACK;
            if (type == white) {
                color = FL_WHITE;
            }
            Point pos = *getChessCord(row, col);
            chesses.push_back(new Circle(pos, chessRadius, 1, color, color));

            // remove chess(set empty)
            // no need to support
        }

        Point* getChessCord(int row, int col)
        {
            return new Point((col + 1) * box_edge, title_placeholder + box_edge * (row + 1));
        }

        void init_board(int nRow, int nCol)
        {
            // graphical board

            int shorter = (w > h) ? h : w;
            box_edge = shorter * 2 / (3 * nRow);
            chessRadius = box_edge / 4;
            title_placeholder = h / 8;
            // rows
            for(int i = 0; i < nRow; i++) {
                int left = box_edge;
                int right = nCol * box_edge;
                int horizontal = (i + 1) * box_edge + title_placeholder;
                lines.push_back(new Line(Point(left, horizontal), Point(right, horizontal), 3, FL_BLACK));
            }

            // columns
            for(int i = 0; i < nCol; i++) {
                int top = box_edge + title_placeholder;
                int bottom = top + (nRow - 1) * box_edge;
                int vertical = (i + 1) * box_edge;
                lines.push_back(new Line(Point(vertical , top), Point(vertical, bottom), 3, FL_BLACK));
            }

            // inside representation
            board = new typeChess[nRow * nCol];
            for(int i = 0; i < nRow; i++) {
                for(int j = 0; j < nCol; j++) {
                    setBoard(i, j, empty);
                }
            }
        }

    public:

        Board(int numRow, int numCol)
            :
            line_width(1),
            line_color(FL_BLACK),
            numCol(numCol),
            numRow(numRow),
            Shape(1, FL_BLACK, 0)
            {
            init_board(numRow, numCol);
        }

        ~Board()
        {
            for(int i = 0; i < lines.size(); i++)
                delete lines[i];
        }


    void draw() {
            // draw lines
        for(int i = 0; i < lines.size(); i++)
            lines[i]->draw();

        for(int i = 0; i < chesses.size(); i++)
            chesses[i]->draw();


    }

};


#endif //RENJU_BOARD_H
