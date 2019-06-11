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
    typeChess turn;
    GameStages stage;

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

    Point* getChessPos(int x, int y)
    {
        Point p1 = Point(x, y);
        for(int i = 0; i < numRow; i++) {
            for(int j = 0; j < numCol; j++) {
                Point p2 = *getChessCord(i, j);
                if(p1.getDistance(p2) < chessRadius) {
                    std::cout << "x: " << i << "\ty: " << j << std::endl;
                    return new Point(i, j);
                }
            }
        }

        return nullptr;
    }

    void flipTurn()
    {
        turn = (turn == black) ? white : black;
    }

    bool IsThePlayerWin(int i, int j)
    {
        typeChess chess = turn;
        int boardSize = numCol;

        // search left - right
        {
            int right, left;
            for (right = 0;  i + right + 1 < boardSize && getBoard(i + right + 1, j) == chess; right++);
            for (left = 0; (i - left - 1) >=0 && getBoard(i - left - 1, j) == chess; left++);
            if (left + right + 1 >= 5)
            {
                return true;
            }
        }

        // search rightTop - leftBottom
        {
            int rightTop, leftBottom;
            for (rightTop = 0; i + rightTop + 1 < boardSize && j - rightTop - 1 >= 0 && getBoard(rightTop + i + 1, j - rightTop - 1) == chess; rightTop++);
            for (leftBottom = 0; (i - leftBottom - 1) >=0 && (j + leftBottom + 1) < boardSize  && getBoard(i - leftBottom - 1, j + leftBottom + 1) == chess; leftBottom++);
            if (leftBottom + rightTop + 1>= 5)
            {
                return true;
            }
        }

        // search top-bottom
        {
            int top, bottom;
            for (top = 0; j - top - 1 >= 0 && getBoard(i, j - top - 1) == chess; top++);
            for (bottom = 0; (j + bottom + 1) < boardSize && getBoard(i, j + bottom + 1) == chess; bottom++);
            if (top + bottom + 1 >= 5)
            {
                return true;
            }
        }

        //search leftTop - rightBottom
        {
            int leftTop, rightBottom;
            for (leftTop = 0; i - leftTop - 1 >= 0 && j - leftTop - 1 >= 0 && getBoard(i - leftTop - 1, j - leftTop - 1) == chess; leftTop++);
            for (rightBottom = 0; (i + rightBottom + 1) < boardSize && (j + rightBottom + 1) < boardSize && getBoard(i + rightBottom + 1, j + rightBottom + 1) == chess; rightBottom++);
            if (leftTop + rightBottom + 1>= 5)
            {
                return true;
            }
        }
        return false;
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
    void setStage(GameStages s)
    {
        stage = s;
    }

    typeChess getTurn()
    {
        return turn;
    }

    Board(int numRow, int numCol)
        :
        line_width(1),
        line_color(FL_BLACK),
        numCol(numCol),
        numRow(numRow),
        Shape(1, FL_BLACK, 0),
        turn(white),
        stage(InitialStage)
        {
        init_board(numRow, numCol);
    }

    ~Board()
    {
        for(int i = 0; i < lines.size(); i++)
            delete lines[i];
    }

    GameStages tryPutChess(int x, int y)
    {
        Point* pos = getChessPos(x, y);
        std::cout << pos << std::endl;
        if(pos && getBoard(pos->x, pos->y) == empty) {
            setBoard(pos->x, pos->y, turn);\

            // check the game rule
            // if the one of the players wins, the game should end
            if(IsThePlayerWin(pos->x, pos->y)) {

                std::cout << ((turn == 2)? "white" : "black") << " wins!" << std::endl;
                return (stage = GAME_OVER_PAGE);
            }
            flipTurn();
        }
        Fl::redraw();

        return stage;
    }


void draw() {
        // draw lines
    for(int i = 0; i < lines.size(); i++)
        lines[i]->draw();
        // draw chesses
    for(int i = 0; i < chesses.size(); i++)
        chesses[i]->draw();
}

};


#endif //RENJU_BOARD_H
