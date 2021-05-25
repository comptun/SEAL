#include <iostream>
#include <fstream>
#include <string>

#define TOKENS 5

enum type {
	_in,_out,_var,_endline,_comment
};

std::string tokens[TOKENS] = { "in","out","var","endline","//" };
std::string out;
std::string fileName;

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
				case _var:
					if (out[lineCol + 1] == char(32)) {

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