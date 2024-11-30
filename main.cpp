/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 10/18/2024
Description:
Main file
*/

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <thread>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "RenderBoard.h"
#include "Chess.h"
#include "Pawn.h"

#include <thread>   // For std::this_thread::sleep_for
#include <chrono>   // For std::chrono::seconds, etc.

#include <vector>
#include "Helper.h"

#include "GlobalVariables.h"
#include "ECE_ChessEngine.h"

bool ReceiveCommand;
std::string InputCommand;
std::pair<int, int> PosPairOriginal;
std::pair<int, int> PosPairFinal;
bool showPrompt;

/// <summary>
/// main function
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int main(void)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);


	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Final project", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	if (!glfwGetCurrentContext()) {
		std::cerr << "No valid OpenGL context!" << std::endl;
	}
	
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited movement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);
	 
	// Dark blue background
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it is closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");


	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
	
	Board board = Board(programID);

	std::vector<Chess> pieces;
	loadPieces(pieces, programID, board);



	ECE_ChessEngine engine;
	engine.InitializeEngine();



	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
	GLuint ModeID = glGetUniformLocation(programID, "mode");
	GLuint lightPowerId = glGetUniformLocation(programID, "LightPower2");
	bool Mode = true;

	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	

	bool firstRun = true;

	ReceiveCommand = false;
	std::thread inputThread(inputThreadFunction);
	
	bool checkMated = false;
	bool animating = false;

	bool engineRound = false;
	int animatingCounter = 0;
	showPrompt = true;


	do {

		if (!checkMated) {
			if (checkCheckMate(board)) {
				checkMated = true;
				std::cout << "Please enter quit to exit program: " << std::endl;
			}
		}

		if (firstRun) {
			defaultProjectionMatrix();
			defaultLightPos();
		}

		firstRun = false;

		if (animating) {
			if (animatingCounter >= 100) {
				animatingCounter = 0;
				animating = false;
			}
			animatingCounter += 1;
		}

		if (!animating && engineRound && !checkMated) {
			std::string response;
			engine.getResponseMove(response);
		
			
			board.MovePiece(PosPairOriginal, PosPairFinal);
			engineRound = false;
			animating = true;
		}

		if (!animating && ReceiveCommand && !engineRound ) {
			showPrompt = true;
			auto CommandType = ParseCommand(board, programID);

			if (CommandType == Move && !checkMated) {
				if (!board.MovePiece(PosPairOriginal, PosPairFinal)) {
					ReceiveCommand = false;
					continue;
				}
				engine.sendMove(InputCommand); 
				engineRound = true;
				animating = true;
				showPrompt = false;
			}

			else if (CommandType == MV) {
				board.MvPiece(PosPairOriginal, PosPairFinal);
			}

			else if (CommandType == Remove) {
				board.RemovePiece(PosPairOriginal);
			}

			else if (CommandType == RemoveAll) {
				board.RemoveAll();
			}

			else if (CommandType == CheckMate) {
				std::cout << engine.moves << std::endl;
				checkCheckMate(board, true);
			}

			else if (CommandType == Restart) {
				checkMated = false;
				board.RemoveAll();
				loadPieces(pieces, programID, board);
			}
			else if (CommandType == Quit) {
				glfwTerminate();
				return 0;
			}
			
			ReceiveCommand = false;
			
			
		}

	

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			if (glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE) {
				Mode = !Mode;
				std::cout << "pressed L" << std::endl;
				//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
			
		}

		glUseProgram(programID);
		
		glUniform1i(ModeID, Mode); 
		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs2();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();

		

		glm::vec3 lightPos = getLightPos();
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);



		glUniform1f(lightPowerId, getLightPower());

		board.RenderBoard(ProjectionMatrix, ViewMatrix, MatrixID, ViewMatrixID, ModelMatrixID);

		int index = 1;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board.Coordinates[i][j].hasPiece) {
					board.Coordinates[i][j].Piece->Render(index, ProjectionMatrix, ViewMatrix, MatrixID, ViewMatrixID, ModelMatrixID);
					
					index++;
				}
			}

		}



		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	board.CleanBoard();

	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();
	
	return 0;
}

