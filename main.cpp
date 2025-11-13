#include "brainfuck.hpp"
#include <fstream>

int main(int argc, char* argv[]) {
	if (argc != 3)
	{
		std::cout << "Usage : program_name progr.txt input.txt";
		return 1;
	}

	std::ifstream progr(argv[1]);
	if (!progr)
	{
		std::cout << "Couldn't open progr file";
		return 2;
	}

	std::ifstream input(argv[2], std::ios::binary);
	if (!input)
	{
		std::cout << "Couldn't open input file";
		return 3;
	}

	Brainfuck brainfuck;

	brainfuck.init();

	// Load progr into memory
	progr.seekg(0, std::ios::end);
	int file_size = static_cast<int>(progr.tellg());
	progr.seekg(0, std::ios::beg);

	std::vector<char> buffer(file_size);
	progr.read(buffer.data(), file_size);

	progr.close();

	brainfuck.loadProgr(file_size, buffer);

	// Load input into buffer
	input.seekg(0, std::ios::end);
	file_size = static_cast<int>(input.tellg());
	input.seekg(0, std::ios::beg);

	std::vector<char> buffer2(file_size);
	input.read(buffer2.data(), file_size);

	input.close();

	brainfuck.loadInput(file_size, buffer2);

	brainfuck.program();

	// If in the process ptr is out of bounds
	// or the brakets are unmatched
	if (brainfuck.get_error())
	{
		std::cout << "ERROR";
	}

	return 0;
}