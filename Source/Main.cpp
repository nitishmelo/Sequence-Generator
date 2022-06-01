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
		std::cin.get();
		std::cout << std::endl;
		std::cout << "Press enter to end the program." << std::endl;
		std::cin.get();
		return 0;
	}

	srand(time(NULL));

	std::ofstream terms;
	std::ofstream sols;
	std::string seqfile;
	std::string solfile;

	std::cout << "Enter a filename to write sequences to: ";
	std::cin >> seqfile;
	std::cout << std::endl;

	std::cout << "Enter a filename to write solutions to: ";
	std::cin >> solfile;
	std::cout << std::endl;

	terms.open(seqfile);

	if (!terms)
	{
		std::cout << "Failed to create & open the sequences file.";
		std::cin.get();
		std::cout << std::endl;
		std::cout << "Press enter to end the program." << std::endl;
		std::cin.get();
		return 0;
	}

	sols.open(solfile);

	if (!sols)
	{
		std::cout << "Failed to create & open the solutions file.";
		std::cin.get();
		std::cout << std::endl;
		std::cout << "Press enter to end the program." << std::endl;
		std::cin.get();
		return 0;
	}

	std::cout << "Generating & writing sequences and solutions..." << std::endl;
	std::cout << std::endl;

	PrintToFile(seqs, terms, sols);

	std::cout << "Sequences & solutions generated and written successfully." << std::endl;

	std::cin.get();
	terms.close();
	sols.close();
	std::cout << std::endl;

	std::cout << "Press enter to end the program." << std::endl;
	std::cin.get();
}
