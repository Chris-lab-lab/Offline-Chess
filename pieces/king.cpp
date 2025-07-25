#include "king.h"

std::vector<Move> getKingMoves(int row, int col, const std::string &piece, std::string (&board)[8][8]){
    std::vector<Move> moves;
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    for(auto &d : directions){
        int r = row + d[0];
        int c = col + d[1];

        if(r >= 0 && r < 8 && c >= 0 && c < 8){
            std::string target = board[r][c];

            if(target.empty() || target[0] != piece[0]){
                moves.push_back({r, c});
            }
        }
    }

    return moves;
}