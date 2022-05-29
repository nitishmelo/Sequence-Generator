#include <iostream>
#include <fstream>
#include "SeqFunct.h"
#include "Printer.h"

int main()
{
	int seqs;
	while (std::cout << "Enter the number of sequences to generate: " && !(std::cin >> seqs))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << std::endl << "Invalid input; try again: " << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	if (seqs == 0)
	{
		std::cout << "No sequences generated; any existing files with the same filenames will remain unaffected." << std::endl;
		std::getchar();
		std::cout << std::endl;
		std::cout << "Press enter to end the program." << std::endl;
		std::getchar();
		return 0;
	}
	srand(time(NULL));
	std::ofstream term;
	std::ofstream sol;
	term.open("seq.txt");
	sol.open("solutions.txt");
	std::cout << "Generating & writing sequences and solutions..." << std::endl;
	std::cout << std::endl;
	PrintToFile(seqs, term, sol);
	std::cout << "Sequences & solutions generated and written successfully." << std::endl;
	std::getchar();
	std::cout << std::endl;
	std::cout << "Press enter to end the program." << std::endl;
	std::getchar();
}
