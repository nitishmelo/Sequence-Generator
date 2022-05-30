#include <iostream>
#include <fstream>
#include <string>
#include "SeqFunct.h"
#include "Printer.h"

#define SEQUENCE_LIMIT 1000000

int main()
{
	int seqs;
	while (std::cout << "Enter the number of sequences to generate: (LIMIT: 1000000) " && (!(std::cin >> seqs) || (seqs > SEQUENCE_LIMIT || seqs < 0)))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (seqs > SEQUENCE_LIMIT)
		{
			std::cout << std::endl << "Exceeded sequence limit; try again: " << std::endl;
		}
		else
		{
			std::cout << std::endl << "Invalid input; try again: " << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	if (seqs == 0)
	{
		std::cout << "No sequences generated." << std::endl;
		std::getchar();
		std::cout << std::endl;
		std::cout << "Press enter to end the program." << std::endl;
		std::getchar();
		return 0;
	}
	srand(time(NULL));
	std::ofstream term;
	std::ofstream sol;
	std::string seqfile;
	std::string solfile;
	std::cout << "Enter a filename to write the sequences to: ";
	std::cin >> seqfile;
	std::cout << std::endl;
	std::cout << "Enter a filename to write solutions to: ";
	std::cin >> solfile;
	std::cout << std::endl;
	term.open(seqfile);
	sol.open(solfile);
	std::cout << "Generating & writing sequences and solutions..." << std::endl;
	std::cout << std::endl;
	PrintToFile(seqs, term, sol);
	std::cout << "Sequences & solutions generated and written successfully." << std::endl;
	std::getchar();
	term.close();
	sol.close();
	std::cout << std::endl;
	std::cout << "Press enter to end the program." << std::endl;
	std::getchar();
}
