#ifndef CHECK_H
#define CHECK_H

#include <string>
#include <vector>
#include "../moves.h"


bool isSquareSafe(int row, int col, const std::string (&board)[8][8], bool whiteTurn);

#endif
