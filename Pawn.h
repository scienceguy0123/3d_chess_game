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

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="path">path</param>
	/// <param name="programID">program iD</param>
	/// <param name="color">color</param>
	/// <param name="MaterialName">matieral name</param>
	/// <param name="PieceName">piece name</param>
	Pawn(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName);

	/// <summary>
	/// check move valid
	/// </summary>
	/// <param name="board">board</param>
	/// <param name="PosPairOriginal">PosPairOriginal</param>
	/// <param name="PosPairFinal">PosPairFinalv</param>
	/// <returns></returns>
	bool CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) override;
};
#endif