// main.cpp
#include <iostream>
#include "bitboard.hpp"
#include "MoveGeneration.hpp"

int main() {
    /*BitBoard bb;
    bb.SetGame();
    std::cout << bb;
    print_board(bb.boards[1]);*/

    MoveGeneration mover;

    print_board(mover.mask_pawn_attacks(e4, white));
    return 0;
}