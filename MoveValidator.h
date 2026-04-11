#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H

#include "Enums.h"
#include "Move.h"
#include "Board.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

class MoveValidator {
public:
    MoveValidator();

    bool isLegal(int fromRow, int fromCol, int toRow, int toCol,
                 const Board& board, PieceColor currentColor);

    bool isInCheck(PieceColor color, const Board& board);
    bool isCheckmate(PieceColor color, Board& board);

private:
    // helpers
    bool moveExistsInList(Move* moves, int count, int toRow, int toCol);
    void findKing(PieceColor color, const Board& board, int& kingRow, int& kingCol);
};

inline MoveValidator::MoveValidator() {}

inline bool MoveValidator::moveExistsInList(Move* moves, int count, int toRow, int toCol) {
    for (int i = 0; i < count; i++) {
        if (moves[i].getRow() == toRow && moves[i].getCol() == toCol)
            return true;
    }
    return false;
}

inline void MoveValidator::findKing(PieceColor color, const Board& board, int& kingRow, int& kingCol) {
    kingRow = -1;
    kingCol = -1;
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            const Cell& cell = board.getCell(r, c);
            if (cell.getOccupied() &&
                cell.getPiece() == KING &&
                cell.getColor() == color) {
                kingRow = r;
                kingCol = c;
                return;
            }
        }
    }
}

inline bool MoveValidator::isLegal(int fromRow, int fromCol, int toRow, int toCol,
                                    const Board& board, PieceColor currentColor) {
    const Cell& from = board.getCell(fromRow, fromCol);

    // must be moving your own piece
    if (!from.getOccupied() || from.getColor() != currentColor) return false;

    int count = 0;
    Move* moves = nullptr;

    // call correct piece's getLegalMoves based on type
    switch (from.getPiece()) {
        case KING: {
            King k(currentColor);
            moves = k.getLegalMoves(fromRow, fromCol, board, count);
            break;
        }
        case QUEEN: {
            Queen q(currentColor);
            moves = q.getLegalMoves(fromRow, fromCol, board, count);
            break;
        }
        case ROOK: {
            Rook r(currentColor);
            moves = r.getLegalMoves(fromRow, fromCol, board, count);
            break;
        }
        case BISHOP: {
            Bishop b(currentColor);
            moves = b.getLegalMoves(fromRow, fromCol, board, count);
            break;
        }
        case KNIGHT: {
            Knight kn(currentColor);
            moves = kn.getLegalMoves(fromRow, fromCol, board, count);
            break;
        }
        case PAWN: {
            Pawn p(currentColor);
            moves = p.getLegalMoves(fromRow, fromCol, board, count);
            break;
        }
        default:
            return false;
    }

    bool legal = moveExistsInList(moves, count, toRow, toCol);
    delete[] moves;
    return legal;
}

inline bool MoveValidator::isInCheck(PieceColor color, const Board& board) {
    // find this color's king
    int kingRow, kingCol;
    findKing(color, board, kingRow, kingCol);
    if (kingRow == -1) return false;

    // enemy color
    PieceColor enemy = (color == WHITE) ? BLACK : WHITE;

    // check if any enemy piece can move to king's position
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            const Cell& cell = board.getCell(r, c);
            if (!cell.getOccupied() || cell.getColor() != enemy) continue;

            int count = 0;
            Move* moves = nullptr;

            switch (cell.getPiece()) {
                case KING:   { 
                    King k(enemy);    
                     moves = k.getLegalMoves(r, c, board, count);  
                     break; 
                }
                case QUEEN:  { 
                    Queen q(enemy);    
                    moves = q.getLegalMoves(r, c, board, count);  
                    break; 
                }
                case ROOK:   { 
                    Rook rk(enemy);    
                    moves = rk.getLegalMoves(r, c, board, count); 
                    break; 
                }
                case BISHOP: { 
                    Bishop b(enemy);   
                    moves = b.getLegalMoves(r, c, board, count);  
                    break; 
                }
                case KNIGHT: { 
                    Knight kn(enemy);  
                    moves = kn.getLegalMoves(r, c, board, count); 
                    break; 
                }
                case PAWN:   { 
                    Pawn p(enemy);     
                    moves = p.getLegalMoves(r, c, board, count);  
                    break; 
                }
                default: continue;
            }

            bool threatens = moveExistsInList(moves, count, kingRow, kingCol);
            delete[] moves;
            if (threatens) return true;
        }
    }
    return false;
}

inline bool MoveValidator::isCheckmate(PieceColor color, Board& board) {
    // not checkmate if not even in check
    if (!isInCheck(color, board)) return false;

    // try every possible move for every piece of this color
    // if any move gets us out of check → not checkmate
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            const Cell& cell = board.getCell(r, c);
            if (!cell.getOccupied() || cell.getColor() != color) continue;

            int count = 0;
            Move* moves = nullptr;

            switch (cell.getPiece()) {
                case KING:   { King k(color);    moves = k.getLegalMoves(r, c, board, count);  break; }
                case QUEEN:  { Queen q(color);   moves = q.getLegalMoves(r, c, board, count);  break; }
                case ROOK:   { Rook rk(color);   moves = rk.getLegalMoves(r, c, board, count); break; }
                case BISHOP: { Bishop b(color);  moves = b.getLegalMoves(r, c, board, count);  break; }
                case KNIGHT: { Knight kn(color); moves = kn.getLegalMoves(r, c, board, count); break; }
                case PAWN:   { Pawn p(color);    moves = p.getLegalMoves(r, c, board, count);  break; }
                default: continue;
            }

            // try each move on a temporary board copy
            for (int i = 0; i < count; i++) {
                int toRow = moves[i].getRow();
                int toCol = moves[i].getCol();

                // save destination cell state
                Cell savedDest = board.getCell(toRow, toCol);
                Cell savedSrc  = board.getCell(r, c);

                // make the move
                board.movePiece(r, c, toRow, toCol);

                // check if still in check after move
                bool stillInCheck = isInCheck(color, board);

                // undo the move
                board.getCell(r, c)         = savedSrc;
                board.getCell(toRow, toCol) = savedDest;

                if (!stillInCheck) {
                    delete[] moves;
                    return false;  // found a move that escapes check
                }
            }
            delete[] moves;
        }
    }
    return true;  // no move escapes check --> checkmate
}

#endif