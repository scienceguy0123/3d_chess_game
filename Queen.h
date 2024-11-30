/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 11/30/2024
Description:
What is the purpose of this file?
Queen header file
*/
#ifndef QUEEN_H
#define QUEEN_H


#include "Chess.h"

/// <summary>
/// Queen class
/// </summary>
class Queen : public Chess {
public:
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="path">path</param>
	/// <param name="programID">program id</param>
	/// <param name="color">color</param>
	/// <param name="MaterialName">material name</param>
	/// <param name="PieceName">peice name</param>
	Queen(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName);

	/// <summary>
	/// check move valid
	/// </summary>
	/// <param name="board">board</param>
	/// <param name="PosPairOriginal">pos pair original</param>
	/// <param name="PosPairFinal">pos pair final</param>
	/// <returns></returns>
	bool CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) override;

};
#endif