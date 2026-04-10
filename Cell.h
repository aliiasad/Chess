#ifndef CELL_H
#define CELL_H

# include "Enums.h"

class Cell  {
    private:
        PieceType piece;
        PieceColor color;
        bool occupied;
    public:
        Cell();

        // setters
        void setPiece(PieceType);
        void setColor(PieceColor);
        void setOccupied(bool);

        // getters
        PieceColor getColor() const;
        PieceType getPiece() const;
        bool getOccupied() const;

        // functions and overloading
        void clear();
        bool operator==(const Cell&);
};

inline Cell :: Cell()  {
    this->piece = NONE;
    this->color = EMPTY;
    this->occupied = false;
}

inline void Cell :: setPiece(PieceType piece)    {
    this->piece = piece;
    return;
}

inline void Cell :: setColor(PieceColor color) {
    this->color = color;
    return;
}

inline void Cell :: setOccupied(bool occupied) {
    this->occupied = occupied;
    return;
}

inline PieceColor Cell :: getColor()   const {
    return color;
}

inline PieceType Cell :: getPiece()  const {
    return piece;
}

inline bool Cell :: getOccupied()  const {
    return occupied;
}

inline void Cell :: clear()    {
    piece = NONE;
    color = EMPTY;
    occupied = false;
}

inline bool Cell :: operator==(const Cell& dummy)  {
    return (this->color == dummy.color && this->piece == dummy.piece); 
}

#endif