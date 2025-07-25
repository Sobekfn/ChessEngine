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


//Move data Type

struct Move {
    Square from_square;
    Square to_square;
    PieceType moving_piece;
    PieceType captured_piece;

    



};



//Bitboard Class

class BitBoard {
public:
    std::array<unsigned long long, 12> boards;

    static const unsigned long long RANK_1 = 0x00000000000000FFULL;
    static const unsigned long long RANK_2 = 0x000000000000FF00ULL;
    static const unsigned long long RANK_3 = 0x0000000000FF0000ULL;
    static const unsigned long long RANK_4 = 0x00000000FF000000ULL;
    static const unsigned long long RANK_5 = 0x000000FF00000000ULL;
    static const unsigned long long RANK_6 = 0x0000FF0000000000ULL;
    static const unsigned long long RANK_7 = 0x00FF000000000000ULL;
    static const unsigned long long RANK_8 = 0xFF00000000000000ULL;


    static const unsigned long long A_FILE = 0x0101010101010101ULL;
    static const unsigned long long B_FILE = 0x0202020202020202ULL;
    static const unsigned long long C_FILE = 0x0303030303030303ULL;
    static const unsigned long long D_FILE = 0x0404040404040404ULL;
    static const unsigned long long E_FILE = 0x0505050505050505ULL;
    static const unsigned long long F_FILE = 0x0606060606060606ULL;
    static const unsigned long long G_FILE = 0x0707070707070707ULL;
    static const unsigned long long H_FILE = 0x0808080808080808ULL;

    BitBoard() {
        for (int i = 0; i < 12; ++i) {
            boards[i] = 0ULL;
    }
    }
    /*void SetGame(){
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
    }*/

    void SetGame(){
        set_bit(WHITE_KING, e1);
        set_bit(WHITE_QUEEN, d1);
        set_bit(WHITE_BISHOPS, c1);
        set_bit(WHITE_BISHOPS, f1);
        set_bit(WHITE_KNIGHTS, b1);
        set_bit(WHITE_KNIGHTS, g1);
        set_bit(WHITE_ROOKS, a1);
        set_bit(WHITE_ROOKS, h1);
        for(int i = 8; i < 16; i++){
            set_bit(WHITE_PAWNS, i);
        }
        set_bit(BLACK_KING, e8);
        set_bit(BLACK_QUEEN, d8);
        set_bit(BLACK_BISHOPS, c8);
        set_bit(BLACK_BISHOPS, f8);
        set_bit(BLACK_KNIGHTS, b8);
        set_bit(BLACK_KNIGHTS, g8);
        set_bit(BLACK_ROOKS, a8);
        set_bit(BLACK_ROOKS, h8);
        for(int i = 48; i < 56; i++){
            set_bit(BLACK_PAWNS, i);
        }
    }

    void set_bit(PieceType piece, int square){
        boards[piece] ^= (1ULL << square);
    }

    bool get_PieceBit(PieceType piece, int square){
        return boards[piece] & (1ULL << square);
    }


    void MovePiece(std::string move){
        //tbd

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
    return 0;
}