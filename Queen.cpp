/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 11/30/2024
Description:
What is the purpose of this file?
queen CPP file
*/

#include "Queen.h"
#include "RenderBoard.h"

/// <summary>
/// constructor
/// </summary>
/// <param name="path">path</param>
/// <param name="programID">program id</param>
/// <param name="color">color</param>
/// <param name="MaterialName">material name</param>
/// <param name="PieceName">peice name</param>
Queen::Queen(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName)
	: Chess(path, programID, color, MaterialName, PieceName) {
}

/// <summary>
/// check move valid
/// </summary>
/// <param name="board">board</param>
/// <param name="PosPairOriginal">PosPairOriginal</param>
/// <param name="PosPairFinal">PosPairFinal</param>
/// <returns></returns>
bool Queen::CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) {
	if (
		(VeriticalMove(PosPairOriginal, PosPairFinal)
			|| HorizontalMove(PosPairOriginal, PosPairFinal)
			|| DiagonalMove(PosPairOriginal, PosPairFinal))
		&& !PieceInRoute(board, PosPairOriginal, PosPairFinal)
		) {
		return true;
	}

	return false;

}
