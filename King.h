/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 11/30/2024
Description:
What is the purpose of this file?
King header file
*/
#ifndef KING_H
#define KING_H


#include "Chess.h"

/// <summary>
/// king class
/// </summary>
class King : public Chess {
public:
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="path">path</param>
	/// <param name="programID">programID</param>
	/// <param name="color">color</param>
	/// <param name="MaterialName">MaterialName</param>
	/// <param name="PieceName">PieceName</param>
	King(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName);
	
	/// <summary>
	/// check move valid
	/// </summary>
	/// <param name="board">board</param>
	/// <param name="PosPairOriginal">PosPairOriginal</param>
	/// <param name="PosPairFinal">PosPairFinal</param>
	/// <returns></returns>
	bool CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) override;

};
#endif