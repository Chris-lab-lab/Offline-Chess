#ifndef KING_H
#define KING_H

#include <vector>
#include <string>
#include "../moves.h"

extern bool whiteKingMoved;
extern bool whiteRookLeftMoved;
extern bool whiteRookRightMoved;
extern bool blackKingMoved;
extern bool blackRookLeftMoved;
extern bool blackRookRightMoved;

std::vector<Move> getKingMoves(int row, int col, const std::string &piece, std::string (&board)[8][8]);

#endif