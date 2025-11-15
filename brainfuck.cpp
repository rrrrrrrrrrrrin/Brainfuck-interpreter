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
	// Calculate jump positions for '[' and ']' loop opcodes
	for (int i = 0; i < progr.size(); i++)
	{
		if (progr[i] == '[')
		{
			brackets_stack.push(i);
		}
		else if (progr[i] == ']')
		{
			if (brackets_stack.empty())
			{
				error = true;
				return;
			}

			// Save positions of the opening and closing brackets
			int open_bracket_pos = brackets_stack.top();
			int close_bracket_pos = i;

			brackets_pos.insert( { open_bracket_pos, close_bracket_pos } );
			brackets_pos.insert({ close_bracket_pos, open_bracket_pos });

			brackets_stack.pop();  // brackets closed

		}
	}

	while (opcode_ptr < progr.size())
	{
		if (ptr >= sizeof(memory))
		{
			error = true;
			break;
		}

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
			if (byte < input.size())
			{
				symbol = input[byte++];
			}
			break;

		// Jump ptr forward to the opcode after the matching ']' command
		case '[':
			if (symbol == 0)
			{
				opcode_ptr = brackets_pos[opcode_ptr];
			}
			break;

		// Jump ptr back to the opcode after the matching '[' command
		case ']':
		{
			if (symbol != 0)
			{
				opcode_ptr = brackets_pos[opcode_ptr];
			}
			break;
		}

		default:
			break;
		}

		++opcode_ptr;
	}
}
