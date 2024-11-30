/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 10/18/2024
Description:
Class for Pawn
*/
#include "Pawn.h"
#include "RenderBoard.h"

/// <summary>
/// constructor
/// </summary>
/// <param name="path">path</param>
/// <param name="programID">programID</param>
/// <param name="color">color</param>
/// <param name="MaterialName">MaterialName</param>
/// <param name="PieceName">PieceName</param>
Pawn::Pawn(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName)
	: Chess(path, programID, color, MaterialName, PieceName) {
}



/// <summary>
/// check move valid
/// </summary>
/// <param name="board">board</param>
/// <param name="PosPairOriginal">PosPairOriginal</param>
/// <param name="PosPairFinal">PosPairFinal</param>
/// <returns>bool</returns>
bool Pawn::CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) {
	//std::cout << "PosPairFinal.first: " << PosPairFinal.first << " PosPairOriginal.first: " << PosPairOriginal.first << std::endl;
	//std::cout << "PosPairFinal.second: " << PosPairFinal.second << " PosPairOriginal.second: " << PosPairOriginal.second << std::endl;


	if (this->color) {
		if (DiagonalMove(PosPairOriginal, PosPairFinal, 1, 1)) {
			if (
				board.Coordinates[PosPairFinal.first][PosPairFinal.second].hasPiece
				&& board.Coordinates[PosPairFinal.first][PosPairFinal.second].Piece->color != board.Coordinates[PosPairOriginal.first][PosPairOriginal.second].Piece->color
				) {
				return true;
			}
			return false;
		}
	}
	else {
		if (DiagonalMove(PosPairOriginal, PosPairFinal, 0, 1)) {
			if (
				board.Coordinates[PosPairFinal.first][PosPairFinal.second].hasPiece
				&& board.Coordinates[PosPairFinal.first][PosPairFinal.second].Piece->color != board.Coordinates[PosPairOriginal.first][PosPairOriginal.second].Piece->color
				) {
				return true;
			}
			return false;
		}
	}

	if (this->color) {
		
		if (!VeriticalMove(PosPairOriginal, PosPairFinal, 2, this->firstMove ? 2 : 1)) {
			return false;
		}
	}
	else {
		
		if (!VeriticalMove(PosPairOriginal, PosPairFinal, 1, this->firstMove ? 2 : 1)) {
			return false;
		}
	}

	if (HorizontalMove(PosPairOriginal, PosPairFinal)) {
		return false;
	}

	this->firstMove = false;

	return true;
}