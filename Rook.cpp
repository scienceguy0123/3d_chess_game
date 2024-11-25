#include "Rook.h"
#include "RenderBoard.h"


Rook::Rook(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName)
	: Chess(path, programID, color, MaterialName, PieceName) {
}

bool Rook::CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal)  {
	if (
		(VeriticalMove(PosPairOriginal, PosPairFinal)
			|| HorizontalMove(PosPairOriginal, PosPairFinal))
		&& !PieceInRoute(board, PosPairOriginal, PosPairFinal)
	) {
		return true;
	}

	return false;

}
