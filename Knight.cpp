#include "Knight.h"
#include "RenderBoard.h"


Knight::Knight(char* path, GLuint programID, bool color, std::string MaterialName) : Chess(path, programID, color, MaterialName) {
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
void Knight::Render (int index, glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID) {

	glm::mat4 ModelMatrix = glm::mat4(1.0);


	if (translating) {
		if (CurrentMoveStage == Rise) {
			this->CurrentTranslateVector.y = this->CurrentTranslateVector.y + Speed;
			if (this->CurrentTranslateVector.y > 10) {
				this->CurrentTranslateVector.y = 10;
				CurrentMoveStage = Translate;
			}
		}
		else if (CurrentMoveStage == Translate) {
			this->TargetTranslateVector.y = this->TargetTranslateVector.y + 10;
			if (calculateCurrentTranslateVector()) {
				CurrentMoveStage = Fall;
			}
		}
		else if (CurrentMoveStage == Fall) {
			this->CurrentTranslateVector.y = this->CurrentTranslateVector.y - Speed;
			if (this->CurrentTranslateVector.y < 0) {
				this->CurrentTranslateVector.y = 0;
				CurrentMoveStage = Rise;
				this->translating = false;
			}
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

