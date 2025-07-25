#include "pawn.h"

std::vector<Move> getPawnMoves(int row, int col, const std::string &piece, std::string (&board)[8][8]){
    std::vector<Move> moves;

    bool isWhite = (piece[0] == 'w');
    int direction = isWhite ? -1 : 1;

    int nextRow = row + direction;
    if(nextRow >= 0 && nextRow < 8 && board[nextRow][col].empty()){
        moves.push_back({nextRow, col});

        int startRow = isWhite ? 6 : 1;
        int doubleRow = row + 2 * direction;
        if(row == startRow && board[doubleRow][col].empty()){
            moves.push_back({doubleRow, col});
        }
    }

    // Capture (diagonal)
    int captureCols[2] = {col - 1, col + 1};
    for(int c : captureCols){
        if(c >= 0 && c < 8){
            std::string target = board[nextRow][c];
            if(!target.empty() && target[0] != piece[0]){
                moves.push_back({nextRow, c});
            }
        }
    }
    return moves;
}