#ifndef QUEEN_H
#define QUEEN_H


#include "Chess.h"

class Queen : public Chess {
public:
	Queen(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName);

	bool CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) override;

};
#endif