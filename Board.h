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

        typeChess getBoard(int row, int col)
        {
            return board[row * numCol + col];
        }

        void setBoard(int row, int col, typeChess type)
        {
            board[row * numCol + col] = type;
        }

        void init_board(int nRow, int nCol)
        {
            // inside representation
            board = new typeChess[nRow * nCol];
            for(int i = 0; i < nRow; i++) {
                for(int j = 0; j < nCol; j++) {
                    setBoard(nRow, nCol, empty);
                }
            }

            // graphical board

            int shorter = (w > h) ? h : w;
            int box_edge = shorter * 2 / (3 * nRow);
            // rows
            for(int i = 0; i < nRow; i++) {
                int left = box_edge;
                int right = nCol * box_edge;
                lines.push_back(new Line(Point(left, (i + 1) * box_edge), Point(right, (i + 1) * box_edge), 3, FL_BLACK));
            }

            // columns
            for(int i = 0; i < nCol; i++) {
                int top = box_edge;
                int bottom = nRow * box_edge;
                lines.push_back(new Line(Point((i + 1) * box_edge , top), Point((i + 1) * box_edge, bottom), 3, FL_BLACK));
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
        for(int i=0;i<lines.size();i++)
            lines[i]->draw();
    }

};


#endif //RENJU_BOARD_H
