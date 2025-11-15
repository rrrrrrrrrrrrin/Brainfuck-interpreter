#include "brainfuck.hpp"
#include <cstring>

void Brainfuck::init()
{
	ptr = 0;
	std::memset(memory, 0, sizeof(memory));

	opcode_ptr = 0;

	byte = 0;
}

void Brainfuck::loadProgr(int file_size, std::vector<char> buffer)
{
	for (int i = 0; i < file_size; i++) {
		progr.push_back(buffer[i]);
	}
}

void Brainfuck::loadInput(int file_size, std::vector<char> buffer)
{
	for (int i = 0; i < file_size; i++) {
		input.push_back(buffer[i]);
	}
}

void Brainfuck::program()
{
	while (ptr <= sizeof(memory)-1)
	{
		unsigned char &symbol = memory[ptr];

		// Move in the program by incrementing the opcode_ptr
		unsigned char opcode = progr[opcode_ptr];

		switch (opcode)
		{
		case '>':
			++ptr;
			break;

		case '<':
			--ptr;
			break;

		case '+':
			symbol = ++symbol % 256;
			break;

		case '-':
			symbol = --symbol % 256;
			break;

		case '.':
			std::cout << memory[ptr];
			break;

		case ',':
			symbol = input[byte++];
			break;

		// Jump ptr forward to the opcode after the matching ']' command
		case '[':
			brackets.push_back({ '[' , opcode_ptr});

			// Byte in the current memory cell is 0
			if (symbol == 0)
			{
				int brackets_s = sizeof(brackets);

				// The initial '[' popped off
				while (sizeof(brackets) != brackets_s - 1)
				{
					++opcode_ptr;

					switch (opcode)
					{
					case '[':
						brackets.push_back({ '[' , opcode_ptr });
						break;

					case ']':
						unsigned char bracket = brackets.back().first;
						if (bracket == '[')
						{
							// Brackets closed
							brackets.pop_back();
						}
						break;
					}
				}
			}
			break;

		// Jump ptr back to the opcode after the matching '[' command
		case ']':
		{
			unsigned char bracket = brackets.back().first;

			if (brackets.empty())
			{
				error = true;
			}
			// Byte in the current memory cell is not 0
			else if (symbol != 0)
			{
				// opcode_ptr is on symbol '['
				opcode_ptr = brackets.back().second;
			}
			else if (bracket == '[')
			{
				// Brackets closed
				brackets.pop_back();
			}

			break;
		}

		default:
			break;
		}

		if (ptr >= sizeof(memory))
		{
			error = true;
			break;
		}

		if (opcode_ptr == progr.size() - 1)
		{
			break;
		}

		++opcode_ptr;
	}
}
