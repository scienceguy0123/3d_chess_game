#ifndef QUEEN_H
#define QUEEN_H


#include "Chess.h"

class Queen : public Chess {
public:
	Queen(char* path, GLuint programID, bool color, std::string MaterialName);
};
#endif