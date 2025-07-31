#ifndef BISHOP_H
#define BISHOP_H

#include <vector>
#include <string>
#include "../moves.h"

std::vector<Move> getBishopMoves(int row, int col, const std::string &piece, std::string (&board)[8][8]);

#endif