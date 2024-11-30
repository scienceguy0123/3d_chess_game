/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 11/30/2024
Description:
What is the purpose of this file?
Rook header file
*/
#ifndef ROOK_H
#define ROOK_H


#include "Chess.h"

/// <summary>
/// Rook class
/// </summary>
class Rook : public Chess {
public:
	/// <summary>
	/// Rook
	/// </summary>
	/// <param name="path">path</param>
	/// <param name="programID">program id</param>
	/// <param name="color">color</param>
	/// <param name="MaterialName">material name</param>
	/// <param name="PieceName">peice name</param>
	Rook(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName);

	/// <summary>
	/// check move valid
	/// </summary>
	/// <param name="board">board</param>
	/// <param name="PosPairOriginal">PosPairOriginal</param>
	/// <param name="PosPairFinal">PosPairFinal</param>
	/// <returns>bool</returns>
	bool CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) override;
};
#endif