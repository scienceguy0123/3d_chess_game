/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 11/30/2024
Description:
What is the purpose of this file?
Helper CPP file
*/

#include "Helper.h"


/// <summary>
/// check under attack
/// </summary>
/// <param name="board">board</param>
/// <param name="i">i</param>
/// <param name="j">j</param>
/// <param name="color">color</param>
/// <param name="debug">debug</param>
/// <param name="recursive">recursive</param>
/// <returns></returns>
bool checkUnderAttack(Board& board, int i, int j, bool color, bool debug, bool recursive) {
	

	int index = 1;
	// up
	while(i - index >= 0) {
		auto& coor = board.Coordinates[i - index][j];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& (
				coor.Piece->PieceName == "queen"
				|| coor.Piece->PieceName == "rook"
				|| (index == 1 && coor.Piece->PieceName == "king" && recursive)
				)
			
			) {
			if (!recursive) {
				return true;
			}
			else if (!checkUnderAttack(board, i - index, j, coor.Piece->color, debug, false)) {
				if (debug) {
					std::cout << i << " " << j << " is being attacked from up" << std::endl;
				}
				return true;
			}
		}
		else if (coor.hasPiece) {
			break;
		}
		index++;
	}

	index = 1;
	// down
	while (i + index <= 7) {
		auto& coor = board.Coordinates[i + index][j];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& (
				coor.Piece->PieceName == "queen"
				|| coor.Piece->PieceName == "rook"
				|| (index == 1 && coor.Piece->PieceName == "king" && recursive)
				)) {
			if (!recursive) {
				return true;
			}
			else if (!checkUnderAttack(board, i + index, j, coor.Piece->color, debug, false)) {
				if (debug) {
					std::cout << i << " " << j << " is being attacked from down" << std::endl;
				}
				return true;
			}
		}
		else if (coor.hasPiece) {
			break;
		}
		index++;
	}

	// right
	index = 1;
	while (j - index >= 0) {
		auto& coor = board.Coordinates[i][j - index];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& (
				coor.Piece->PieceName == "queen"
				|| coor.Piece->PieceName == "rook"
				|| (index == 1 && coor.Piece->PieceName == "king" && recursive)
				)) {
			
			if (!recursive) {
				return true;
			}
			else if (!checkUnderAttack(board, i, j - index, coor.Piece->color, debug, false)) {
				if (debug) {
					std::cout << i << " " << j << " is being attacked from right" << std::endl;
				}
				return true;
			}
			
		}
		else if (coor.hasPiece) {
			break;
		}
		index++;
	}

	//left
	index = 1;
	while (j + index <= 7) {
		auto& coor = board.Coordinates[i][j + index];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& (
				coor.Piece->PieceName == "queen"
				|| coor.Piece->PieceName == "rook"
				|| (index == 1 && coor.Piece->PieceName == "king" && recursive)
				)) {
		
			if (!recursive) {
				return true;
			}
			else if (!checkUnderAttack(board, i, j + index, coor.Piece->color, debug, false)) {
				if (debug) {
					std::cout << i << " " << j << " is being attacked from left" << std::endl;
				}
				return true;
			}
		}
		else if (coor.hasPiece) {
			break;
		}
		index++;
	}

	//upper right diagnal
	index = 1;
	while (
		i - index >= 0
		 && j - index >= 0 
	) {
		auto& coor = board.Coordinates[i - index][j - index];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& (
				coor.Piece->PieceName == "queen"
				|| coor.Piece->PieceName == "bishop"
				|| (index == 1 && coor.Piece->PieceName == "pawn")
				|| (index == 1 && coor.Piece->PieceName == "king" && recursive)
				)) {
			
			if (!recursive) {
				return true;
			}
			else if (!checkUnderAttack(board, i - index, j - index, coor.Piece->color, debug, false)) {
				if (debug) {
					std::cout << i << " " << j << " is being attacked from upper right diagnal" << std::endl;
				}
				return true;
			}
		}
		else if (coor.hasPiece) {
			break;
		}
		index++;
	}

	//upper left diagnal
	index = 1;
	while (
		i - index >= 0
		&& j + index <= 7
		) {
		auto& coor = board.Coordinates[i - index][j + index];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& (
				coor.Piece->PieceName == "queen"
				|| coor.Piece->PieceName == "bishop"
				|| (index == 1 && coor.Piece->PieceName == "pawn")
				|| (index == 1 && coor.Piece->PieceName == "king" && recursive)
				)) {
			
			if (!recursive) {
				return true;
			}
			else if (!checkUnderAttack(board, i - index, j + index, coor.Piece->color, debug, false)) {
				if (debug) {
					std::cout << i << " " << j << " is being attacked from upper left diagnal" << std::endl;
				}
				return true;
			}
		}
		else if (coor.hasPiece) {
			break;
		}
		index++;
	}


	//lower right diagnal
	index = 1;
	while (
		i + index <= 7
		&& j - index >= 0
		) {
		auto& coor = board.Coordinates[i + index][j - index];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& (
				coor.Piece->PieceName == "queen"
				|| coor.Piece->PieceName == "bishop"
				|| (index == 1 && coor.Piece->PieceName == "pawn")
				|| (index == 1 && coor.Piece->PieceName == "king" && recursive)
				)) {
			
			if (!recursive) {
				
				return true;
			}
			else if (!checkUnderAttack(board, i + index, j - index, coor.Piece->color, debug, false)) 
			{
				if (debug) {
					std::cout << i  << " " << j << " is being attacked from lower right diagnal" << std::endl;
				}
				return true;
			}
		}
		else if (coor.hasPiece) {
			break;
		}
		index++;
	}

	//lower left diagnal
	index = 1;
	while (
		i + index <= 7
		&& j + index <= 7
		) {
		auto& coor = board.Coordinates[i + index][j + index];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& (
				coor.Piece->PieceName == "queen"
				|| coor.Piece->PieceName == "bishop"
				|| (index == 1 && coor.Piece->PieceName == "pawn")
				|| (index == 1 && coor.Piece->PieceName == "king" && recursive)
				)) {
			
			if (!recursive) {
				if (debug) {
					std::cout << i << " " << j << " is being attacked from lower left diagnal" << std::endl;
				}
				return true;
			}
			else if (!checkUnderAttack(board, i + index, j + index, coor.Piece->color, debug, false)) {
				if (debug) {
					std::cout << i << " " << j << " is being attacked from lower left diagnal" << std::endl;
				}
				return true;
			}
		}
		else if (coor.hasPiece) {
			break;
		}
		index++;
	}

	//up two right one
	if (i - 2 >= 0 && j - 1 >= 0) {
		auto& coor = board.Coordinates[i - 2][j - 1];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& coor.Piece->PieceName == "knight"
			) {
			if (debug) {
				std::cout << i << " " << j << " is being attacked fromup two right one" << std :: endl;
			}
			if (!recursive) {
				return true;
			}
			else if (!checkUnderAttack(board, i - 2, j - 1, coor.Piece->color, debug, false)) {
				return true;
			}
		}
	}

	//up two left one
	if (i - 2 >= 0 && j + 1 <= 7) {
		auto& coor = board.Coordinates[i - 2][j + 1];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& coor.Piece->PieceName == "knight"
			) {
			if (!recursive) {
				return true;
			}
			else if (!checkUnderAttack(board, i - 2, j + 1, coor.Piece->color, debug, false)) {
				return true;
			}
		}
	}

	//up one left two
	if (i - 1 >= 0 && j - 2 >= 0) {
		auto& coor = board.Coordinates[i - 1][j - 2];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& coor.Piece->PieceName == "knight"
			) {
			if (!recursive) {
				return true;
			}
			else if (!checkUnderAttack(board, i - 1, j - 2, coor.Piece->color, debug, false)) {
				return true;
			}
		}
	}


	//up one right two
	if (i - 1 >= 0 && j + 2 <= 7) {
		auto& coor = board.Coordinates[i - 1][j + 2];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& coor.Piece->PieceName == "knight"
			) {
			if (!recursive) {
				return true;
			}
			else if (!checkUnderAttack(board, i - 1, j + 2, coor.Piece->color, debug, false)) {
				return true;
			}
		}
	}

	//down two left one
	if (i + 2 <= 7 && j - 1 >= 0) {
		auto& coor = board.Coordinates[i + 2][j - 1];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& coor.Piece->PieceName == "knight"
			) {
			if (!recursive) {
				return true;
			}
			else if (!checkUnderAttack(board, i + 2, j - 1, coor.Piece->color, debug, false)) {
				return true;
			}
		}
	}

	//down two right one
	if (i + 2 <= 7 && j + 1 <= 7) {
		auto& coor = board.Coordinates[i + 2][j + 1];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& coor.Piece->PieceName == "knight"
			) {
			if (!recursive) {
				return true;
			}
			else if (!checkUnderAttack(board, i + 2, j + 1, coor.Piece->color, debug, false)) {
				return true;
			}
		}
	}

	//down one left two
	if (i + 1 <= 7 && j - 2 <= 7) {
		auto& coor = board.Coordinates[i + 1][j - 2];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& coor.Piece->PieceName == "knight"
			) {
			if (!recursive) {
				return true;
			}
			else if (!checkUnderAttack(board, i + 1, j - 2, coor.Piece->color, debug, false)) {
				return true;
			}
		}
	}

	//down one left two
	if (i + 1 <= 7 && j + 2 <= 7) {
		auto& coor = board.Coordinates[i + 1][j + 2];
		if (
			coor.hasPiece
			&& coor.Piece->color != color
			&& coor.Piece->PieceName == "knight"
			) {
			if (!recursive) {
				return true;
			}
			else if (!checkUnderAttack(board, i + 1, j + 2, coor.Piece->color, debug, false)) {
				return true;
			}
		}
	}

	return false;

}

