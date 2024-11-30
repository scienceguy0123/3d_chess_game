/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 11/30/2024
Description:
What is the purpose of this file?
Coordinate CPP file
*/
#include "Coordinate.h"

/// <summary>
/// constructor
/// </summary>
Coordinate::Coordinate() {};

/// <summary>
/// constructor
/// </summary>
/// <param name="row">row</param>
/// <param name="column">column</param>
/// <param name="x">x</param>
/// <param name="y">y</param>
/// <param name="z">z</param>
Coordinate::Coordinate(int row, int column, float x, float y, float z)
	: row(row), column(column), x(x), y(y), z(z) {
	this->hasPiece = false;
}

/// <summary>
/// - operator
/// </summary>
/// <param name="other">other</param>
/// <returns></returns>
glm::vec3 Coordinate::operator-(const Coordinate& other) const {
	return glm::vec3(x - other.x, y - other.y, z - other.z);
}

/// <summary>
/// + operator
/// </summary>
/// <param name="other">other</param>
/// <returns></returns>
glm::vec3 Coordinate::operator+(const Coordinate& other) const {
	return glm::vec3(x + other.x, y + other.y, z + other.z);
}