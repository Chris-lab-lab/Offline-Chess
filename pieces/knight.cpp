#include "knight.h"

std::vector<Move> getKnightMoves(int row, int col, const std::string &piece, std::string (&board)[8][8]){
    std::vector<Move> moves;
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
                moves.push_back({r, c});
            }
        }
    }

    return moves;
}