/// <summary>
/// check surrounding under attack
/// </summary>
/// <param name="board">board</param>
/// <param name="i">i</param>
/// <param name="j">j</param>
/// <param name="debug">debug</param>
/// <returns>bool</returns>
bool checkSurroundingUndetAttack(Board& board, int i, int j, bool debug ) {
	int underAttackCount = 0;
	int friendlyOccuipied = 0;
	if (i - 1 >= 0 && j - 1 >= 0) {
		if (
			checkUnderAttack(board, i - 1, j - 1, board.Coordinates[i][j].Piece->color, debug, false)) {
			underAttackCount++;
		}
		else if (
			board.Coordinates[i - 1][j - 1].hasPiece &&
			board.Coordinates[i][j].Piece->color == board.Coordinates[i - 1][j - 1].Piece->color
			) {
			friendlyOccuipied++;
		}
	}
	else {
		friendlyOccuipied++;
	}
	
	if (i - 1 >= 0) {
		if (checkUnderAttack(board, i - 1, j, board.Coordinates[i][j].Piece->color, debug, false)) {
			underAttackCount++;
		}
		else if (
			board.Coordinates[i - 1][j].hasPiece &&
			board.Coordinates[i][j].Piece->color == board.Coordinates[i - 1][j].Piece->color
			) {
			friendlyOccuipied++;
		}
	}
	else {
		friendlyOccuipied++;
	}

	if (i - 1 >= 0 && j + 1 <= 7) {
		if (checkUnderAttack(board, i - 1, j + 1, board.Coordinates[i][j].Piece->color, debug, false)) {
			underAttackCount++;
		}
		else if (
			board.Coordinates[i - 1][j + 1].hasPiece &&
			board.Coordinates[i][j].Piece->color == board.Coordinates[i - 1][j + 1].Piece->color
			) {
			friendlyOccuipied++;
		}
	}
	else {
		friendlyOccuipied++;
	}

	if (j - 1 >= 0) {
		if (checkUnderAttack(board, i, j - 1, board.Coordinates[i][j].Piece->color, debug, false)) {
			underAttackCount++;
		}
		else if (
			board.Coordinates[i][j - 1].hasPiece &&
			board.Coordinates[i][j].Piece->color == board.Coordinates[i][j - 1].Piece->color
			) {
			friendlyOccuipied++;
		}
		
	}
	else {
		friendlyOccuipied++;
	}


	if (j + 1 <= 7) {
		if (checkUnderAttack(board, i, j + 1, board.Coordinates[i][j].Piece->color, debug, false)) {
			underAttackCount++;
		}
		else if (
			board.Coordinates[i][j + 1].hasPiece &&
			board.Coordinates[i][j].Piece->color == board.Coordinates[i][j + 1].Piece->color
			) {
			friendlyOccuipied++;
		}
	}
	else {
		friendlyOccuipied++;
	}

	if (i + 1 <= 7 && j - 1 >=0) {
		if (checkUnderAttack(board, i + 1, j - 1, board.Coordinates[i][j].Piece->color, debug, false)) {
			underAttackCount++;
		}
		else if (
			board.Coordinates[i + 1][j - 1].hasPiece &&
			board.Coordinates[i][j].Piece->color == board.Coordinates[i + 1][j - 1].Piece->color
			) {
			friendlyOccuipied++;
		}
	}
	else {
		friendlyOccuipied++;
	}

	if (i + 1 <= 7) {
		if (checkUnderAttack(board, i + 1, j, board.Coordinates[i][j].Piece->color, debug, false)) {
			underAttackCount++;
		}
		else if (
			board.Coordinates[i + 1][j].hasPiece &&
			board.Coordinates[i][j].Piece->color == board.Coordinates[i + 1][j].Piece->color
			) {
			friendlyOccuipied++;
		}
	}
	else {
		friendlyOccuipied++;
	}

	if (i + 1 <= 7 && j +1 <=7) {
		if (checkUnderAttack(board, i + 1, j +1, board.Coordinates[i][j].Piece->color, debug, false)) {
			underAttackCount++;
		}
		else if (
			board.Coordinates[i + 1][j + 1].hasPiece &&
			board.Coordinates[i][j].Piece->color == board.Coordinates[i + 1][j + 1].Piece->color
			) {
			friendlyOccuipied++;
		}
	}
	else {
		friendlyOccuipied++;
	}

	if (debug) {
		std::cout << "underAttackCount is " << underAttackCount << " in check surrounding under attack" << std::endl;
		std::cout << "friendlyOccuipied is " << friendlyOccuipied << " in check surrounding under attack" << std::endl;
	}

	if (
		underAttackCount > 0 
		&& underAttackCount + friendlyOccuipied == 8) {
		return true;
	}
	else {
		return false;
	}
	
}

