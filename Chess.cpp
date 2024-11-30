/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 10/18/2024
Description:
Class for Chess
*/
#include "Chess.h"
#include "RenderBoard.h"
/// <summary>
/// Constructor
/// </summary>
Chess::Chess() {};



/// <summary>
/// Constructor
/// </summary>
/// <param name="path">path</param>
/// <param name="programID">program id</param>
/// <param name="color">color</param>
/// <param name="MaterialName">material name</param>
/// <param name="PieceName">peice name</param>
Chess::Chess(
	std::string path,
	GLuint programID,
	bool color,
	std::string MaterialName,
	std::string PieceName
) 
{
	this->color = color;
	this->MaterialName = MaterialName;
	this->PieceName = PieceName;

	bool res = loadAssImpChess(path.c_str(), this->indices, this->indexed_vertices, this->indexed_uvs, this->indexed_normals);
	//GLuint vertexbuffer;
	glGenBuffers(1, &this->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->indexed_vertices.size() * sizeof(glm::vec3), &this->indexed_vertices[0], GL_STATIC_DRAW);



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

	auto material = loadMTL("Chess/chess.mtl")[MaterialName];

	auto test1 = glGetUniformLocation(programID, "ambient");
	auto test2 = glGetUniformLocation(programID, "diffuse");
	auto test3 = glGetUniformLocation(programID, "specular");

	glUniform3fv(glGetUniformLocation(programID, "ambient"), 1, &material.ambient[0]);
	glUniform3fv(glGetUniformLocation(programID, "diffuse"), 1, &material.diffuse[0]);
	glUniform3fv(glGetUniformLocation(programID, "specular"), 1, &material.specular[0]);



	// Load the texture
	//GLuint Texture;
	this->Texture = loadTextureChess(("Chess/" + material.textureMap).c_str());

	// Get a handle for our "myTextureSampler" uniform
	//GLuint TextureID;
	this->TextureID = glGetUniformLocation(programID, "myTextureSampler");

	this->CurrentTranslateVector = glm::vec3(0, 0, 0);
	this->TargetTranslateVector = glm::vec3(0, 0, 0);
}

/// <summary>
/// display
/// </summary>
void Chess::display() {
	//std::cout << "TargetTranslateVector.x: " << TargetTranslateVector.x << " TargetTranslateVector.y: " << TargetTranslateVector.y << " TargetTranslateVector.z: " << TargetTranslateVector.z << std::endl;
	//std::cout << "CurrentTranslateVector.x: " << CurrentTranslateVector.x << " CurrentTranslateVector.y: " << CurrentTranslateVector.y << " CurrentTranslateVector.z: " << CurrentTranslateVector.z << std::endl;

}

/// <summary>
/// calculate Current translate vector
/// </summary>
/// <returns>bool</returns>
bool Chess::calculateCurrentTranslateVector() {

	//this->display();
	bool XDone = false;
	bool YDone = true;
	bool ZDone = false;;
	if (TargetTranslateVector.x < CurrentTranslateVector.x) {
		CurrentTranslateVector.x -= Speed;
		if (CurrentTranslateVector.x < TargetTranslateVector.x) {
			CurrentTranslateVector.x = TargetTranslateVector.x;
			XDone = true;
		}
	}
	else if (TargetTranslateVector.x > CurrentTranslateVector.x) {
		CurrentTranslateVector.x += Speed;
		if (CurrentTranslateVector.x > TargetTranslateVector.x) {
			CurrentTranslateVector.x = TargetTranslateVector.x;
			XDone = true;
		}
	}
	else {
		XDone = true;
	}

	
	
	if (TargetTranslateVector.z < CurrentTranslateVector.z) {
		//std::cout << "TargetTranslateVector.z: " << TargetTranslateVector.z << " CurrentTranslateVector.z: " << CurrentTranslateVector.z << std::endl;
		CurrentTranslateVector.z -= Speed;
		if (CurrentTranslateVector.z < TargetTranslateVector.z) {
			CurrentTranslateVector.z = TargetTranslateVector.z;
			ZDone = true;
		}
	}
	else if (TargetTranslateVector.z > CurrentTranslateVector.z) {
		//std::cout << "TargetTranslateVector.z: " << TargetTranslateVector.z << " CurrentTranslateVector.z: " << CurrentTranslateVector.z << std::endl;
		CurrentTranslateVector.z += Speed;
		if (CurrentTranslateVector.z > TargetTranslateVector.z) {
			CurrentTranslateVector.z = TargetTranslateVector.z;
			ZDone = true;
		}
	}
	else {
		ZDone = true;
	}

	return XDone && YDone && ZDone;
}

