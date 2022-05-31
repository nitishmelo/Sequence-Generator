#include "SeqFunct.h"
#include <iostream>
#include <fstream>
void PrintToFile(int seqs, std::ostream &term, std::ostream &sol)
{
	int x = 0;
	Sequence seq;

	while (x < seqs)
	{
		BasicSeqGen(seq);
		size_t termsz = seq.terms.size();
		size_t solsz = seq.solutions.size();
		size_t totalsz = termsz + solsz;
		int missind = 0;
		term << (x + 1) << ". "; 
		int counter = 0;
		int totalcounter = 0;
		bool exit = false;

		while (true)
		{
			while (true)
			{ 
				if (missind < solsz)
				{
					while (totalcounter == seq.missingindices[missind])
					{
						missind++;
						totalcounter++;
						term << "?";

						if (totalcounter < totalsz)
						{
							term << ", ";
						}
						else
						{
							exit = true;
						}

						if (missind == solsz)
						{
							break;
						}
					}
				}

				break;
			}

			if (exit)
			{
				break;
			}

			if (counter < termsz)
			{
				term << seq.terms[counter];
				totalcounter++;
				counter++;
			}

			if (totalcounter >= totalsz)
			{
				break;
			}

			term << ", ";
		}

		term << std::endl;
		sol << (x + 1) << ". ";

		for (int i = 0; i < solsz; i++)
		{
			if (i != (solsz - 1))
			{
				sol << seq.solutions[i] << ", ";
			}
			else
			{
				sol << seq.solutions[i];
			}
		}

		sol << std::endl;
		seq.terms.clear();
		seq.solutions.clear();
		seq.missingindices.clear();
		x++;
	}
}
