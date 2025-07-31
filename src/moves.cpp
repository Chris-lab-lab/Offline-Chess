#include "moves.h"
#include "pieces/pawn.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/rook.h"
#include "pieces/queen.h"
#include "pieces/king.h"
#include "pieces/check.h"
#include <string>
#include <vector>
#include <algorithm>

std::vector<Move> getMoves(int row, int col, const std::string &piece, std::string (&board)[8][8], int enPassantRow, int enPassantCol){
    if (piece.empty()) return {};
    char type = piece[1];
    switch (type){
        case 'p' : return getPawnMoves(row, col, piece, board, enPassantRow, enPassantCol);
        case 'n' : return getKnightMoves(row, col, piece, board);
        case 'b' : return getBishopMoves(row, col, piece, board);
        case 'r' : return getRookMoves(row, col, piece, board);
        case 'k' : return getKingMoves(row, col, piece, board);
        case 'q' : return getQueenMoves(row, col, piece, board);
    }
    return {};
}
