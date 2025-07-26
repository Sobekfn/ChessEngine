// main.cpp
#include <iostream>
#include "bitboard.hpp"
#include "MoveGeneration.hpp"

int main() {
    BitBoard bb;
    bb.SetGame();
    std::cout << bb;
    return 0;
}