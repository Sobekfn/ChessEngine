#include <iostream>
#include <array>
#include <intrin.h>
#include <string>
#include <unordered_map>
#include "BitBoard.hpp"
#include "MoveGeneration.hpp"
#pragma intrinsic(_BitScanForward64)

//pawn attacks table
unsigned long long MoveGeneration::mask_pawn_attacks(int square, int side){
    unsigned long long attacks = 0ULL;
    unsigned long long bitboard = 0ULL;

    bitboard |= (1ULL << square);

    if(side){ //if black to move

    }
    else{ //if white to move

    }

    return attacks;
}