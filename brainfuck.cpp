#include "brainfuck.hpp"
#include <cstring>

void Brainfuck::init()
{
	ptr = 0;
	std::memset(memory, 0, sizeof(memory));
	
	byte = 0;
	input = { 0 };

	brackets = { 0 };
}

void Brainfuck::loadFile(int file_size, std::vector<char> buffer)
{
	for (int i = 0; i < file_size; i++) {
		memory[i] = buffer[i];
	}
}

void Brainfuck::loadInput(int file_size, std::vector<char> buffer)
{
	for (int i = 0; i < file_size; i++) {
		input[i] = buffer[i];
	}
}

void Brainfuck::program()
{
	init();

	while (ptr <= sizeof(memory))
	{
		unsigned char &symbol = memory[ptr];

		switch (symbol)
		{
		case '>':
			++ptr;
			break;

		case '<':
			--ptr;
			break;

		case '+':
			++symbol;
			break;

		case '-':
			--symbol;
			break;

		case '.':
			std::cout << symbol;
			break;

		case ',':
			symbol = input[byte++];
			break;

		case '[':
			brackets.push_back('[');

			if (symbol == 0)
			{

			}
			break;

		case ']':
			unsigned char bracket = brackets[sizeof(brackets)];

			if (brackets.empty())
			{
				error = true;
			} 
			else if (bracket == '[')
			{
				// Brackets closed
				brackets.pop_back();
			}

			if (symbol != 0)
			{

			}
			break;
		}

		if (ptr > sizeof(memory))
		{
			error = true;
			break;
		}
	}
}
