#include "Bishop.h" 

Bishop::Bishop(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName) 
	: Chess(path, programID, color, MaterialName, PieceName) {
}

bool Bishop::CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) {
	if (
		( DiagonalMove(PosPairOriginal, PosPairFinal))
		&& !PieceInRoute(board, PosPairOriginal, PosPairFinal)
		) {
		return true;
	}

	return false;

}