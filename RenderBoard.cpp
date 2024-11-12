#include "RenderBoard.h"



Board::Board(GLuint programID) {

	bool res = loadAssImp("ChessBoard/chess_board.obj", this->indices, this->indexed_vertices, this->indexed_uvs, this->indexed_normals);
	
	//GLuint vertexbuffer;
	glGenBuffers(1, &this->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->indexed_vertices.size() * sizeof(glm::vec3), &this->indexed_vertices[0], GL_STATIC_DRAW);

	// Check for errors
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "RenderBoard glBufferData failed with error code: " << err << std::endl;

	}
	else {
		std::cout << "RenderBoard main glBufferData succeeded!" << std::endl;
	}

	//GLuint uvbuffer;
	glGenBuffers(1, &this->uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->indexed_uvs.size() * sizeof(glm::vec2), &this->indexed_uvs[0], GL_STATIC_DRAW);

	//GLuint normalbuffer;
	glGenBuffers(1, &this->normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->indexed_normals.size() * sizeof(glm::vec3), &this->indexed_normals[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	//GLuint elementbuffer;
	glGenBuffers(1, &this->elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned short), &this->indices[0], GL_STATIC_DRAW);

	auto material = loadMTL("ChessBoard/chess_board.mtl")["12951_Stone_Chess_Board"];


	glUniform3fv(glGetUniformLocation(programID, "ambient"), 1, &material.ambient[0]);
	glUniform3fv(glGetUniformLocation(programID, "diffuse"), 1, &material.diffuse[0]);
	glUniform3fv(glGetUniformLocation(programID, "specular"), 1, &material.specular[0]);

	// Load the texture
	//GLuint Texture;
	this->Texture = loadTexture(("ChessBoard/" + material.textureMap).c_str());

	// Get a handle for our "myTextureSampler" uniform
	//GLuint TextureID;
	this->TextureID = glGetUniformLocation(programID, "myTextureSampler");
	
	CreateCoordinates();
	
}

