#ifndef MOVEGENERATION_HPP
#define MOVEGENERATION_HPP

enum Colours {
    white = 0,
    black = 1
};

class MoveGeneration{
    public:
    //pawn_attacks table (a precalculated attack table), [side][square]
    unsigned long long pawn_attacks[2][64];

    //what pawn is attacking (square), and which side will move
    unsigned long long mask_pawn_attacks(int square, int side);


};
#endif