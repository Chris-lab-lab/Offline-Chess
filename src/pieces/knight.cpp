#include "knight.h"
#include "check.h"

std::vector<Move> getKnightMoves(int row, int col, const std::string &piece, std::string (&board)[8][8]){
    std::vector<Move> moves;

    bool isWhite = (piece[0] == 'w');

    int knightMoves[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };

    for(auto &m : knightMoves){
        int r = row + m[0];
        int c = col + m[1];
        if(r >= 0 && r < 8 && c >= 0 && c < 8){
            std::string target = board[r][c];

            // movement and capture
            if(target.empty() || target[0] != piece[0]){
                if(isMoveLegal(row, col, r, c, board, isWhite)) moves.push_back({r, c});
            }
        }
    }

    return moves;
}