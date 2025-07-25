#ifndef QUEEN_H
#define QUEEN_H

#include <vector>
#include <string>
#include "../moves.h"

std::vector<Move> getQueenMoves(int row, int col, const std::string &piece, std::string (&board)[8][8]);

#endif