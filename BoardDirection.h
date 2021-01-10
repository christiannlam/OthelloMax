#pragma once
#include <iostream>
#include <array>

class BoardDirection {
private:
    char mRowDir;
    char mColDir;

public:
    BoardDirection();
    BoardDirection(char rowDir, char colDir);

    inline char getRowChange() const { return  mRowDir; }
    inline char getColChange() const { return  mColDir; }

    static std::array<BoardDirection, 8> CARDINAL_DIRECTIONS;

};