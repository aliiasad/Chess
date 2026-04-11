#ifndef PAWN_H
#define PAWN_H

# include "Enums.h"
# include "Board.h"
# include "Move.h"

class Pawn {
    private:
        PieceColor color;
    public:
        Pawn(PieceColor);

        // getter
        PieceColor getColor() const;

        // legal move handling
        Move* getLegalMove(int, int, const Board&, int&);
};

inline Pawn :: Pawn(PieceColor color)   {
    this->color = color;
}

inline PieceColor Pawn :: getColor() const {
    return color;
}

inline Move* Pawn :: getLegalMove(int row, int col, const Board& board, int& count) {
    Move* temp = new Move [4];
    count = 0;

    int direction = (color == WHITE) ? -1 : 1;
    int startRow = (color == WHITE) ? 6 : 1;

    int oneForward = row + direction;
    if (oneForward >= 0 && oneForward <= 7) {
        const Cell& target = board.getCell(oneForward, col);
        if (!target.getOccupied())  {
            temp[count].setRow(oneForward);
            temp[count].setCol(col);
            count++;
        }

        int twoForward = row + 2 * direction;
        if (row == startRow && twoForward >= 0 && twoForward <= 7)  {
            const Cell& target2 = board.getCell(twoForward, col);
            if (!target2.getOccupied())  {
                temp[count].setRow(twoForward);
                temp[count].setCol(col);
                count++;
            }
        }
    }

    int captureCols[] = {col - 1, col + 1};
    for (int i = 0; i < 2; i++) {
        int captureRow = row + direction;
        int captureCol = col + captureCols[i];

        if (captureRow >= 0 && captureCol >= 0 && captureCol <=7 && captureRow <= 7)    continue;

        const Cell& target = board.getCell(captureRow, captureCol);
        if (target.getOccupied() && target.getColor() != color) {
            temp[count].setRow(captureRow);
            temp[count].setCol(captureCol);
            count++;
        }
    }

    Move* moves = new Move[count];
    for (int i = 0; i < count; i++)
        moves[i] = temp[i];

    delete[] temp;
    return moves;
}

#endif