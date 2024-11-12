#ifndef BISHOP_H
#define BISHOP_H


#include "Chess.h"
#include "RenderBoard.h"

class Bishop : public Chess {
public:
	Bishop(char* path, GLuint programID, bool color, std::string MaterialName);
};
#endif