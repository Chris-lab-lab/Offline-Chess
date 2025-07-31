#include "king.h"
#include "check.h"

std::vector<Move> getKingMoves(int row, int col, const std::string &piece, std::string (&board)[8][8]){
    std::vector<Move> moves;
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},          { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    bool isWhite = piece[0] == 'w';

    for(auto &d : directions){
        int r = row + d[0];
        int c = col + d[1];

        if(r >= 0 && r < 8 && c >= 0 && c < 8){
            std::string target = board[r][c];

            if(target.empty() || target[0] != piece[0]){
                if(isSquareSafe(r, c, board, isWhite)){
                    moves.push_back({r, c});
                }
            }
        }
    }

    if(isWhite && !whiteKingMoved){
        if(!whiteRookRightMoved && board[7][5] == "" && board[7][6] == "" &&
            isSquareSafe(7, 4, board, true) &&
            isSquareSafe(7, 5, board, true) &&
            isSquareSafe(7, 6, board, true))
        {
            moves.push_back({7, 6});
        }
        if(!whiteRookLeftMoved && board[7][1] == "" && board[7][2] == "" && board[7][3] == "" &&
            isSquareSafe(7, 4, board, true) &&
            isSquareSafe(7, 3, board, true) &&
            isSquareSafe(7, 2, board, true))
        {
            moves.push_back({7, 2});
        }
    }
    else if(!isWhite && !blackKingMoved){
        if(!blackRookRightMoved && board[0][5] == "" && board[0][6] == "" &&
            isSquareSafe(0, 4, board, false) &&
            isSquareSafe(0, 5, board, false) &&
            isSquareSafe(0, 6, board, false))
        {
            moves.push_back({0, 6});
        }
        if(!blackRookLeftMoved && board[0][1] == "" && board[0][2] == "" && board[0][3] == "" &&
            isSquareSafe(0, 4, board, false) &&
            isSquareSafe(0, 3, board, false) &&
            isSquareSafe(0, 2, board, false))
        {
            moves.push_back({0, 2});
        }
    }

    return moves;
}
