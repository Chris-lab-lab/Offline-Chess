#include "moves.h"
#include "pieces/pawn.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/rook.h"
#include "pieces/queen.h"
#include "pieces/king.h"
#include <string>
#include <vector>

std::vector<Move> getMoves(int row, int col, const std::string &piece, std::string (&board)[8][8]){
    if (piece.empty()) return {};
    char type = piece[1];
    switch (type){
        case 'p' : return getPawnMoves(row, col, piece, board);
/*        case 'n' : return getKnightMoves(row, col, board[row][col], board);
        case 'b' : return getBishopMoves(row, col, board[row][col], board);
        case 'r' : return getRookMoves(row, col, board[row][col], board);
        case 'k' : return getKingMoves(row, col, board[row][col], board);
        case 'q' : return getQueenMoves(row, col, board[row][col], board);
*/
    }
    return {};
}