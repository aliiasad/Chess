#ifndef KNIGHT_H
#define KNIGHT_H

# include "Enums.h"
# include "Move.h"
#include "Board.h"


class Knight {
    private:
        PieceColor color;
    public:
        Knight(PieceColor);

        // getter
        PieceColor getColor() const;

        // move handling
        Move* getLegalMoves(int, int, const Board&, int&);
};

inline Knight :: Knight(PieceColor color) {
    this->color = color;
} 

inline PieceColor Knight :: getColor()  const {
    return color;
}

inline Move* Knight :: getLegalMoves(int row, int col, const Board& board, int& count)    {
    // max moves are 8
    //(-2,-1), (-2,+1)
    //(-1,-2), (-1,+2)
    //(+1,-2), (+1,+2)
    //(+2,-1), (+2,+1)

    Move* temp = new Move [8];
    count = 0;

    int rowOffset[] = {-1, -2, -2, -1 , 1, 2, 2, 1};
    int colOffset[] = {-2, -1, 1, -2, -1, 1, 1, 2};

    for (int i = 0; i < 8; i++) {
        int newRow = row + rowOffset[i];
        int newCol = col + colOffset[i];

        if (newRow < 0 || newRow > 7 || newCol < 0 || newCol > 7) continue;

        const Cell& target = board.getCell(newRow, newCol);

        if (target.getOccupied() && target.getColor() == color) continue;

        // valid move
        temp[count].setRow(newRow);
        temp[count].setCol(newCol);
        count++;
    }
    Move* moves = new Move[count];
    for (int i = 0; i < count; i++)
        moves[i] = temp[i];

    delete[] temp;
    return moves;
}

#endif