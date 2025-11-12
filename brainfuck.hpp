#pragma once
#include <iostream>
#include <vector>

class Brainfuck
{
private:
	int ptr = 0;
	unsigned char memory[30000] = { 0 };

	int byte = 0;
	std::vector<char> input = { 0 };

	std::vector<unsigned char> brackets = { 0 };
	
	bool error = false;

public:
	bool get_error() { return error; }

	void init();
	void loadFile(int file_size, std::vector<char> buffer);
	void loadInput(int file_size, std::vector<char> buffer);

	void program();
};