void Board::CreateCoordinates() {
	this->Coordinates[0][0] = Coordinate(0, 0, -18.852f, 1.8588f, 18.8363f); // a1
	this->Coordinates[0][1] = Coordinate(0, 1, -18.9634f, 1.8588f, 13.4614f); // b1
	this->Coordinates[0][2] = Coordinate(0, 2, -18.963f, 1.8588f, 8.10215f);
	this->Coordinates[0][3] = Coordinate(0, 3, -18.963f, 1.8588f, 2.7026f);
	this->Coordinates[0][4] = Coordinate(0, 4, -18.963f, 1.8588f, -2.7104f);
	this->Coordinates[0][5] = Coordinate(0, 5, -18.963f, 1.8588f, -8.10995f);
	this->Coordinates[0][6] = Coordinate(0, 6, -18.963f, 1.8588f, -13.4692f);
	this->Coordinates[0][7] = Coordinate(0, 7, -18.963f, 1.8588f, -18.844f);

	this->Coordinates[1][0] = Coordinate(1, 0, -13.4772f, 1.8588f, 18.9476f); //b2
	this->Coordinates[1][1] = Coordinate(1, 1, -13.4753f, 1.8588f, 13.4596f); //b2
	this->Coordinates[1][2] = Coordinate(1, 2, -13.4753f, 1.8588f, 8.1018f);
	this->Coordinates[1][3] = Coordinate(1, 3, -13.4753f, 1.8588f, 2.7026f);
	this->Coordinates[1][4] = Coordinate(1, 4, -13.4753f, 1.8588f, -2.7104f);
	this->Coordinates[1][5] = Coordinate(1, 5, -13.4753f, 1.8588f, -8.1096f);
	this->Coordinates[1][6] = Coordinate(1, 6, -13.4753f, 1.8588f, -13.4673f);
	this->Coordinates[1][7] = Coordinate(1, 7, -13.4753f, 1.8588f, -18.9553f);

	this->Coordinates[2][0] = Coordinate(2, 0, -8.11795f, 1.8588f, 18.9476f); //a3
	this->Coordinates[2][1] = Coordinate(2, 1, -8.1176f, 1.8588f, 13.4596f); //b3
	this->Coordinates[2][2] = Coordinate(2, 2, -8.1176f, 1.8588f, 8.1018f);
	this->Coordinates[2][3] = Coordinate(2, 3, -8.1176f, 1.8588f, 2.7026f);
	this->Coordinates[2][4] = Coordinate(2, 4, -8.1176f, 1.8588f, -2.7104f);
	this->Coordinates[2][5] = Coordinate(2, 5, -8.1176f, 1.8588f, -8.1096f);
	this->Coordinates[2][6] = Coordinate(2, 6, -8.1176f, 1.8588f, -13.4673f);
	this->Coordinates[2][7] = Coordinate(2, 7, -8.1176f, 1.8588f, -18.9553f);
													  
	this->Coordinates[3][0] = Coordinate(3, 0, -2.7184f, 1.8588f, 18.9476f); //a4
	this->Coordinates[3][1] = Coordinate(3, 1, -2.7184f, 1.8588f, 13.4596f); //b4
	this->Coordinates[3][2] = Coordinate(3, 2, -2.7184f, 1.8588f, 8.1018f);
	this->Coordinates[3][3] = Coordinate(3, 3, -2.7184f, 1.8588f, 2.7026f);
	this->Coordinates[3][4] = Coordinate(3, 4, -2.7184f, 1.8588f, -2.7104f);
	this->Coordinates[3][5] = Coordinate(3, 5, -2.7184f, 1.8588f, -8.1096f);
	this->Coordinates[3][6] = Coordinate(3, 6, -2.7184f, 1.8588f, -13.4673f);
	this->Coordinates[3][7] = Coordinate(3, 7, -2.71846f, 1.8588f, -18.955f);

	this->Coordinates[4][0] = Coordinate(4, 0, 2.6946f, 1.8588f, 18.9476f); //a5
	this->Coordinates[4][1] = Coordinate(4, 1, 2.6946f, 1.8588f, 13.4596f); //b5
	this->Coordinates[4][2] = Coordinate(4, 2, 2.6946f, 1.8588f, 8.1018f);
	this->Coordinates[4][3] = Coordinate(4, 3, 2.6946f, 1.8588f, 2.7026f);
	this->Coordinates[4][4] = Coordinate(4, 4, 2.6946f, 1.8588f, -2.7104f);
	this->Coordinates[4][5] = Coordinate(4, 5, 2.6946f, 1.8588f, -8.1096f);
	this->Coordinates[4][6] = Coordinate(4, 6, 2.6946f, 1.8588f, -13.4673f);
	this->Coordinates[4][7] = Coordinate(4, 7, 2.6946f, 1.8588f, -18.955f);
													 
	this->Coordinates[5][0] = Coordinate(5, 0, 8.0942f, 1.8588f, 18.9476f); //a6
	this->Coordinates[5][1] = Coordinate(5, 1, 8.0939f, 1.8588f, 13.4596f); //b6
	this->Coordinates[5][2] = Coordinate(5, 2, 8.0939f, 1.8588f, 8.1018f);
	this->Coordinates[5][3] = Coordinate(5, 3, 8.0939f, 1.8588f, 2.7026f);
	this->Coordinates[5][4] = Coordinate(5, 4, 8.0939f, 1.8588f, -2.7104f);
	this->Coordinates[5][5] = Coordinate(5, 5, 8.0939f, 1.8588f, -8.1096f);
	this->Coordinates[5][6] = Coordinate(5, 6, 8.0939f, 1.8588f, -13.4673f);
	this->Coordinates[5][7] = Coordinate(5, 7, 8.0939f, 1.8588f, -18.955f);

	this->Coordinates[6][0] = Coordinate(6, 0, 13.4535f, 1.8588f, 18.9476f); //a7
	this->Coordinates[6][1] = Coordinate(6, 1, 13.4516f, 1.8588f, 13.4596f); //b7
	this->Coordinates[6][2] = Coordinate(6, 2, 13.4516f, 1.8588f, 8.1018f);
	this->Coordinates[6][3] = Coordinate(6, 3, 13.4516f, 1.8588f, 2.7026f);
	this->Coordinates[6][4] = Coordinate(6, 4, 13.4516f, 1.8588f, -2.7104f);
	this->Coordinates[6][5] = Coordinate(6, 5, 13.4516f, 1.8588f, -8.1096f);
	this->Coordinates[6][6] = Coordinate(6, 6, 13.4516f, 1.8588f, -13.4673f);
	this->Coordinates[6][7] = Coordinate(6, 7, 13.4516f, 1.8588f, -18.955f);
													  		   
	this->Coordinates[7][0] = Coordinate(7, 0, 18.8283f, 1.8588f, 18.8363f); //a8
	this->Coordinates[7][1] = Coordinate(7, 1, 18.9396f, 1.8588f, 13.4614f); //b8
	this->Coordinates[7][2] = Coordinate(7, 2, 18.9396f, 1.8588f, 8.10215f);
	this->Coordinates[7][3] = Coordinate(7, 3, 18.9396f, 1.8588f, 2.7026f);
	this->Coordinates[7][4] = Coordinate(7, 4, 18.9396f, 1.8588f, -2.7104f);
	this->Coordinates[7][5] = Coordinate(7, 5, 18.9396f, 1.8588f, -8.1096f);
	this->Coordinates[7][6] = Coordinate(7, 6, 18.9396f, 1.8588f, -13.4673f);
	this->Coordinates[7][7] = Coordinate(7, 7, 19.3088f, 1.8588f, -19.3245f);

	//this->Coordinates[0][0] = Coordinate(0, 0, -18.852, 18.8363, 1.8588); // a1
	//this->Coordinates[0][1] = Coordinate(0, 1, -18.9634, 13.4614 , 1.8588); // b1
	//this->Coordinates[0][2] = Coordinate(0, 2, -18.963, 8.10215, 1.8588);
	//this->Coordinates[0][3] = Coordinate(0, 3, -18.963, 2.7026, 1.8588);
	//this->Coordinates[0][4] = Coordinate(0, 4, -18.963, -2.7104, 1.8588);
	//this->Coordinates[0][5] = Coordinate(0, 5, -18.963, -8.10995, 1.8588);
	//this->Coordinates[0][6] = Coordinate(0, 6, -18.963, -13.4692, 1.8588);
	//this->Coordinates[0][7] = Coordinate(0, 7, -18.963, -18.844, 1.8588);

	//this->Coordinates[1][0] = Coordinate(1, 0, -13.4772, 18.9476, 1.8588); //a2
	//this->Coordinates[1][1] = Coordinate(1, 1, -13.4753, 13.4596, 1.8588); //b2
	//this->Coordinates[1][2] = Coordinate(1, 2, -13.4753, 8.1018, 1.8588);
	//this->Coordinates[1][3] = Coordinate(1, 3, -13.4753, 2.7026, 1.8588);
	//this->Coordinates[1][4] = Coordinate(1, 4, -13.4753, -2.7104, 1.8588);
	//this->Coordinates[1][5] = Coordinate(1, 5, -13.4753, -8.1096, 1.8588);
	//this->Coordinates[1][6] = Coordinate(1, 6, -13.4753, -13.4673, 1.8588);
	//this->Coordinates[1][7] = Coordinate(1, 7, -13.4753, -18.9553, 1.8588);

	//this->Coordinates[2][0] = Coordinate(2, 0, -8.11795 , 18.9476, 1.8588); //a3
	//this->Coordinates[2][1] = Coordinate(2, 1, -8.1176, 13.4596, 1.8588); //b3
	//this->Coordinates[2][2] = Coordinate(2, 2, -8.1176, 8.1018, 1.8588);
	//this->Coordinates[2][3] = Coordinate(2, 3, -8.1176, 2.7026, 1.8588);
	//this->Coordinates[2][4] = Coordinate(2, 4, -8.1176, -2.7104, 1.8588);
	//this->Coordinates[2][5] = Coordinate(2, 5, -8.1176, -8.1096, 1.8588);
	//this->Coordinates[2][6] = Coordinate(2, 6, -8.1176, -13.4673, 1.8588);
	//this->Coordinates[2][7] = Coordinate(2, 7, -8.1176, -18.9553, 1.8588);

	//this->Coordinates[3][0] = Coordinate(3, 0, -2.7184, 18.9476, 1.8588); //a4
	//this->Coordinates[3][1] = Coordinate(3, 1, -2.7184, 13.4596, 1.8588); //b4
	//this->Coordinates[3][2] = Coordinate(3, 2, -2.7184, 8.1018, 1.8588);
	//this->Coordinates[3][3] = Coordinate(3, 3, -2.7184, 2.7026, 1.8588);
	//this->Coordinates[3][4] = Coordinate(3, 4, -2.7184, -2.7104, 1.8588);
	//this->Coordinates[3][5] = Coordinate(3, 5, -2.7184, -8.1096, 1.8588);
	//this->Coordinates[3][6] = Coordinate(3, 6, -2.7184, -13.4673, 1.8588);
	//this->Coordinates[3][7] = Coordinate(3, 7, -2.71846, -18.955, 1.8588);

	//this->Coordinates[4][0] = Coordinate(4, 0, 2.6946, 18.9476, 1.8588); //a5
	//this->Coordinates[4][1] = Coordinate(4, 1, 2.6946, 13.4596, 1.8588); //b5
	//this->Coordinates[4][2] = Coordinate(4, 2, 2.6946, 8.1018, 1.8588);
	//this->Coordinates[4][3] = Coordinate(4, 3, 2.6946, 2.7026, 1.8588);
	//this->Coordinates[4][4] = Coordinate(4, 4, 2.6946, -2.7104, 1.8588);
	//this->Coordinates[4][5] = Coordinate(4, 5, 2.6946, -8.1096, 1.8588);
	//this->Coordinates[4][6] = Coordinate(4, 6, 2.6946, -13.4673, 1.8588);
	//this->Coordinates[4][7] = Coordinate(4, 7, 2.6946, -18.955, 1.8588);

	//this->Coordinates[5][0] = Coordinate(5, 0, 8.0942, 18.9476, 1.8588); //a6
	//this->Coordinates[5][1] = Coordinate(5, 1, 8.0939, 13.4596, 1.8588); //b6
	//this->Coordinates[5][2] = Coordinate(5, 2, 8.0939, 8.1018, 1.8588);
	//this->Coordinates[5][3] = Coordinate(5, 3, 8.0939, 2.7026, 1.8588);
	//this->Coordinates[5][4] = Coordinate(5, 4, 8.0939, -2.7104, 1.8588);
	//this->Coordinates[5][5] = Coordinate(5, 5, 8.0939, -8.1096, 1.8588);
	//this->Coordinates[5][6] = Coordinate(5, 6, 8.0939, -13.4673, 1.8588);
	//this->Coordinates[5][7] = Coordinate(5, 7, 8.0939, -18.955, 1.8588);

	//this->Coordinates[6][0] = Coordinate(6, 0, 13.4535, 18.9476, 1.8588); //a7
	//this->Coordinates[6][1] = Coordinate(6, 1, 13.4516, 13.4596, 1.8588); //b7
	//this->Coordinates[6][2] = Coordinate(6, 2, 13.4516, 8.1018, 1.8588);
	//this->Coordinates[6][3] = Coordinate(6, 3, 13.4516, 2.7026, 1.8588);
	//this->Coordinates[6][4] = Coordinate(6, 4, 13.4516, -2.7104, 1.8588);
	//this->Coordinates[6][5] = Coordinate(6, 5, 13.4516, -8.1096, 1.8588);
	//this->Coordinates[6][6] = Coordinate(6, 6, 13.4516, -13.4673, 1.8588);
	//this->Coordinates[6][7] = Coordinate(6, 7, 13.4516, -18.955, 1.8588);

	//this->Coordinates[7][0] = Coordinate(7, 0, 18.8283, 18.8363, 1.8588); //a8
	//this->Coordinates[7][1] = Coordinate(7, 1, 18.9396, 13.4614, 1.8588); //b8
	//this->Coordinates[7][2] = Coordinate(7, 2, 18.9396, 8.10215, 1.8588);
	//this->Coordinates[7][3] = Coordinate(7, 3, 18.9396, 2.7026, 1.8588);
	//this->Coordinates[7][4] = Coordinate(7, 4, 18.9396, -2.7104, 1.8588);
	//this->Coordinates[7][5] = Coordinate(7, 5, 18.9396, -8.1096, 1.82588);
	//this->Coordinates[7][6] = Coordinate(7, 6, 18.9396, -13.4673, 1.8588);
	//this->Coordinates[7][7] = Coordinate(7, 7, 19.3088, -19.3245, 1.8588);
}
	

