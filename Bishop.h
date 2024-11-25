#ifndef BISHOP_H
#define BISHOP_H


#include "Chess.h"
#include "RenderBoard.h"

class Bishop : public Chess {
public:
	Bishop(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName);
	bool CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) override;

};
#endif