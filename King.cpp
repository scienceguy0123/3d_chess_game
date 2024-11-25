#include "King.h"
#include "RenderBoard.h"


King::King(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName)
	: Chess(path, programID, color, MaterialName, PieceName) {
}

bool King::CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) {
	if (
		(VeriticalMove(PosPairOriginal, PosPairFinal, 2, 1)
			|| HorizontalMove(PosPairOriginal, PosPairFinal, 1)
			|| DiagonalMove(PosPairOriginal, PosPairFinal, 2, 1)
			)
		&& !PieceInRoute(board, PosPairOriginal, PosPairFinal)
		) {
		return true;
	}
	return false;
}