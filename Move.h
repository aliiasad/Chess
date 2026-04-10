#ifndef MOVE_H
#define MOVE_H

class Move {
private:
    int row;
    int col;
public:
    Move();
    Move(int, int);

    // getters
    int getRow() const;
    int getCol() const;

    // setters
    void setRow(int);
    void setCol(int);

    bool operator==(const Move&);
};

inline Move::Move() {
    row = -1;
    col = -1;
}

inline Move :: Move(int row, int col)  {
    this->row = row;
    this->col = col;
}

inline int Move :: getRow() const { 
    return row; 
}

inline int Move::getCol() const { 
    return col; 
}

inline void Move :: setRow(int row) { 
    this->row = row;
    return;
}

inline void Move :: setCol(int col) { 
    this->col = col; 
    return;
}

inline bool Move::operator==(const Move& dummy) {
    return (this->row == dummy.row && this->col == dummy.col);
}

#endif