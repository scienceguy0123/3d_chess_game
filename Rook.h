#ifndef ROOK_H
#define ROOK_H


#include "Chess.h"

class Rook : public Chess {
public:
	Rook(char* path, GLuint programID, bool color, std::string MaterialName);

	bool CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) override;
};
#endif