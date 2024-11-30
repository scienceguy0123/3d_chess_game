/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 11/30/2024
Description:
What is the purpose of this file?
Bishop header file
*/
#ifndef BISHOP_H
#define BISHOP_H


#include "Chess.h"
#include "RenderBoard.h"

/// <summary>
/// Bishop class
/// </summary>
class Bishop : public Chess {
public:
	Bishop(char* path, GLuint programID, bool color, std::string MaterialName, std::string PieceName);
	bool CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) override;

};
#endif