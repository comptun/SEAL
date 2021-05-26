#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define TOKENS 8

enum type {
	_inp,_out,_int,_float,_bool,_string,_endline,_comment
};

struct ref {
	std::vector<std::string> ref;
} int_,float_,bool_,string_;

std::string tokens[TOKENS] = { "inp","out","int","float","bool","string","endline","//" };
std::string out;
std::string fileName;

std::vector<int> intReg;
std::vector<float> floatReg;
std::vector<bool> boolReg;
std::vector<std::string> stringReg;

bool isNum(std::string const& a) {
	int checkDigit = 0;
	bool allowedPeriod = true;
	for (int i = 0; i < a.length(); ++i) {
		if (isdigit(a[i])) {
			++checkDigit;
		}
		if (a[i] == char(46) && allowedPeriod) {
			++checkDigit;
			allowedPeriod = false;
		}
	}
	if (checkDigit == a.length()) {
		return true;
	}
	else {
		return false;
	}
}

bool to_bool(std::string const& a) {
	if (a == "true") {
		return true;
	}
	else {
		return false;
	}
}

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
				case _inp:
					if (out[lineCol + 1] == char(32)) {
						std::string varName;
						for (int c = lineCol + 2; c < out.length(); ++c) {
							if (out[c] == char(59)) {
								break;
							}
							varName += out[c];
						}
						for (int v = 0; v < int_.ref.size(); ++v) {
							if (int_.ref[v] == varName) {
								int input = 0;
								std::cin >> input;
								intReg.at(v) = int(input);
							}
						}
						for (int v = 0; v < float_.ref.size(); ++v) {
							if (float_.ref[v] == varName) {
								float input = 0;
								std::cin >> input;
								floatReg.at(v) = float(input);
							}
						}
						for (int v = 0; v < bool_.ref.size(); ++v) {
							if (bool_.ref[v] == varName) {
								bool input = false;
								std::cin >> input;
								boolReg.at(v) = input;
							}
						}
						for (int v = 0; v < string_.ref.size(); ++v) {
							if (string_.ref[v] == varName) {
								std::string input;
								std::cin >> input;
								stringReg.at(v) = input;
							}
						}
					}
					break;
				case _out:
					if (out[lineCol + 1] == char(32)) {
						std::string outStr;
						for (int c = lineCol + 2; c < out.length(); ++c) {
							if (out[c] == char(59)) {
								break;
							}
							outStr += out[c];
						}
						if (isNum(outStr)) {
							for (int c = lineCol + 2; c < out.length(); ++c) {
								if (out[c] == char(59)) {
									break;
								}
								std::cout << out[c];
							}
						}
						else {
							for (int v = 0; v < int_.ref.size(); ++v) {
								if (int_.ref[v] == outStr) {
									std::cout << intReg[v];
								}
							}
							for (int v = 0; v < float_.ref.size(); ++v) {
								if (float_.ref[v] == outStr) {
									std::cout << floatReg[v];
								}
							}
							for (int v = 0; v < bool_.ref.size(); ++v) {
								if (bool_.ref[v] == outStr) {
									std::cout << boolReg[v];
								}
							}
							for (int v = 0; v < string_.ref.size(); ++v) {
								if (string_.ref[v] == outStr) {
									std::cout << stringReg[v];
								}
							}
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
					}
					break;
				case _bool:
					if (out[lineCol + 1] == char(32)) {
						bool cont = true;
						std::string varName;
						for (int c = lineCol + 2; c < out.length(); ++c) {
							if (out[c] == char(59)) {
								cont = false;
								boolReg.push_back(false);
								break;
							}
							if (out[c] == char(32)) {
								break;
							}
							varName += out[c];
							lineCol = c;
						}
						bool_.ref.push_back(varName);
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
								boolReg.push_back(to_bool(varVal));
							}
						}
					}
					break;
				case _string:
					if (out[lineCol + 1] == char(32)) {
						bool cont = true;
						std::string varName;
						for (int c = lineCol + 2; c < out.length(); ++c) {
							if (out[c] == char(59)) {
								cont = false;
								stringReg.push_back(std::to_string(0));
								break;
							}
							if (out[c] == char(32)) {
								break;
							}
							varName += out[c];
							lineCol = c;
						}
						string_.ref.push_back(varName);
						if (cont) {
							if (out[lineCol + 2] == char(61) && out[lineCol + 4] == char(34)) {
								lineCol += 5;
								std::string varVal;
								for (int c = lineCol; c < out.length(); ++c) {
									if (out[c + 1] == char(59) && out[c] == char(34)) {
										break;
									}
									varVal += out[c];
								}
								stringReg.push_back(varVal);
							}
						}
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
	int a;
	std::cin >> a;
	src.close();
}