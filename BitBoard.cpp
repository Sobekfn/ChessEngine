#include <iostream>
#include <array>
#include <intrin.h>
#include <string>
#include <unordered_map>
#pragma intrinsic(_BitScanForward64)

//Bitboard Code
enum PieceType{
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
    BLACK_PAWNS = 11
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



//Bitboard Class

class BitBoard {
public:
    std::array<unsigned long long, 12> boards;
    BitBoard() {
        for (int i = 0; i < 12; ++i) {
            boards[i] = 0ULL;
    }
    }
    void SetGame(){
        boards[WHITE_KING] = 1ULL << e1;
        boards[WHITE_QUEEN] = 1ULL << d1;
        boards[WHITE_BISHOPS] = (1ULL << c1) | (1ULL << f1); 
        boards[WHITE_KNIGHTS] = (1ULL << b1) | (1ULL << g1);
        boards[WHITE_ROOKS] = (1ULL << a1) | (1ULL << h1);
        for(int i = 8; i < 16; i++){
            boards[WHITE_PAWNS] = boards[WHITE_PAWNS] | (1ULL << i);
        }

        boards[BLACK_KING] = 1ULL << e8;
        boards[BLACK_QUEEN] = 1ULL << d8;
        boards[BLACK_BISHOPS] = (1ULL << c8) | (1ULL << f8);
        boards[BLACK_KNIGHTS] = (1ULL << b8) | (1ULL << g8);
        boards[BLACK_ROOKS] = (1ULL << a8) | (1ULL << h8);
        for(int i = 48; i < 56; i++){
            boards[BLACK_PAWNS] = boards[BLACK_PAWNS] | (1ULL << i);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const BitBoard& bb);

};

std::ostream& operator<<(std::ostream& os, const BitBoard& bb){
    char boardrep[64];
    for (int i = 0; i < 64; i++){
        boardrep[i] = 'o';
    }


    //needed for printing board
    std::unordered_map<int, char> conversions;
    conversions[0] = 'K';
    conversions[1] = 'Q';
    conversions[2] = 'B';
    conversions[3] = 'N';
    conversions[4] = 'R';
    conversions[5] = 'P';
    conversions[6] = 'k';
    conversions[7] = 'q';
    conversions[8] = 'b';
    conversions[9] = 'n';
    conversions[10] = 'r';
    conversions[11] = 'p';



    std::array<unsigned long long, 12> temp_boards = bb.boards;

    for(int i = 0; i < 12; i++){
        while(temp_boards[i] != 0){
            unsigned long index;
            unsigned char found = _BitScanForward64(&index, temp_boards[i]);
            
            if(found){
                boardrep[static_cast<int>(index)] = conversions[i];
                temp_boards[i] &= temp_boards[i] - 1;
            }
            }
    
    }
    
    for (int i = 63; i > -1; i--){
        std::cout << boardrep[i] << " ";

        if (i % 8 == 0){
            std::cout << "\n";
        }
    } 
    return os;
}

int main(){
    BitBoard bb;
    bb.SetGame();
    std::cout << bb;
}