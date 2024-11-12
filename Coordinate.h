#ifndef COORDINATE_H
#define COORDINATE_H

#include "Chess.h"

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