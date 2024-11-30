/*
Author: Hsueh-Yuan Chou
Class: ECE6122
Last Date Modified: 11/30/2024
Description:
What is the purpose of this file?
ECE Chess Engine CPP file
*/

#include "ECE_ChessEngine.h"

/// <summary>
/// Initialize engine
/// </summary>
/// <returns>bool</returns>
bool ECE_ChessEngine::InitializeEngine() {

    c = bp::child(path, bp::std_in < os, bp::std_out > is);
    os << "uci\n" << std::flush;
    os << "isready\n" << std::flush;
    moves = "";
    return 0;
}

/// <summary>
/// Send move
/// </summary>
/// <param name="strMove">string move</param>
/// <returns>bool </returns>
bool ECE_ChessEngine::sendMove(const std::string& strMove) {
    std::vector<std::string> words;
    std::istringstream stream(strMove);
    std::string word;
    while (stream >> word) {
        words.push_back(word);
    }
    moves += " " + words[1];
    os << moveCommand + moves + "\n" << std::flush;
    return true;
}

/// <summary>
/// get response move
/// </summary>
/// <param name="strMove">string move</param>
/// <returns>bool</returns>
bool ECE_ChessEngine::getResponseMove(std::string& strMove) {
    os << "go\n" << std::flush;
    std::string line;
    std::string move_string;
    while (getline(is, line)) {
        if (!line.compare(0, 8, "bestmove")) {
            move_string = line;
            break;
        }
     }
    move_string = move_string.substr(9, move_string.size() - 9);
    std::vector<std::string> mv;
    boost::split(mv, move_string, boost::is_any_of(" "));
    std::string enginerResponse = mv.at(0);

    moves += " " + mv.at(0);

    auto pos1 = enginerResponse.substr(0, 2);
    auto pos2 = enginerResponse.substr(2, 4);

    PosPairOriginal = convertToCoordinate(pos1);
    PosPairFinal = convertToCoordinate(pos2);
    return true;
}