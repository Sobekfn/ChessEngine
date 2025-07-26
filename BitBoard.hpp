#ifndef BITBOARD_HPP
#define BITBOARD_HPP

#include <array>
#include <iostream>

enum PieceType {
    WHITE_KING = 0,
    WHITE_QUEEN = 1,
    WHITE_BISHOPS = 2,
    WHITE_KNIGHTS = 3,
    WHITE_ROOKS = 4,
    WHITE_PAWNS = 5,
    BLACK_KING = 6,
    BLACK_QUEEN = 7,
    BLACK_BISHOPS = 8,
    BLACK_KNIGHTS = 9,
    BLACK_ROOKS = 10,
    BLACK_PAWNS = 11,
    WHITE = 12,
    BLACK = 13
};

enum Square {
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8
};

void print_board(unsigned long long bitboard);
void set_bit(unsigned long long& board, int square);
bool get_bit(unsigned long long& board, int square);
void pop_bit(unsigned long long& board, int square);


class BitBoard {
public:
    std::array<unsigned long long, 14> boards;
    BitBoard();
    void SetGame();
    friend std::ostream& operator<<(std::ostream& os, const BitBoard& bb);
};

#endif // BITBOARD_HPP
