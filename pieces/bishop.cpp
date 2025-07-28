#include "bishop.h"
#include "check.h"

std::vector<Move> getBishopMoves(int row, int col, const std::string &piece, std::string (&board)[8][8]){
    std::vector<Move> moves;
    
    bool isWhite = (piece[0] == 'w');

    int directions[4][2] = {
        {-1, -1}, {-1, 1}, {1, 1}, {1, -1}
    };

    for(int i = 0; i < 4; i++){
        int dr = directions[i][0];
        int dc = directions[i][1];
        int r = row + dr;
        int c = col + dc;

        while(r >= 0 && r < 8 && c >= 0 && c < 8){
            std::string target = board[r][c];

            if(target.empty()){
                if(isMoveLegal(row, col, r, c, board, isWhite)){
                    moves.push_back({r, c});
                }
                
            }
            else{ // available moves won't pierced through enemy piece
                if(target[0] != piece[0]){
                    if(isMoveLegal(row, col, r, c, board, isWhite)) moves.push_back({r, c});
                }
                break; // met friendly piece
            }
            r += dr;
            c += dc;
        }
    }

    return moves;
}