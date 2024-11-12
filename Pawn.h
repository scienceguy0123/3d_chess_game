/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 10/18/2024
Description:
Class for Pawn
*/

#ifndef PAWN_H
#define PAWN_H

#include "Chess.h"

/// <summary>
/// Class for pawn
/// </summary>
class Pawn : public Chess {
public:

	bool firstMove = true;

	Pawn(char* path, GLuint programID, bool color, std::string MaterialName);

	bool CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) override;
};
#endif