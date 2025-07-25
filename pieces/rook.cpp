#include "rook.h"

std::vector<Move> getRookMoves(int row, int col, const std::string &piece, std::string (&board)[8][8]){
    std::vector<Move> moves;

    int directions[4][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    for(auto &d : directions){
        int r = row + d[0];
        int c = col + d[1];

        while(r >= 0 && r < 8 && c >= 0 && c < 8){
            std::string target = board[r][c];

            if(target.empty()){
                moves.push_back({r, c});
            }
            else{
                if(target[0] != piece[0]){
                    moves.push_back({r, c});
                }
                break;
            }
            r += d[0];
            c += d[1];
        }
    }
    return moves;
}