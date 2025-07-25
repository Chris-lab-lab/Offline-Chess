#ifndef KING_H
#define KING_H

#include <vector>
#include <string>
#include "../moves.h"

std::vector<Move> getKingMoves(int row, int col, std::string &piece, std::string (&board)[8][8]);

#endif