#ifndef MOVES_H
#define MOVES_H

#include <string>
#include <vector>

struct Move{
    int row;
    int col;
};

std::vector<Move> getMoves(int row, int col, const std::string &piece, std::string (&board)[8][8], int enPassantRow, int enPassantCol);

#endif
