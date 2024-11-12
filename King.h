#ifndef KING_H
#define KING_H


#include "Chess.h"

class King : public Chess {
public:
	King(char* path, GLuint programID, bool color, std::string MaterialName);
};
#endif