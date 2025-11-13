#pragma once
#include <iostream>
#include <vector>

class Brainfuck
{
private:
	int ptr = 0;  // memory ptr
	unsigned char memory[30000] = { 0 };

	int opcode_ptr = 0;  // progr ptr
	std::vector<unsigned char> progr;

	int byte = 0;
	std::vector<char> input;

	std::vector<std::pair<unsigned char, int>> brackets;
	
	bool error = false;

public:
	bool get_error() { return error; }

	void init();
	void loadProgr(int file_size, std::vector<char> buffer);
	void loadInput(int file_size, std::vector<char> buffer);

	void program();
};