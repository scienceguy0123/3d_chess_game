/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 11/30/2024
Description:
What is the purpose of this file?
Helper header file
*/
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
#include "RenderBoard.h"

/// <summary>
/// load pieces
/// </summary>
/// <param name="pieces">pieces</param>
/// <param name="programID">program id</param>
/// <param name="board"></param>
void loadPieces(std::vector<Chess>& pieces, GLuint programID, Board& board);

/// <summary>
/// input thread function
/// </summary>
void inputThreadFunction();

/// <summary>
/// parse command
/// </summary>
/// <param name="Board">board</param>
/// <param name="programID">program id</param>
/// <returns></returns>
CommandType ParseCommand(Board& Board, GLuint programID);

/// <summary>
/// converty to coordinate
/// </summary>
/// <param name="pos">pos</param>
/// <returns></returns>
std::pair<int, int> convertToCoordinate(std::string pos);

/// <summary>
/// check check mate
/// </summary>
/// <param name="board">board</param>
/// <param name="debug">debug</param>
/// <returns></returns>
bool checkCheckMate(Board& board, bool debug=false);

/// <summary>
/// check under attack
/// </summary>
/// <param name="board">board</param>
/// <param name="i">i</param>
/// <param name="j">j</param>
/// <param name="color">color</param>
/// <param name="debug">debug</param>
/// <param name="recursive">recursive</param>
/// <returns></returns>
bool checkUnderAttack(Board& board, int i, int j, bool color, bool debug, bool recursive);


#endif