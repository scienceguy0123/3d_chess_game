/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 11/30/2024
Description:
What is the purpose of this file?
ECE Chess Engine header file
*/

#ifndef CHESSENGINE_H
#define CHESSENGINE_H
#include <boost/process.hpp>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <sstream>
#include "Helper.h"
namespace bp = boost::process;

/// <summary>
/// ECE chess engine class
/// </summary>
class ECE_ChessEngine {
	public:
		std::string path = "./dragon-64bit.exe";
		std::FILE* pipe;
		bp::ipstream is;
		bp::opstream os;
		bp::child c;
		std::string moves;
		std::string moveCommand = "position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1 moves ";
		bool InitializeEngine();

		bool sendMove(const std::string& strMove);
		
		bool getResponseMove(std::string& strMove);

};


#endif