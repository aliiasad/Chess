#ifndef BOARD_H
#define BOARD_H

# include "Cell.h"
# include <SFML/Graphics.hpp>
# include "Enums.h"
using namespace sf;

const int TILE_SIZE = 80; // 80 px

class MoveValidator;

class Board {
    private:
        Cell grid[8][8];
        int selectedRow;
        int selectedCol;
        bool pieceSelected;

        // graphics
        void drawPieces(RenderWindow&);
        void drawTiles(RenderWindow&);
    public:
        Board();

        // input reading and graphics managing
        void handleClick(int, int);
        void movePiece(int, int, int, int);
        void draw(RenderWindow&);

        // board initializer
        void init();

        // getters
        Cell& getCell(int, int);
        const Cell& getCell(int, int) const;
        int getSelectedRow() const;
        int getSelectedCol() const;
        bool getSelectedPiece() const;

        // friend class
        friend class MoveValidator;

        // back to deselected state
        void deselectPiece();
};

// using member initializer list since we have to init board
inline Board :: Board() : selectedRow(-1), selectedCol(-1), pieceSelected(false)   {
    init();
}

inline void Board :: handleClick(int mouseX, int mouseY)  {
    int row = mouseY / TILE_SIZE;
    int col = mouseX / TILE_SIZE;

    // click anywhere other than cells
    if (row < 0 || row > 7 || col < 0 || col > 7) return;

    if (!pieceSelected) {
        if (grid[row][col].getOccupied())    {
            selectedCol = col;
            selectedRow = row;
            pieceSelected = true;
        }
    } else { // validate second or multiple clicks
        selectedCol = col;
        selectedRow = row;
    }
}

inline void Board :: movePiece(int fromCol, int fromRow, int toCol, int toRow)    {
    grid[toCol][toRow] = grid[fromCol][fromRow];
    grid[fromCol][fromRow].clear();
    return;
}

inline void Board :: draw(RenderWindow& window) {
    drawTiles(window);
    drawPieces(window);
    return;
}

inline Cell& Board :: getCell(int row, int col)  {
    return grid[row][col];
}

inline const Cell& Board :: getCell(int row, int col) const {
    return grid[row][col];
}

inline int Board :: getSelectedRow() const   {
    return selectedRow;
}

inline int Board :: getSelectedCol() const  {
    return selectedCol;
}

inline bool Board :: getSelectedPiece() const    {
    return pieceSelected;
}

inline void Board::deselectPiece() {
    pieceSelected = false;
    selectedRow   = -1;
    selectedCol   = -1;
}

inline void Board :: init() {
    // setting up black pieces
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            grid[r][c].clear();
        }
    }

    // back rank black
    grid[0][0].setPiece(ROOK).setColor(BLACK).setOccupied(true);
    grid[0][1].setPiece(KNIGHT).setColor(BLACK).setOccupied(true);
    grid[0][2].setPiece(BISHOP).setColor(BLACK).setOccupied(true);
    grid[0][3].setPiece(QUEEN).setColor(BLACK).setOccupied(true);
    grid[0][4].setPiece(KING).setColor(BLACK).setOccupied(true);
    grid[0][5].setPiece(BISHOP).setColor(BLACK).setOccupied(true);
    grid[0][6].setPiece(KNIGHT).setColor(BLACK).setOccupied(true);
    grid[0][7].setPiece(ROOK).setColor(BLACK).setOccupied(true);

    // pawn row black
    for (int c = 0; c < 8; c++) {
        grid[1][c].setPiece(PAWN).setColor(BLACK).setOccupied(true);
    }

    // back rank white
    grid[7][0].setPiece(ROOK).setColor(WHITE).setOccupied(true);
    grid[7][1].setPiece(KNIGHT).setColor(WHITE).setOccupied(true);
    grid[7][2].setPiece(BISHOP).setColor(WHITE).setOccupied(true);
    grid[7][3].setPiece(QUEEN).setColor(WHITE).setOccupied(true);
    grid[7][4].setPiece(KING).setColor(WHITE).setOccupied(true);
    grid[7][5].setPiece(BISHOP).setColor(WHITE).setOccupied(true);
    grid[7][6].setPiece(KNIGHT).setColor(WHITE).setOccupied(true);
    grid[7][7].setPiece(ROOK).setColor(WHITE).setOccupied(true);

    // pawn row white
    for (int c = 0; c < 8; c++) {
        grid[6][c].setPiece(PAWN).setColor(WHITE).setOccupied(true);
    }
    return;
}

inline void Board :: drawTiles(RenderWindow& window)    {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            RectangleShape tile(Vector2f(TILE_SIZE, TILE_SIZE));
            tile.setPosition(Vector2f(c * TILE_SIZE, r * TILE_SIZE));
            // since all even tiles are white, set (r + c) % 2 light/white

            if ((r + c) % 2 == 0)   {
                tile.setFillColor(Color(240, 217, 181));
            }   else {
                tile.setFillColor(Color(181, 136, 99));
            }

            // highlight selected tile
            if (pieceSelected && c == selectedCol && r == selectedRow)  {
                tile.setFillColor(Color(100, 200, 100));
            }

            window.draw(tile);
        }
    }
}

inline void Board :: drawPieces(RenderWindow& window)   {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (!grid[r][c].getOccupied()) continue;

            sf::CircleShape piece(30.f);
            piece.setPosition(sf::Vector2f(c * TILE_SIZE + 10, r * TILE_SIZE + 10));

            piece.setFillColor(grid[r][c].getColor() == WHITE
                ? sf::Color(255, 255, 255)
                : sf::Color(40,  40,  40));

            window.draw(piece);
        }
    }
}

#endif