#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define TOKENS 8

enum type {
	_in,_out,_int,_float,_bool,_string,_endline,_comment
};

struct ref {
	std::vector<std::string> ref;
} int_,float_,bool_,string_;

std::string tokens[TOKENS] = { "in","out","int","float","bool","string","endline","//" };
std::string out;
std::string fileName;

std::vector<int> intReg;
std::vector<float> floatReg;
std::vector<bool> boolReg;
std::vector<std::string> strReg;

int main() {
	std::cout << "Enter the name of the .SEAL file you would like to run: ";
	std::cin >> fileName;
	std::cout << "\n";
	std::ifstream src(fileName);
	while (getline(src, out)) {
		for (int i = 0; i < TOKENS; ++i) {
			int checkChar = 0;
			int lineCol = 0;
			for (int j = 0; j < tokens[i].length(); ++j) {
				if (out[j] == tokens[i].at(j)) {
					++checkChar;
				}
				lineCol = j;
			}
			if (checkChar == tokens[i].length()) {
				switch (i) {
				case _in:
					if (out[lineCol + 1] == char(32)) {

					}
					break;
				case _out:
					if (out[lineCol + 1] == char(32)) {
						for (int c = lineCol + 2; c < out.length(); ++c) {
							if (out[c] == char(59)) {
								break;
							}
							std::cout << out[c];
						}
					}
					break;
				case _int:
					if (out[lineCol + 1] == char(32)) {
						bool cont = true;
						std::string varName;
						for (int c = lineCol + 2; c < out.length(); ++c) {
							if (out[c] == char(59)) {
								cont = false;
								intReg.push_back(0);
								break;
							}
							if (out[c] == char(32)) {
								break;
							}
							varName += out[c];
							lineCol = c;
						}
						int_.ref.push_back(varName);
						if (cont) {
							if (out[lineCol + 2] == char(61)) {
								lineCol += 4;
								std::string varVal;
								for (int c = lineCol; c < out.length(); ++c) {
									if (out[c] == char(59)) {
										break;
									}
									varVal += out[c];
								}
								intReg.push_back(std::stoi(varVal));
							}
						}
						std::cout << intReg[0];
					}
					break;
				case _float:
					if (out[lineCol + 1] == char(32)) {
						bool cont = true;
						std::string varName;
						for (int c = lineCol + 2; c < out.length(); ++c) {
							if (out[c] == char(59)) {
								cont = false;
								floatReg.push_back(0);
								break;
							}
							if (out[c] == char(32)) {
								break;
							}
							varName += out[c];
							lineCol = c;
						}
						float_.ref.push_back(varName);
						if (cont) {
							if (out[lineCol + 2] == char(61)) {
								lineCol += 4;
								std::string varVal;
								for (int c = lineCol; c < out.length(); ++c) {
									if (out[c] == char(59)) {
										break;
									}
									varVal += out[c];
								}
								floatReg.push_back(std::stof(varVal));
							}
						}
						std::cout << floatReg[0];
					}
					break;
				case _endline:
					std::cout << "\n";
					break;
				case _comment:
					break;
				}
			}
		}
	}
	src.close();
}