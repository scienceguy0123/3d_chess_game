#include "Coordinate.h"

Coordinate::Coordinate() {};
Coordinate::Coordinate(int row, int column, float x, float y, float z)
	: row(row), column(column), x(x), y(y), z(z) {
	this->hasPiece = false;
}

glm::vec3 Coordinate::operator-(const Coordinate& other) const {
	return glm::vec3(x - other.x, y - other.y, z - other.z);
}

glm::vec3 Coordinate::operator+(const Coordinate& other) const {
	return glm::vec3(x + other.x, y + other.y, z + other.z);
}