/// <summary>
/// move constructor
/// </summary>
/// <param name="other">other</param>
Chess::Chess(Chess&& other) noexcept :
	indices(std::move(other.indices)),
	indexed_vertices(std::move(other.indexed_vertices)),
	indexed_uvs(std::move(other.indexed_uvs)),
	indexed_normals(std::move(other.indexed_normals)),
	vertexbuffer(other.vertexbuffer),
	uvbuffer(other.uvbuffer),
	normalbuffer(other.normalbuffer),
	elementbuffer(other.elementbuffer),
	Texture(other.Texture),
	TextureID(other.TextureID),
	MeshName(std::move(other.MeshName)),
	MaterialName(std::move(other.MaterialName)),
	PieceName(std::move(other.PieceName)),
	translating(other.translating),
	TargetTranslateVector(std::move(other.TargetTranslateVector)),
	CurrentTranslateVector(std::move(other.CurrentTranslateVector)),
	ScaleFactor(std::move(other.ScaleFactor)),
	color(other.color),
	Speed(other.Speed) 
	{
		//std::cout << "move constructor is called" << std::endl;

	}

/// <summary>
///  move assignment
/// </summary>
/// <param name="other">other </param>
/// <returns></returns>
Chess& Chess::operator=(Chess&& other) noexcept {
	if (this != &other) {
		indices = std::move(other.indices);
		indexed_vertices = std::move(other.indexed_vertices);
		indexed_uvs = std::move(other.indexed_uvs);
		indexed_normals = std::move(other.indexed_normals);
		vertexbuffer = other.vertexbuffer;
		uvbuffer = other.uvbuffer;
		normalbuffer = other.normalbuffer;
		elementbuffer = other.elementbuffer;
		Texture = other.Texture;
		TextureID = other.TextureID;
		MeshName = std::move(other.MeshName);
		MaterialName = std::move(other.MaterialName);
		PieceName = std::move(other.PieceName);
		translating = other.translating;
		TargetTranslateVector = std::move(other.TargetTranslateVector);
		CurrentTranslateVector = std::move(other.CurrentTranslateVector);
		ScaleFactor = std::move(other.ScaleFactor);
		color = other.color;
		Speed = other.Speed;
	}
	//std::cout << "move assignment is called" << std::endl;
	return *this;
}


/// <summary>
/// check move valid
/// </summary>
/// <param name="board">board</param>
/// <param name="PosPairOriginal">PosPairOriginal</param>
/// <param name="PosPairFinal">PosPairFinal</param>
/// <returns>bool</returns>
bool Chess::CheckMoveValid(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) {
	return true;
}

/// <summary>
/// Render
/// </summary>
/// <param name="index">index</param>
/// <param name="ProjectionMatrix">project matrix</param>
/// <param name="ViewMatrix">view matrix</param>
/// <param name="MatrixID">matrix id</param>
/// <param name="ViewMatrixID">view material id</param>
/// <param name="ModelMatrixID">model matrix id</param>
void Chess::Render(int index, glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID) {

	glm::mat4 ModelMatrix = glm::mat4(1.0);

	
	if (translating) {
		if (calculateCurrentTranslateVector()) {
			this->translating = false;
		}
	}

	// Translate the model on the X-axis (dynamic translation example)
	ModelMatrix = glm::translate(ModelMatrix, this->CurrentTranslateVector);
	
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

	glActiveTexture(GL_TEXTURE1 + index);

	glBindTexture(GL_TEXTURE_2D, this->Texture);
	glUniform1i(this->TextureID, 1 + index);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, 9);
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
	//glBindBuffer(GL_ARRAY_BUFFER, 10);
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
	//glBindBuffer(GL_ARRAY_BUFFER, 11); 
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


};

/// <summary>
/// clean
/// </summary>
void Chess::clean() {
	glDeleteBuffers(1, &this->vertexbuffer);
	glDeleteBuffers(1, &this->uvbuffer);
	glDeleteBuffers(1, &this->normalbuffer);
	glDeleteBuffers(1, &this->elementbuffer);
	glDeleteTextures(1, &this->Texture);
};

/// <summary>
/// vertical move
/// </summary>
/// <param name="PosPairOriginal">PosPairOriginal</param>
/// <param name="PosPairFinal">PosPairFinal</param>
/// <param name="direction">direction</param>
/// <param name="MaxStep">MaxStep</param>
/// <returns></returns>
bool Chess::VeriticalMove(std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal, int direction,  int MaxStep  ) {
	//direction 1 is from black to white
	// direction 2 is from white to black
	// direction 3 is all direction
	if (MaxStep == 0) {
		if (PosPairFinal.second == PosPairOriginal.second) {
			return true;
		}
		return false;
	}
	else {
		if (direction == 1) {
			//std::cout << "black to white vertical move " << MaxStep << std::endl;

			if (
				abs(PosPairFinal.first - PosPairOriginal.first ) <= MaxStep
				&& (PosPairFinal.first - PosPairOriginal.first) < 0
				) {
				return true;
			}
			//std::cout << "black to white vertical move return false " << MaxStep << std::endl;

			return false;
		}
		else if (direction == 2) {
			//std::cout << "white to black vertical move " << std::endl;

			if (
				abs(PosPairFinal.first - PosPairOriginal.first) <= MaxStep
				&& (PosPairFinal.first - PosPairOriginal.first) > 0
				) {
				return true;
			}
			return false;
		}
		else {
			if (
				abs(PosPairFinal.first - PosPairOriginal.first ) > MaxStep
				) {
				return false;
			}
			return true;
		}

	}
};

