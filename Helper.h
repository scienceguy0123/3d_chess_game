#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include "Chess.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "GlobalVariables.h"
#include "CommandType.h"
#include "common/controls.hpp"
#include "RenderBoard.h"
#include <utility>
#include "Bishop.h"
#include "King.h"
#include "Queen.h"

void loadPieces(std::vector<Chess>& pieces, GLuint programID, Board& board);
void inputThreadFunction();
CommandType ParseCommand();
std::pair<int, int> convertToCoordinate(std::string pos);
#endif