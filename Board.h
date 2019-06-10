//
// Created by Fenghe Xu on 2019-06-11.
//

#ifndef RENJU_BOARD_H
#define RENJU_BOARD_H
#include "GUI.h"
#include "Chess.h"

class Board: public Shape
        {
private:
    int line_width, line_color;
    Chess* board; // 0 for black, 1 for white
    int numCol, numRow;
    vector<Line*> lines;
    int box_edge, title_placeholder;

    Chess getChess(int row, int col)
    {
        return board[row * numCol + col];
    }

    void setChess(int row, int col, typeChess type)
    {
        board[row * numCol + col] = type;
    }

    void initBoard(int nRow, int nCol)
    {
        // inside representation
        points = new Points
        board = new Chess[nCol * nRow];
        for(int i = 0; i < nRow; i++) {
            for(int j = 0; j < nCol; j++) {
                setChess(nRow, nCol, empty);
            }
        }

        // graphical board

        int shorter = (w > h) ? h : w;
        box_edge = shorter * 2 / (3 * nRow);
        // rows
        title_placeholder = h / 8;
        for(int i = 0; i < nRow; i++) {
            int left = box_edge;
            int right = nCol * box_edge;
            int level = title_placeholder + (i + 1) * box_edge;
            lines.push_back(new Line(Point(left, level), Point(right, level), 3, FL_BLACK));
        }

        // columns
        for(int i = 0; i < nCol; i++) {
            int top = box_edge + title_placeholder;
            int bottom = top + (nRow - 1) * box_edge;
            int vertical = (i + 1) * box_edge;
            lines.push_back(new Line(Point(vertical , top), Point(vertical, bottom), 3, FL_BLACK));

            // get position info

            for(int j = 0; j < nRow; j++) {
                int horizontal = title_placeholder + (i + 1) * box_edge;

            }
        }

        for(int )
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
        initBoard(numRow, numCol);
    }

    ~Board()
    {
        for(int i = 0; i < lines.size(); i++)
            delete lines[i];
        delete [] board;
    }


void draw() {
    for(int i=0;i<lines.size();i++)
        lines[i]->draw();
}

};


#endif //RENJU_BOARD_H
