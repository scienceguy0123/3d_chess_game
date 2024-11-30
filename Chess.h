/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 10/18/2024
Description:
Class for Chess
*/

#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h> // For OpenGL types like GLuint
#include "common/objloader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "common/texture.hpp"
#include <utility>
// Parent class Chess

class Board;
/// <summary>
/// Class for chess
/// </summary>
class Chess {
public:
    // Data members
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

    std::string MeshName;
    std::string MaterialName;

    std::string PieceName;
    
    bool translating = false ;
    glm::vec3 TargetTranslateVector;
    glm::vec3 CurrentTranslateVector;

    float ScaleFactor = 0.2f;

    bool color; //0 is black, 1 is white

    float Speed = 0.3;

    /// <summary>
    /// constructor
    /// </summary>
    Chess();
   

    Chess(
        std::string path,
        GLuint programID,
        bool color,
        std::string MaterialName,
        std::string PieceName
   );

   Chess(Chess&& other) noexcept;

   Chess& operator=(Chess&& other) noexcept;

    virtual void Render(int index, glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, GLuint MatrixID, GLuint ViewMatrixID, GLuint ModelMatrixID);

    virtual bool CheckMoveValid(Board& board,  std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal);


    bool calculateCurrentTranslateVector();

    bool VeriticalMove(std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal, int direction = 2, int MaxStep = 0  );
    

    bool HorizontalMove(std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal, int MaxStep = 0);

    bool DiagonalMove(std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal, int direction = 2, int MaxStep = 15);

    bool PieceInRoute(Board& board, std::pair<int, int>& PosPairOriginal, std::pair<int, int>& PosPairFinal);


    /// <summary>
    /// clean
    /// </summary>
    void clean();

    void display();
};

#endif