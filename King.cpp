/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 11/30/2024
Description:
What is the purpose of this file?
King CPP file
*/

#include "King.h"
#include "RenderBoard.h"

/// <summary>
/// constructor
/// </summary>
/// <param name="path">path</param>
/// <param name="programID">program id</param>
/// <param name="color">color</param>
/// <param name="MaterialName">matrial name</param>
/// <param name="PieceName">piece name</param>
King::King(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName)
	: Chess(path, programID, color, MaterialName, PieceName) {
}

/// <summary>
/// check move valid
/// </summary>
/// <param name="board">board</param>
/// <param name="PosPairOriginal">pos pair original</param>
/// <param name="PosPairFinal">pos pair final</param>
/// <returns></returns>
bool King::CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) {
	if (
		(VeriticalMove(PosPairOriginal, PosPairFinal, 3, 1)
			|| HorizontalMove(PosPairOriginal, PosPairFinal, 1)
			|| DiagonalMove(PosPairOriginal, PosPairFinal, 2, 1)
			)
		&& !PieceInRoute(board, PosPairOriginal, PosPairFinal)
		) {
		return true;
	}
	return false;
}