/// <summary>
/// Horizontal move
/// </summary>
/// <param name="PosPairOriginal">PosPairOriginal</param>
/// <param name="PosPairFinal">PosPairFinal</param>
/// <param name="MaxStep">MaxStep</param>
/// <returns></returns>
bool Chess::HorizontalMove(std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal, int MaxStep) {
	if (MaxStep == 0) {
		if (PosPairFinal.first == PosPairOriginal.first) {
			return true;
		}
		return false;
	}
	else {
		if (
			PosPairFinal.first == PosPairOriginal.first
			&& abs(PosPairFinal.second - PosPairOriginal.second) <= MaxStep) {
			return true;
		}
		return false;
	}
	
}

/// <summary>
/// Diagnal Move
/// </summary>
/// <param name="PosPairOriginal">PosPairOriginal</param>
/// <param name="PosPairFinal">PosPairFinal</param>
/// <param name="direction">direction</param>
/// <param name="MaxStep">MaxStep</param>
/// <returns>bool</returns>
bool Chess::DiagonalMove(std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal, int direction , int MaxStep ) {
	// direction 0: only from black to white
	// direction 1: only from white to black
	// direction 2: all direction
	//std::cout << "PosPairOriginal.first: " << PosPairOriginal.first << " PosPairOriginal.second: " << PosPairOriginal.second << std::endl;
	//std::cout << "PosPairFinal.first: " << PosPairFinal.first << " PosPairFinal.second: " << PosPairFinal.second << std::endl;

	if (direction == 1){
		for (int i = 1; i < MaxStep + 1; i++) {
			if (
				(PosPairOriginal.first + i == PosPairFinal.first
					&& PosPairOriginal.second + i == PosPairFinal.second)
				||
				(PosPairOriginal.first + i == PosPairFinal.first
					&& PosPairOriginal.second - i == PosPairFinal.second)
			) {
				//std::cout << "DiagonalMove d1 returns true" << std::endl;
				return true;
			}
		}
		return false;
	}
	else if (direction == 0) {
		for (int i = 1; i < MaxStep + 1; i++) {
			if (
				(PosPairOriginal.first - i == PosPairFinal.first
					&& PosPairOriginal.second - i == PosPairFinal.second)
				||
				(PosPairOriginal.first - i == PosPairFinal.first
					&& PosPairOriginal.second + i == PosPairFinal.second)
				) {
				//std::cout << "DiagonalMove d0 returns true" << std::endl;
				return true;
			}
		}
		return false;
	}
	else {
		for (int i = 1; i < MaxStep + 1; i++) {
			if (
				(PosPairOriginal.first + i == PosPairFinal.first
					&& PosPairOriginal.second + i == PosPairFinal.second)
				||
				(PosPairOriginal.first - i == PosPairFinal.first
					&& PosPairOriginal.second - i == PosPairFinal.second)
				||
				(PosPairOriginal.first - i == PosPairFinal.first
					&& PosPairOriginal.second + i == PosPairFinal.second)
				||
				(PosPairOriginal.first + i == PosPairFinal.first
					&& PosPairOriginal.second - i == PosPairFinal.second)
			) {
				return true;
			}
		}
		return false;
	}
}

/// <summary>
/// Piece in route
/// </summary>
/// <param name="board">board</param>
/// <param name="PosPairOriginal">PosPairOriginal</param>
/// <param name="PosPairFinal">PosPairFinal</param>
/// <returns>bool</returns>
bool Chess::PieceInRoute(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal) {
	int i = 0;

	int IncrementX;
	int IncrementY;
	
	int currentX = PosPairOriginal.first;
	int currentY = PosPairOriginal.second;


	if (PosPairOriginal.first < PosPairFinal.first) {
		IncrementX = 1;
	}
	else {
		IncrementX = -1;
	}

	if (PosPairOriginal.second < PosPairFinal.second) {
		IncrementY = 1;
	}
	else {
		IncrementY = -1;
	}

	
	while (
		(currentX != PosPairFinal.first
			)
		|| 
		(currentY != PosPairFinal.second
			)
	) {
		if (currentX != PosPairFinal.first) {
			currentX += IncrementX;
		}

		if (currentY != PosPairFinal.second) {
			currentY += IncrementY;
		}

		//std::cout << "PieceInRoute currentX: " << currentX << " currentY: " << currentY << std::endl;


		if (
			currentX == PosPairFinal.first
			&& currentY == PosPairFinal.second
		) {
			return false;
		}


		if (
			board.Coordinates[currentX][currentY].hasPiece
		) {
			return true;
		}

		
	}

	return false;
}

