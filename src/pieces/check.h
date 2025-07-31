#ifndef CHECK_H
#define CHECK_H

#include <string>
#include <vector>
#include "../moves.h"


bool isSquareSafe(int row, int col, const std::string (&board)[8][8], bool isWhite);

bool isKingInCheck(const std::string(&board)[8][8], bool isWhite);

bool isMoveLegal(int fromRow, int fromCol, int toRow, int toCol, const std::string (&board)[8][8], bool isWhite);

#endif

