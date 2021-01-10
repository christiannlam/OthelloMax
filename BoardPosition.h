#pragma once
#include <string>
#include <vector>
#include "BoardDirection.h"
class BoardPosition {

private:
    char mRow;
    char mCol;

public:
    BoardPosition();
    BoardPosition(char row, char col);

    inline char getRow() const {
        return mRow;
    };
    inline char getCol() const {
        return mCol;
    };

    operator std::string() const;

    friend std::istream& operator>>(std::istream& lhs, BoardPosition& rhs);

    bool operator==(BoardPosition rhs);

    bool operator<(BoardPosition rhs);

    BoardPosition operator+(BoardDirection dir);

    bool InBounds(int boardSize);

    bool InBounds(int rows, int columns);

    static std::vector<BoardPosition> GetRectangularPositions(int rows, int columns);


};

std::ostream& operator<<(std::ostream& lhs, BoardPosition rhs);