void Board::MovePiece(std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) {
	auto& OriginalCoordinate = this->Coordinates[PosPairOriginal.first][PosPairOriginal.second];
	if (OriginalCoordinate.hasPiece) {
		auto& FinalCoordiante = this->Coordinates[PosPairFinal.first][PosPairFinal.second];

		if (FinalCoordiante.hasPiece) {
			if (FinalCoordiante.Piece->color == OriginalCoordinate.Piece->color) {
				std::cout << "Invalid command or move" << std::endl;
				return;
			}

		}

		if (!OriginalCoordinate.Piece->CheckMoveValid(*this, PosPairOriginal, PosPairFinal)) {
			std::cout << "Invalid command or move" << std::endl;
			return;
		}


		this->Coordinates[PosPairFinal.first][PosPairFinal.second].Piece = std::move(this->Coordinates[PosPairOriginal.first][PosPairOriginal.second].Piece);

		OriginalCoordinate.hasPiece = false;

		FinalCoordiante.hasPiece = true;

		auto test = FinalCoordiante - OriginalCoordinate;
		FinalCoordiante.Piece->TargetTranslateVector.x = FinalCoordiante.Piece->TargetTranslateVector.x + test.x;
		FinalCoordiante.Piece->TargetTranslateVector.z = FinalCoordiante.Piece->TargetTranslateVector.z - test.z;
		FinalCoordiante.Piece->TargetTranslateVector.y = FinalCoordiante.Piece->TargetTranslateVector.y + test.y;
		//FinalCoordiante.Piece.TargetTranslateVector.x = FinalCoordiante.Piece.TargetTranslateVector + (FinalCoordiante - OriginalCoordinate);
		FinalCoordiante.Piece->translating = true;
	}
	else {
		std::cout<< "Invalid command or move" << std::endl;
	}
}


