#ifndef ROOK_H
#define ROOK_H

#include <vector>
#include <string>
#include "../moves.h"

std::vector<Move> getRookMoves(int row, int col, const std::string &piece, std::string (&board)[8][8]);

#endif