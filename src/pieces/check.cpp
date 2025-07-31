#include "check.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

bool isSquareSafe(int row, int col, const std::string (&board)[8][8], bool isWhite){
    char enemyColor = isWhite ? 'b' : 'w';

    // Check pawn attack
    if(enemyColor == 'w'){
        int pawnRow = row + 1;
        if(pawnRow < 8){
            if(col - 1 >= 0 && board[pawnRow][col - 1] == "wp") return false;
            if(col + 1 < 8 && board[pawnRow][col + 1] == "wp") return false;
        }
    }
    else{
        int pawnRow = row - 1;
        if(pawnRow >= 0){
            if(col - 1 >= 0 && board[pawnRow][col - 1] == "bp") return false;
            if(col + 1 < 8 && board[pawnRow][col + 1] == "bp") return false;
        }
        
    }

    // Check knight attack
    int knightMoves[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };
    for(auto &m : knightMoves){
        int r = row + m[0];
        int c = col + m[1];
        if(r >= 0 && r < 8 && c >= 0 && c < 8){
            if(!board[r][c].empty()){
                if(board[r][c][0] == enemyColor && board[r][c][1] == 'n') return false;
            }
        }
    }

    // Check rook/queen(rook) attack
    int straightMoves[4][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };
    for(auto &d : straightMoves){
        int r = row + d[0];
        int c = col + d[1];
        while(r >= 0 && r < 8 && c >= 0 && c < 8){
            if(!board[r][c].empty()){
                if(board[r][c][0] == enemyColor && (board[r][c][1] == 'r' || board[r][c][1] == 'q')) return false;
                else{
                    if(board[r][c][1] != 'k') break;
                }
            }
            r += d[0];
            c += d[1];
        }
    }

    // Check bishop/queen(bishop) attack
    int diagonalMoves[4][2] = {
        {-1, -1}, {-1, 1}, {1, 1}, {1, -1}
    };
    for(auto &d : diagonalMoves){
        int r = row + d[0];
        int c = col + d[1];
        while(r >=0 && r < 8 && c >=0 && c < 8){
            if(!board[r][c].empty()){
                if(board[r][c][0] == enemyColor && (board[r][c][1] == 'b' || board[r][c][1] == 'q')) return false;
                else{
                    if(board[r][c][1] != 'k') break;
                }
            }
            r += d[0];
            c += d[1];
        }
    }

    // Check king
    int kingMoves[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };
    for(auto &d : kingMoves){
        int r = row + d[0];
        int c = col + d[1];
        if(r >= 0 && r < 8 && c >=0 && c < 8){
            if(!board[r][c].empty()){
                if(board[r][c][0] == enemyColor && board[r][c][1] == 'k') return false;
            }
        }
    }

    return true;
}

bool isKingInCheck(const std::string (&board)[8][8], bool isWhite){
    std::string kingCode = isWhite ? "wk" : "bk";
    int kingRow = -1, kingCol = -1;

    // LF king
    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            if(board[r][c] == kingCode){
                kingRow = r;
                kingCol = c;
                break;
            }
        }
    }
    return !isSquareSafe(kingRow, kingCol, board, isWhite);
}

bool isMoveLegal(int fromRow, int fromCol, int toRow, int toCol, const std::string (&board)[8][8], bool isWhite){
    std::string tempBoard[8][8];
    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            tempBoard[r][c] = board[r][c];
        }
    }

    tempBoard[toRow][toCol] = tempBoard[fromRow][fromCol];
    tempBoard[fromRow][fromCol] = "";

    if(isKingInCheck(tempBoard, isWhite)) return false;
    return true;

}
