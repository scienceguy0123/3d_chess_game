/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 11/30/2024
Description:
What is the purpose of this file?
Coordinate header file
*/
#ifndef COORDINATE_H
#define COORDINATE_H

#include "Chess.h"

/// <summary>
/// Coordinate class
/// </summary>
struct Coordinate {
	int row;
	int column;
	float x;
	float y;
	float z;

	Coordinate();
	Coordinate(int row, int column, float x, float y, float z);
	bool hasPiece;
	Chess* Piece;
	glm::vec3 Coordinate::operator-(const Coordinate& other) const;
	glm::vec3 Coordinate::operator+(const Coordinate& other) const;
};

#endif