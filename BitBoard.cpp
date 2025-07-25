#include <iostream>
#include <array>
#include <intrin.h>
#include <string>
#include <unordered_map>
#pragma intrinsic(_BitScanForward64)


//enumeration of piecetypes
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

//enumeration of all the squares into integers
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
    //array holding all 12 bitboards which represent the gamestate
    std::array<unsigned long long, 12> boards;

    //All Ranks as bits (May be useful, idk)
    static const unsigned long long RANK_1 = 0x00000000000000FFULL;
    static const unsigned long long RANK_2 = 0x000000000000FF00ULL;
    static const unsigned long long RANK_3 = 0x0000000000FF0000ULL;
    static const unsigned long long RANK_4 = 0x00000000FF000000ULL;
    static const unsigned long long RANK_5 = 0x000000FF00000000ULL;
    static const unsigned long long RANK_6 = 0x0000FF0000000000ULL;
    static const unsigned long long RANK_7 = 0x00FF000000000000ULL;
    static const unsigned long long RANK_8 = 0xFF00000000000000ULL;

    //All files as bits (May be useful, idk)
    static const unsigned long long A_FILE = 0x0101010101010101ULL;
    static const unsigned long long B_FILE = 0x0202020202020202ULL;
    static const unsigned long long C_FILE = 0x0303030303030303ULL;
    static const unsigned long long D_FILE = 0x0404040404040404ULL;
    static const unsigned long long E_FILE = 0x0505050505050505ULL;
    static const unsigned long long F_FILE = 0x0606060606060606ULL;
    static const unsigned long long G_FILE = 0x0707070707070707ULL;
    static const unsigned long long H_FILE = 0x0808080808080808ULL;

    //constructor
    BitBoard() {
        for (int i = 0; i < 12; ++i) {
            boards[i] = 0ULL;
    }
    }

    //sets game to default position. I think I will eventually switch to Fen, but idk when
    void SetGame(){
        set_PieceBit(WHITE_KING, e1);
        set_PieceBit(WHITE_QUEEN, d1);
        set_PieceBit(WHITE_BISHOPS, c1);
        set_PieceBit(WHITE_BISHOPS, f1);
        set_PieceBit(WHITE_KNIGHTS, b1);
        set_PieceBit(WHITE_KNIGHTS, g1);
        set_PieceBit(WHITE_ROOKS, a1);
        set_PieceBit(WHITE_ROOKS, h1);
        for(int i = 8; i < 16; i++){
            set_PieceBit(WHITE_PAWNS, i);
        }
        set_PieceBit(BLACK_KING, e8);
        set_PieceBit(BLACK_QUEEN, d8);
        set_PieceBit(BLACK_BISHOPS, c8);
        set_PieceBit(BLACK_BISHOPS, f8);
        set_PieceBit(BLACK_KNIGHTS, b8);
        set_PieceBit(BLACK_KNIGHTS, g8);
        set_PieceBit(BLACK_ROOKS, a8);
        set_PieceBit(BLACK_ROOKS, h8);
        for(int i = 48; i < 56; i++){
            set_PieceBit(BLACK_PAWNS, i);
        }
    }

    //sets a bit to 1
    void set_PieceBit(PieceType piece, int square){
        boards[piece] |= (1ULL << square);
    }

    //checks if a piece of a given type exists on a square
    bool get_PieceBit(PieceType piece, int square){
        return boards[piece] & (1ULL << square);
    }


    //removes a piece of a given type on a square
    void pop_PieceBit(PieceType piece, int square){
            boards[piece] &= ~(1ULL << square);
    }

    //for printing
    friend std::ostream& operator<<(std::ostream& os, const BitBoard& bb);

};


//adding compatibility for printing for my class
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



//main function
int main(){
    BitBoard bb;
    bb.SetGame();
    std::cout << bb;
    return 0;
}