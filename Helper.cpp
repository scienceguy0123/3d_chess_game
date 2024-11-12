#include "Helper.h"

void loadPieces(std::vector<Chess>& pieces, GLuint programID, Board& board) {

	char buffer[21];
	for (int i = 1; i < 9; i++) {
		std::sprintf(buffer, "Chess/pawn_w_%d.obj", i);
		board.Coordinates[1][i - 1].hasPiece = true;
		board.Coordinates[1][i - 1].Piece = new Pawn(buffer, programID, true, "woodlight0");

		std::sprintf(buffer, "Chess/pawn_b_%d.obj", i);
		board.Coordinates[6][8 - i].hasPiece = true;
		board.Coordinates[6][8 - i].Piece = new Pawn(buffer, programID, false, "wooddark0");

	
	}

	for (int i = 1; i < 3; i++) {
		std::sprintf(buffer, "Chess/rook_w_%d.obj", i);
		if (i == 1) {
			board.Coordinates[0][0].hasPiece = true;
			board.Coordinates[0][0].Piece = new Rook(buffer, programID, true, "woodlight1");
		}
		else {
			board.Coordinates[0][7].hasPiece = true;
			board.Coordinates[0][7].Piece = new Rook(buffer, programID, false, "woodlight1");
		}
		
		std::sprintf(buffer, "Chess/rook_b_%d.obj", i);
		if (i == 1) {
			board.Coordinates[7][7].hasPiece = true;
			board.Coordinates[7][7].Piece = new Rook(buffer, programID, true, "wooddark1");
		}
		else {
			board.Coordinates[7][0].hasPiece = true;
			board.Coordinates[7][0].Piece = new Rook(buffer, programID, false, "wooddark1");
		}
	}

	
	for (int i = 1; i < 3; i++) {
		std::sprintf(buffer, "Chess/knight_w_%d.obj", i);
		if (i == 1) {
			board.Coordinates[0][1].hasPiece = true;
			board.Coordinates[0][1].Piece = new Knight(buffer, programID, true, "woodlight2");
		}
		else {
			board.Coordinates[0][6].hasPiece = true;
			board.Coordinates[0][6].Piece = new Knight(buffer, programID, false, "woodlight2");
		}

		std::sprintf(buffer, "Chess/knight_b_%d.obj", i);
		if (i == 1) {
			board.Coordinates[7][6].hasPiece = true;
			board.Coordinates[7][6].Piece = new Knight(buffer, programID, true, "wooddark2");
		}
		else {
			board.Coordinates[7][1].hasPiece = true;
			board.Coordinates[7][1].Piece = new Knight(buffer, programID, false, "wooddark2");
		}
	}

	
	for (int i = 1; i < 3; i++) {
		std::sprintf(buffer, "Chess/bishop_w_%d.obj", i);
		if (i == 1) {
			board.Coordinates[0][2].hasPiece = true;
			board.Coordinates[0][2].Piece = new Bishop(buffer, programID, true, "woodlight3");
		}
		else {
			board.Coordinates[0][5].hasPiece = true;
			board.Coordinates[0][5].Piece = new Bishop(buffer, programID, false, "woodlight3");
		}

		std::sprintf(buffer, "Chess/bishop_b_%d.obj", i);
		if (i == 1) {
			board.Coordinates[7][5].hasPiece = true;
			board.Coordinates[7][5].Piece = new Bishop(buffer, programID, true, "wooddark3");
		}
		else {
			board.Coordinates[7][2].hasPiece = true;
			board.Coordinates[7][2].Piece = new Bishop(buffer, programID, false, "wooddark3");
		}
	}

	
	std::sprintf(buffer, "Chess/queen_w.obj");
	board.Coordinates[0][4].hasPiece = true;
	board.Coordinates[0][4].Piece = new Queen(buffer, programID, true, "woodlight4");

	std::sprintf(buffer, "Chess/queen_b.obj");
	board.Coordinates[7][4].hasPiece = true;
	board.Coordinates[7][4].Piece = new Queen(buffer, programID, false, "wooddark4");

	std::sprintf(buffer, "Chess/king_w.obj");
	board.Coordinates[0][3].hasPiece = true;
	board.Coordinates[0][3].Piece = new King(buffer, programID, true, "woodlight5");

	std::sprintf(buffer, "Chess/king_b.obj");
	board.Coordinates[7][3].hasPiece = true;
	board.Coordinates[7][3].Piece = new King(buffer, programID, false, "wooddark5");
	
}


void inputThreadFunction() {
	
	while (1) {
		if (!ReceiveCommand) {
			std::cout << "Please enter a command: ";
			std::getline(std::cin, InputCommand);
			ReceiveCommand = true;
		}
	}
}

CommandType ParseCommand() {
	std::vector<std::string> words;
	std::istringstream stream(InputCommand);
	std::string word;
	
		

	while (stream >> word) { // Extract each word separated by space
		words.push_back(word);
	}

	std::cout << "words.size(): " << words.size() << std::endl;

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

		std::cout << "camera polar is " << polar << " azimuthal is " << azimuthal << " radial is " << radial << std::endl;
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
		std::cout << "light polar is " << polar << " azimuthal is " << azimuthal << " radial is " << radial << std::endl;
		updateLightPos(polar, azimuthal, radial);
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

		std::cout << "pair row :" << PosPairOriginal.first << " column: " << PosPairOriginal.second << std::endl;
		std::cout << "pair2 row :" << PosPairFinal.first << " column: " << PosPairFinal.second << std::endl;
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

		std::cout << "pair row :" << PosPairOriginal.first << " column: " << PosPairOriginal.second << std::endl;
		std::cout << "pair2 row :" << PosPairFinal.first << " column: " << PosPairFinal.second << std::endl;
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

		std::cout << "pair row :" << PosPairOriginal.first << " column: " << PosPairOriginal.second << std::endl;
		return Remove;

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


