#include "SeqFunct.h"
#include "Printer.h"
#include "Helpers.h"
#include <iostream>
#include <fstream>

void PrintToFile(int seqs, std::ostream &terms, std::ostream &sols)
{
	int x = 0;
	Sequence seq;
	bool isGrouping;
	int len;
	int funct;

	while (x < seqs)
	{
		funct = (rand() % 4);
		len = -1;
		isGrouping = false;

		if (funct < 2)
		{
			BasicSeqGen(seq);
		}
		else if (funct == 2)
		{
			len = DigitGrouping(seq);
			isGrouping = true;
		}
		else
		{
			Fibonacci(seq);
		}

		size_t termsz = seq.terms.size();
		size_t solsz = seq.solutions.size();
		size_t totalsz = termsz + solsz;
		int missind = 0;
		terms << (x + 1) << ". ";
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
						terms << "?";

						if (totalcounter < totalsz)
						{
							terms << ", ";
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
				PrintVal(seq.terms[counter], len, isGrouping, terms);
				totalcounter++;
				counter++;
			}

			if (totalcounter >= totalsz)
			{
				break;
			}

			terms << ", ";
		}

		terms << std::endl;
		sols << (x + 1) << ". ";

		for (int i = 0; i < solsz; i++)
		{
			if (i != (solsz - 1))
			{
				PrintVal(seq.solutions[i], len, isGrouping, sols);
				sols << ", ";
			}
			else
			{
				PrintVal(seq.solutions[i], len, isGrouping, sols);
			}
		}

		sols << std::endl;
		seq.terms.clear();
		seq.solutions.clear();
		seq.missingindices.clear();
		x++;
	}
}

void PrintVal(int val, int len, bool isGrouping, std::ostream &stream)
{
	if (isGrouping && (len != -1))
	{
		int vallen = intlen(val);

		if (vallen != len)
		{
			int numofzeroes = (len - vallen);

			for (int i = 0; i < numofzeroes; i++)
			{
				stream << "0";
			}

			stream << val;
		}
		else
		{
			stream << val;
		}
		
		return;
	}

	stream << val;
}
