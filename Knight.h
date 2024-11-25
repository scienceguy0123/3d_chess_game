#ifndef KNIGHT_H
#define KNIGHT_H


#include "Chess.h"

class Knight : public Chess {
public:
	Knight(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName);

	enum MoveStage {
		Rise,
		Translate,
		Fall
	};
	MoveStage CurrentMoveStage = Rise;

	void Render (int index, glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID) override;
	bool CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) override;

};
#endif