/// <summary>
/// check check mate
/// </summary>
/// <param name="board">board</param>
/// <param name="debug">debug</param>
/// <returns>bool</returns>
bool checkCheckMate(Board& board, bool debug) {
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			auto& coor = board.Coordinates[i][j];
			if (
				coor.hasPiece
				&& coor.Piece->PieceName == "king"
				&& checkUnderAttack(board, i, j, coor.Piece->color,false, false)
				) {
				if (debug) {
					std::cout << "check check mate" << std::endl;
				}
				if (checkSurroundingUndetAttack(board, i, j, debug)) {
					if (coor.Piece->color) {
						std::cout << "\nCheckMate, black wins" << std::endl;
					}
					else {
						std::cout << "\nCheckMate, white wins" << std::endl;
					}

					return true;
				}
			}
		}

	}



	return false;

}

/// <summary>
/// load pieces
/// </summary>
/// <param name="pieces">pieces</param>
/// <param name="programID">program id</param>
/// <param name="board">board</param>
void loadPieces(std::vector<Chess>& pieces, GLuint programID, Board& board) {

	char buffer[21];
	for (int i = 1; i < 9; i++) {
		std::sprintf(buffer, "Chess/pawn_w_%d.obj", i);
		board.Coordinates[1][i - 1].hasPiece = true;
		board.Coordinates[1][i - 1].Piece = new Pawn(buffer, programID, true, "woodlight0", "pawn");

		std::sprintf(buffer, "Chess/pawn_b_%d.obj", i);
		board.Coordinates[6][8 - i].hasPiece = true;
		board.Coordinates[6][8 - i].Piece = new Pawn(buffer, programID, false, "wooddark0", "pawn");

	
	}

	for (int i = 1; i < 3; i++) {
		std::sprintf(buffer, "Chess/rook_w_%d.obj", i);
		if (i == 1) {
			board.Coordinates[0][0].hasPiece = true;
			board.Coordinates[0][0].Piece = new Rook(buffer, programID, true, "woodlight1", "rook");
		}
		else {
			board.Coordinates[0][7].hasPiece = true;
			board.Coordinates[0][7].Piece = new Rook(buffer, programID, true, "woodlight1", "rook");
		}
		
		std::sprintf(buffer, "Chess/rook_b_%d.obj", i);
		if (i == 1) {
			board.Coordinates[7][7].hasPiece = true;
			board.Coordinates[7][7].Piece = new Rook(buffer, programID, false, "wooddark1", "rook");
		}
		else {
			board.Coordinates[7][0].hasPiece = true;
			board.Coordinates[7][0].Piece = new Rook(buffer, programID, false, "wooddark1", "rook");
		}
	}

	
	for (int i = 1; i < 3; i++) {
		std::sprintf(buffer, "Chess/knight_w_%d.obj", i);
		if (i == 1) {
			board.Coordinates[0][1].hasPiece = true;
			board.Coordinates[0][1].Piece = new Knight(buffer, programID, true, "woodlight2", "knight");
		}
		else {
			board.Coordinates[0][6].hasPiece = true;
			board.Coordinates[0][6].Piece = new Knight(buffer, programID, true, "woodlight2", "knight");
		}

		std::sprintf(buffer, "Chess/knight_b_%d.obj", i);
		if (i == 1) {
			board.Coordinates[7][6].hasPiece = true;
			board.Coordinates[7][6].Piece = new Knight(buffer, programID, false, "wooddark2", "knight");
		}
		else {
			board.Coordinates[7][1].hasPiece = true;
			board.Coordinates[7][1].Piece = new Knight(buffer, programID, false, "wooddark2", "knight");
		}
	}

	
	for (int i = 1; i < 3; i++) {
		std::sprintf(buffer, "Chess/bishop_w_%d.obj", i);
		if (i == 1) {
			board.Coordinates[0][2].hasPiece = true;
			board.Coordinates[0][2].Piece = new Bishop(buffer, programID, true, "woodlight3", "bishop");
		}
		else {
			board.Coordinates[0][5].hasPiece = true;
			board.Coordinates[0][5].Piece = new Bishop(buffer, programID, true, "woodlight3","bishop");
		}

		std::sprintf(buffer, "Chess/bishop_b_%d.obj", i);
		if (i == 1) {
			board.Coordinates[7][5].hasPiece = true;
			board.Coordinates[7][5].Piece = new Bishop(buffer, programID, false, "wooddark3","bishop");
		}
		else {
			board.Coordinates[7][2].hasPiece = true;
			board.Coordinates[7][2].Piece = new Bishop(buffer, programID, false, "wooddark3","bishop");
		}
	}

	
	std::sprintf(buffer, "Chess/queen_w.obj");
	board.Coordinates[0][3].hasPiece = true;
	board.Coordinates[0][3].Piece = new Queen(buffer, programID, true, "woodlight4", "queen");

	std::sprintf(buffer, "Chess/queen_b.obj");
	board.Coordinates[7][3].hasPiece = true;
	board.Coordinates[7][3].Piece = new Queen(buffer, programID, false, "wooddark4", "queen");

	std::sprintf(buffer, "Chess/king_w.obj");
	board.Coordinates[0][4].hasPiece = true;
	board.Coordinates[0][4].Piece = new King(buffer, programID, true, "woodlight5", "king");

	std::sprintf(buffer, "Chess/king_b.obj");
	board.Coordinates[7][4].hasPiece = true;
	board.Coordinates[7][4].Piece = new King(buffer, programID, false, "wooddark5", "king");
	
}

