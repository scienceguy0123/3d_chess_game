#ifndef KING_H
#define KING_H


#include "Chess.h"

class King : public Chess {
public:
	King(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName);
	bool CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) override;

};
#endif