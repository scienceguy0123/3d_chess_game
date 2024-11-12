#ifndef KNIGHT_H
#define KNIGHT_H


#include "Chess.h"

class Knight : public Chess {
public:
	Knight(char* path, GLuint programID, bool color, std::string MaterialName);

	enum MoveStage {
		Rise,
		Translate,
		Fall
	};
	MoveStage CurrentMoveStage = Rise;

	void Render (int index, glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID) override;

};
#endif