void Board::MvPiece(std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) {
	auto& OriginalCoordinate = this->Coordinates[PosPairOriginal.first][PosPairOriginal.second];
	if (OriginalCoordinate.hasPiece) {
		auto& FinalCoordiante = this->Coordinates[PosPairFinal.first][PosPairFinal.second];

		if (FinalCoordiante.hasPiece) {
			if (FinalCoordiante.Piece->color == OriginalCoordinate.Piece->color) {
				std::cout << "Invalid command or move" << std::endl;
				return;
			}

		}


		this->Coordinates[PosPairFinal.first][PosPairFinal.second].Piece = std::move(this->Coordinates[PosPairOriginal.first][PosPairOriginal.second].Piece);

		OriginalCoordinate.hasPiece = false;

		FinalCoordiante.hasPiece = true;

		auto test = FinalCoordiante - OriginalCoordinate;
		FinalCoordiante.Piece->TargetTranslateVector.x = FinalCoordiante.Piece->TargetTranslateVector.x + test.x;
		FinalCoordiante.Piece->TargetTranslateVector.z = FinalCoordiante.Piece->TargetTranslateVector.z - test.z;
		FinalCoordiante.Piece->TargetTranslateVector.y = FinalCoordiante.Piece->TargetTranslateVector.y + test.y;
		//FinalCoordiante.Piece.TargetTranslateVector.x = FinalCoordiante.Piece.TargetTranslateVector + (FinalCoordiante - OriginalCoordinate);
		FinalCoordiante.Piece->translating = true;
	}
	else {
		std::cout << "Invalid command or move" << std::endl;
	}
}

void Board::RemovePiece(std::pair<int, int>& PosPairOriginal) {
	auto& OriginalCoordinate = this->Coordinates[PosPairOriginal.first][PosPairOriginal.second];
	if (OriginalCoordinate.hasPiece) {
		OriginalCoordinate.hasPiece = false;
	}
	else {
		std::cout << "Invalid command or move" << std::endl;
	}
}

void Board::RenderBoard( glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID) {

	

	glm::mat4 ModelMatrix = glm::mat4(1.0);
	//ModelMatrix = glm::translate(ModelMatrix, glm::vec3(100.0f, -100.00f, -0.0f));

	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->Texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(this->TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_SHORT,   // type
		(void*)0           // element array buffer offset
	);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	
}

void Board:: CleanBoard() {
	glDeleteBuffers(1, &this->vertexbuffer);
	glDeleteBuffers(1, &this->uvbuffer);
	glDeleteBuffers(1, &this->normalbuffer);
	glDeleteBuffers(1, &this->elementbuffer);
	glDeleteTextures(1, &this->Texture);

}