/// <summary>
/// input thread function
/// </summary>
void inputThreadFunction() {
	
	while (1) {
		if (!ReceiveCommand) {
			//if (showPrompt) {
				std::cout << "Please enter a command: ";
				std::getline(std::cin, InputCommand);
				ReceiveCommand = true;
			//}
		
		}
	}
}

/// <summary>
/// parse command
/// </summary>
/// <param name="board">board</param>
/// <param name="programID">program ID</param>
/// <returns>Command type</returns>
CommandType ParseCommand(Board& board, GLuint programID) {
	std::vector<std::string> words;
	std::istringstream stream(InputCommand);
	std::string word;
	
		

	while (stream >> word) { // Extract each word separated by space
		words.push_back(word);
	}


	if (words[0] == "camera" && words.size() == 4) {
		float polar = std::stof(words[1]);
		
		float azimuthal = std::stof(words[2]);
		float radial = std::stof(words[3]);

		if (polar < 10
			|| polar > 80
			|| azimuthal < 0
			|| azimuthal > 360
			|| radial < 0) {
			std::cout << "Invalid command or move" << std::endl;
			return Invalid;
		}

		//std::cout << "camera polar is " << polar << " azimuthal is " << azimuthal << " radial is " << radial << std::endl;
		updateProjectionMatrix(polar, azimuthal, radial);
		return Camera;
	}
	else if (words[0] == "light" && words.size() == 4) {
		float polar = std::stof(words[1]);
		float azimuthal = std::stof(words[2]);
		float radial = std::stof(words[3]);

		if (polar < 10
			|| polar > 80
			|| azimuthal < 0
			|| azimuthal > 360
			|| radial < 0) {
			std::cout << "Invalid command or move" << std::endl;
			return Invalid;
		}
		//std::cout << "light polar is " << polar << " azimuthal is " << azimuthal << " radial is " << radial << std::endl;
		updateLightPos(polar, azimuthal, radial);
		return Light;
	}

	else if (words[0] == "power" && words.size() == 2) {
		float power = std::stof(words[1]);
		

		if (power < 0) {
			std::cout << "Invalid command or move" << std::endl;
			return Invalid;
		}
		//std::cout << "light polar is " << polar << " azimuthal is " << azimuthal << " radial is " << radial << std::endl;
		updateLightPower(power);
		return Light;
	}

	else if (words[0] == "move" && words.size() == 2) {
		if (words[1].length() != 4) {
			std::cout << "Invalid command or move" << std::endl;
			return Invalid;
		}

		auto pos1 = words[1].substr(0, 2);
		auto pos2 = words[1].substr(2, 4);

		PosPairOriginal = convertToCoordinate(pos1);
		PosPairFinal = convertToCoordinate(pos2);

		if (
			PosPairOriginal.first == 8
			|| PosPairOriginal.second == 8
			|| PosPairFinal.first == 8
			|| PosPairFinal.second == 8
		) {
			std::cout << "Invalid command or move" << std::endl;
			return Invalid;
		}

		//std::cout << "pair row :" << PosPairOriginal.first << " column: " << PosPairOriginal.second << std::endl;
		//std::cout << "pair2 row :" << PosPairFinal.first << " column: " << PosPairFinal.second << std::endl;
		return Move;
	
	}

	else if (words[0] == "mv" && words.size() == 2) {
		if (words[1].length() != 4) {
			std::cout << "Invalid command or move" << std::endl;
			return Invalid;
		}

		auto pos1 = words[1].substr(0, 2);
		auto pos2 = words[1].substr(2, 4);

		PosPairOriginal = convertToCoordinate(pos1);
		PosPairFinal = convertToCoordinate(pos2);

		if (
			PosPairOriginal.first == 8
			|| PosPairOriginal.second == 8
			|| PosPairFinal.first == 8
			|| PosPairFinal.second == 8
			) {
			std::cout << "Invalid command or move" << std::endl;
			return Invalid;
		}

		//std::cout << "pair row :" << PosPairOriginal.first << " column: " << PosPairOriginal.second << std::endl;
		//std::cout << "pair2 row :" << PosPairFinal.first << " column: " << PosPairFinal.second << std::endl;
		return MV;

	}


	else if (words[0] == "rm" && words.size() == 2) {
		if (words[1].length() != 2) {
			std::cout << "Invalid command or move" << std::endl;
			return Invalid;
		}

		auto pos1 = words[1].substr(0, 2);
		

		PosPairOriginal = convertToCoordinate(pos1);
		

		if (
			PosPairOriginal.first == 8
			|| PosPairOriginal.second == 8
	
			) {
			std::cout << "Invalid command or move" << std::endl;
			return Invalid;
		}

		//std::cout << "pair row :" << PosPairOriginal.first << " column: " << PosPairOriginal.second << std::endl;
		return Remove;

	}

	else if (words[0] == "rma" ) {
		
		return RemoveAll;

	}

	else if (words[0] == "re") {

		return Restart;

	}
	else if (words[0] == "quit") {
		return Quit;
	}
	else if (words[0] == "add" && words.size() == 2) {
		char buffer[21];
		if (words[1] == "queen_b") {
			std::sprintf(buffer, "Chess/queen_b.obj");
			board.Coordinates[7][3].hasPiece = true;
			board.Coordinates[7][3].Piece = new Queen(buffer, programID, false, "wooddark4", "queen");
		}
		else if (words[1] == "queen_w") {
			std::sprintf(buffer, "Chess/queen_w.obj");
			board.Coordinates[0][3].hasPiece = true;
			board.Coordinates[0][3].Piece = new Queen(buffer, programID, true, "woodlight4", "queen");
		}
		else if (words[1] == "king_w") {
			std::sprintf(buffer, "Chess/king_w.obj");
			board.Coordinates[0][4].hasPiece = true;
			board.Coordinates[0][4].Piece = new King(buffer, programID, true, "woodlight5", "king");
		}
		else if (words[1] == "king_b") {
			std::sprintf(buffer, "Chess/king_b.obj");
			board.Coordinates[7][4].hasPiece = true;
			board.Coordinates[7][4].Piece = new King(buffer, programID, false, "wooddark5", "king");
		}
		else if (words[1] == "pawn_b") {
			std::sprintf(buffer, "Chess/pawn_b_1.obj");
			board.Coordinates[6][7].hasPiece = true;
			board.Coordinates[6][7].Piece = new Pawn(buffer, programID, false, "wooddark0", "pawn");
		}
		else if (words[1] == "pawn_w") {
			std::sprintf(buffer, "Chess/pawn_w_1.obj");
			board.Coordinates[1][0].hasPiece = true;
			board.Coordinates[1][0].Piece = new Pawn(buffer, programID, true, "woodlight0", "pawn");
		}
		else if (words[1] == "rook_w") {
			std::sprintf(buffer, "Chess/rook_w_1.obj");
			board.Coordinates[0][0].hasPiece = true;
			board.Coordinates[0][0].Piece = new Rook(buffer, programID, true, "woodlight1", "rook");
		}
		else if (words[1] == "rook_b") {
			std::sprintf(buffer, "Chess/rook_b_1.obj");
			board.Coordinates[7][7].hasPiece = true;
			board.Coordinates[7][7].Piece = new Rook(buffer, programID, false, "wooddark1", "rook");
		}
		else if (words[1] == "knight_w") {
			std::sprintf(buffer, "Chess/knight_w_1.obj");
			board.Coordinates[0][1].hasPiece = true;
			board.Coordinates[0][1].Piece = new Knight(buffer, programID, true, "woodlight2", "knight");
		}
		else if (words[1] == "knight_b") {
			std::sprintf(buffer, "Chess/knight_b_1.obj");
			board.Coordinates[7][6].hasPiece = true;
			board.Coordinates[7][6].Piece = new Knight(buffer, programID, false, "wooddark2", "knight");
		}
		else if (words[1] == "bishop_w") {
			std::sprintf(buffer, "Chess/bishop_w_1.obj");
			board.Coordinates[0][2].hasPiece = true;
			board.Coordinates[0][2].Piece = new Bishop(buffer, programID, true, "woodlight3", "bishop");
		}
		else if (words[1] == "bishop_b") {
			std::sprintf(buffer, "Chess/bishop_b_1.obj");
			board.Coordinates[7][5].hasPiece = true;
			board.Coordinates[7][5].Piece = new Bishop(buffer, programID, false, "wooddark3", "bishop");
		}
	}
	else if (words[0] == "checkm") {
		return CheckMate;
	}
	else if (words[0] == "coor" && words.size() == 2) {
		if (words[1].length() != 2) {
			std::cout << "Invalid command or move" << std::endl;
			return Invalid;
		}

		auto pos1 = words[1].substr(0, 2);


		PosPairOriginal = convertToCoordinate(pos1);


		if (
			PosPairOriginal.first == 8
			|| PosPairOriginal.second == 8

			) {
			std::cout << "Invalid command or move" << std::endl;
			return Invalid;
		}

		std::cout << "pair row :" << PosPairOriginal.first << " column: " << PosPairOriginal.second << std::endl;
		return Coor;

	}



	else {
		std::cout << "Invalid command or move" << std::endl;
	}
	return Invalid;
}

/// <summary>
/// convert to coordinate
/// </summary>
/// <param name="pos">pos</param>
/// <returns></returns>
std::pair<int, int> convertToCoordinate(std::string pos) {
	
	char row = pos[1];
	char column = pos[0];

	int row2;

	switch (row) {
		case '1': 
			row2 = 0;
			break;
		case '2':
			row2 = 1;
			break;
		case'3':
			row2 = 2;
			break;
		case '4':
			row2 = 3;
			break;
		case '5':
			row2 = 4;
			break;
		case '6':
			row2 = 5;
			break;
		case '7':
			row2 = 6;
			break;
		case '8':
			row2 = 7;
			break;
		default: 
			row2 = 8;
			break;
	}

	int column2;
	switch (column) {
		case 'a':
			column2 = 0;
			break;
		case 'b':
			column2 = 1;
			break;
		case 'c':
			column2 = 2;
			break;
		case 'd':
			column2 = 3;
			break;
		case 'e':
			column2 = 4;
			break;
		case 'f':
			column2 = 5;
			break;
		case 'g':
			column2 = 6;
			break;
		case 'h':
			column2 = 7;
			break;
		default:
			column2 = 8;
			break;
	}

	return std::make_pair(row2, column2);
}


