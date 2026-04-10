#ifndef ROOK_H
#define ROOK_H

# include "Enums.h"
# include "Board.h"
# include "Move.h"

class Rook {
    private:
        PieceColor color;
    public:
        Rook(PieceColor);

        // getter
        PieceColor getColor() const;

        // move handling and validation
        Move* getLegalMoves(int, int, const Board&, int&);
};

inline Rook :: Rook(PieceColor color)    {
    this->color = color;
}

inline PieceColor Rook :: getColor()   const {
    return color;
}

inline Move* Rook :: getLegalMoves(int row, int col, const Board& board, int& count)    {
    // max moves for rook are 7 + 7
    Move* temp = new Move [14];
    count = 0;

    int rowOffset[] = {-1, 0, 0, 1};
    int colOffset[] = {0, -1, 1, 0};

    for (int i = 0; i < 4; i++) {
        int newRow = row + rowOffset[i];
        int newCol = col + colOffset[i];

        // keep traversing untill hit by dead end, enemy piece or own piece
        while (newRow >= 0 && newRow <= 7 && newCol >= 0 && newCol <= 7)    {

            const Cell& target = board.getCell(newRow, newCol);

            if (target.getOccupied())   {
                if (target.getColor() != color) {// enemy piece
                    temp[count].setRow(newRow);
                    temp[count].setCol(newCol);
                    count++;
                    break;
                }   else {  // own piece
                    break;
                }
            }
            // empty square..valid move, keep sliding
            temp[count].setRow(newRow);
            temp[count].setCol(newCol);
            count++;

            newRow += rowOffset[i];
            newCol += colOffset[i];
        }
    }

    Move* moves = new Move [count];
    for (int i = 0; i < count; i++) {
        moves[i] = temp[i];
    }

    delete[] temp;
    return moves;
}

#endif