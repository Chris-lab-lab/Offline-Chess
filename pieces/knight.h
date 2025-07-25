#ifndef KNIGHT_H
#define KNIGHT_H

#include <vector>
#include <string>
#include "../moves.h"

std::vector<Move> getKnightMoves(int row, int col, const std::string &piece, std::string (&board)[8][8]);

#endif