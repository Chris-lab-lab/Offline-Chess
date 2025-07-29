#include "pawn.h"
#include "check.h"

std::vector<Move> getPawnMoves(int row, int col, const std::string &piece, std::string (&board)[8][8], int enPassantRow, int enPassantCol){
    std::vector<Move> moves;

    bool isWhite = (piece[0] == 'w');
    int direction = isWhite ? -1 : 1;
    int startRow = isWhite ? 6 : 1;

    int nextRow = row + direction;
    if(nextRow >= 0 && nextRow < 8 && board[nextRow][col].empty()){
        if(isMoveLegal(row, col, nextRow, col, board, isWhite)) moves.push_back({nextRow, col});

        int doubleRow = row + 2 * direction;
        if(row == startRow && board[doubleRow][col].empty()){
            if(isMoveLegal(row, col, doubleRow, col, board, isWhite)) moves.push_back({doubleRow, col});
        }
    }

    // Capture (diagonal)
    int captureCols[2] = {col - 1, col + 1};
    for(int c : captureCols){
        if(c >= 0 && c < 8){
            std::string target = board[nextRow][c];
            if(!target.empty() && target[0] != piece[0]){
                if(isMoveLegal(row, col, nextRow, c, board, isWhite)) moves.push_back({nextRow, c});
            }
        }
    }

    // En Passant capture
    if(enPassantRow != -1 && enPassantCol != -1){
        // Check if the en passant square is adjacent
        if(nextRow == enPassantRow && (col - 1 == enPassantCol || col + 1 == enPassantCol)){
            if(isMoveLegal(row, col, enPassantRow, enPassantCol, board, isWhite)){
                moves.push_back({enPassantRow, enPassantCol});
            }
        }
    }
    return moves;
}
