/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 11/30/2024
Description:
What is the purpose of this file?
Bishop CPP file
*/
#include "Bishop.h" 

/// <summary>
/// Bishop constructor
/// </summary>
/// <param name="path">path</param>
/// <param name="programID">programID</param>
/// <param name="color">color</param>
/// <param name="MaterialName">MaterialName</param>
/// <param name="PieceName">PieceName</param>
Bishop::Bishop(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName) 
	: Chess(path, programID, color, MaterialName, PieceName) {
}

/// <summary>
/// Check move valid
/// </summary>
/// <param name="board">board</param>
/// <param name="PosPairOriginal">PosPairOriginal</param>
/// <param name="PosPairFinal">PosPairFinal</param>
/// <returns>bool</returns>
bool Bishop::CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) {
	if (
		( DiagonalMove(PosPairOriginal, PosPairFinal))
		&& !PieceInRoute(board, PosPairOriginal, PosPairFinal)
		) {
		return true;
	}

	return false;

}