#include "Queen.h"
#include "RenderBoard.h"


Queen::Queen(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName)
	: Chess(path, programID, color, MaterialName, PieceName) {
}

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
