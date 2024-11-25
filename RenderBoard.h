/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 10/18/2024
Description:
Class for Render board
*/

#ifndef RENDERBOARD_H
#define RENDERBOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <glm/glm.hpp>
#include "common/objloader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Coordinate.h"
#include "Knight.h"

/// <summary>
/// class for board
/// </summary>
struct Board {
	
	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint elementbuffer;

	GLuint Texture;
	GLuint TextureID;

	Coordinate Coordinates[8][8];



	/// <summary>
	/// Board constructor
	/// </summary>
	/// <param name="programID">program id</param>
	Board(GLuint programID);

	/// <summary>
	/// Render board
	/// </summary>
	/// <param name="ProjectionMatrix">project matrix</param>
	/// <param name="ViewMatrix">view matrix</param>
	/// <param name="MatrixID">matrix id</param>
	/// <param name="ViewMatrixID">view matrix id</param>
	/// <param name="ModelMatrixID">model matrix id</param>
	void RenderBoard(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID);
	
	void CreateCoordinates();


	void MovePiece(std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal);

	void MvPiece(std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal);

	void RemovePiece(std::pair<int, int>& PosPairOriginal);

	void RemoveAll();

	/// <summary>
	/// clean board
	/// </summary>
	void CleanBoard();

};


#endif

/// a2 : x: -13.447, y : 18.948, z:1.8588
/// a3 : x: -8.1179, y : 18.948, z:1.8588