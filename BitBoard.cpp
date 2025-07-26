#include "bitboard.hpp"
#include <unordered_map>
#include <intrin.h>
#pragma intrinsic(_BitScanForward64)





//array holding all 12 bitboards which represent the gamestate
std::array<unsigned long long, 14> boards; //last two boards are colour boards (12 = white, 13 = black)

//All Ranks as bits (May be useful, idk)
static unsigned long long RANK_1 = 0x00000000000000FFULL;
static unsigned long long RANK_2 = 0x000000000000FF00ULL;
static unsigned long long RANK_3 = 0x0000000000FF0000ULL;
static unsigned long long RANK_4 = 0x00000000FF000000ULL;
static unsigned long long RANK_5 = 0x000000FF00000000ULL;
static unsigned long long RANK_6 = 0x0000FF0000000000ULL;
static unsigned long long RANK_7 = 0x00FF000000000000ULL;
static unsigned long long RANK_8 = 0xFF00000000000000ULL;

//All files as bits (May be useful, idk)
static unsigned long long A_FILE = 0x0101010101010101ULL;
static unsigned long long B_FILE = 0x0202020202020202ULL;
static unsigned long long C_FILE = 0x0303030303030303ULL;
static unsigned long long D_FILE = 0x0404040404040404ULL;
static unsigned long long E_FILE = 0x0505050505050505ULL;
static unsigned long long F_FILE = 0x0606060606060606ULL;
static unsigned long long G_FILE = 0x0707070707070707ULL;
static unsigned long long H_FILE = 0x0808080808080808ULL;

//constructor
BitBoard::BitBoard() {
    for (int i = 0; i < 14; ++i) {
        boards[i] = 0ULL;
}
}

//sets game to default position. I think I will eventually switch to Fen, but idk when
void BitBoard::SetGame(){
    set_bit(boards[WHITE_KING], e1);
    set_bit(boards[WHITE_QUEEN], d1);
    set_bit(boards[WHITE_BISHOPS], c1);
    set_bit(boards[WHITE_BISHOPS], f1);
    set_bit(boards[WHITE_KNIGHTS], b1);
    set_bit(boards[WHITE_KNIGHTS], g1);
    set_bit(boards[WHITE_ROOKS], a1);
    set_bit(boards[WHITE_ROOKS], h1);
    for(int i = 8; i < 16; i++){
        set_bit(boards[WHITE_PAWNS], i);
    }
    set_bit(boards[BLACK_KING], e8);
    set_bit(boards[BLACK_QUEEN], d8);
    set_bit(boards[BLACK_BISHOPS], c8);
    set_bit(boards[BLACK_BISHOPS], f8);
    set_bit(boards[BLACK_KNIGHTS], b8);
    set_bit(boards[BLACK_KNIGHTS], g8);
    set_bit(boards[BLACK_ROOKS], a8);
    set_bit(boards[BLACK_ROOKS], h8);
    for(int i = 48; i < 56; i++){
        set_bit(boards[BLACK_PAWNS], i);
    }

    //now for the colour boards
    boards[WHITE] = RANK_1 | RANK_2;
    boards[BLACK] = RANK_7 | RANK_8;
}

//sets a bit to 1
void set_bit(unsigned long long& board, int square){
    board |= (1ULL << square);
}

//checks if a piece of a given type exists on a square
bool get_bit(unsigned long long& board, int square){
    return board & (1ULL << square);
}


//removes a piece of a given type on a square
void pop_bit(unsigned long long& board, int square){
        board &= ~(1ULL << square);
}


void print_board(unsigned long long board){

}



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



std::array<unsigned long long, 14> temp_boards = bb.boards;

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
