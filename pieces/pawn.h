#ifndef PAWN_H
#define PAWN_H

#include <vector>
#include <string>
#include "../moves.h"

std::vector<Move> getPawnMoves(int row, int col, const std::string &piece, std::string (&board)[8][8]);

#endif