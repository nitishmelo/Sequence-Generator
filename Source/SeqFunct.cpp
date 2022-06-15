#include "SeqFunct.h"
#include "Helpers.h"
#include <string>
#include <algorithm>

void Randominit(int info[2])
{
	info[0] = 4 + (rand() % TERMS_RANGE);
	info[1] = 1 + (rand() % FIRST_TERM_RANGE);

	int isnegative = (rand() % 5);

	if (isnegative == 3)
	{
		info[1] = info[1] * -1;
	}
}
int RandomAddConstant()
{
	int constant = 1 + (rand() % ADD_RANGE);
	int isnegative = (rand() % 2);

	if (isnegative)
	{
		constant = constant * -1;
	}

	return constant;
}
int RandomMultiplyConstant()
{
	int i = 0;
	int constant = 2 + (rand() % MUL_RANGE);

	if (constant == 10)
	{
		constant = 2 + (rand() % MUL_RANGE);
	}

	if (constant > 3)
	{
		int isnegative = (rand() % 4);
		if (isnegative == 2)
		{
			constant = constant * -1;
		}
	}

	return constant;
}
void RandomIndiceGen(std::vector<int> &missingindices, int numofTerms, int numofMissing, int lowerrange)
{
	int pos;

	for (int i = 0; i < numofMissing; i++)
	{
		pos = lowerrange + (rand() % numofTerms);

		while ((std::find(missingindices.begin(), missingindices.end(), pos) != missingindices.end()))
		{
			pos = lowerrange + (rand() % numofTerms);
		}

		missingindices.push_back(pos);
	}

	std::sort(missingindices.begin(), missingindices.end());
}
void Randomindices(int numofTerms, std::vector<int> &missingindices, bool isgeo)
{
	int numofmissing;
	bool specialcase = false;

	if (numofTerms == 4)
	{
		numofmissing = 1;
	}
	else
	{
		if (isgeo)
		{
			specialcase = true;
		}

		int subvalue = (rand() % NUMMISSINGSUB);

		if (numofTerms % 2 == 0)
		{
			if (subvalue == 0 && specialcase)
			{
				numofmissing = (numofTerms / NUMTERMSDIV) - 1;
				specialcase = false;
			}
			else
			{
				numofmissing = (numofTerms / NUMTERMSDIV) - (subvalue);
			}
		}
		else
		{
			numofmissing = (numofTerms / NUMTERMSDIV);
		}
	}

	RandomIndiceGen(missingindices, numofTerms, numofmissing, 0);

	if (specialcase)
	{
		if (missingindices[0] == 1)
		{
			int missz = missingindices.size();
			int previndex = 1;

			for (int i = 1; i < missz; i++)
			{
				if (missingindices[i] - previndex != 2)
				{
					return;
				}
				previndex = missingindices[i];
			}

			int whattoremove = (rand() % missz);
			missingindices.erase(missingindices.begin() + whattoremove);
		}
	}
}
void Insert(Sequence &seq, int val, bool isMissing)
{
	if (isMissing)
	{
		seq.solutions.push_back(val);
	}
	else
	{
		seq.terms.push_back(val);
	}
}
void InsertTerms(Sequence &seq, std::vector<int> &terms)
{
	int i = 0;
	int numofTerms = terms.size();
	int tracksz = 0;
	int missingindsz = seq.missingindices.size();

	while (i < numofTerms)
	{
		if (i == 0)
		{
			if (seq.missingindices[tracksz] == 0)
			{
				Insert(seq, terms[0], true);
				tracksz++;
			}
			else
			{
				Insert(seq, terms[0], false);
			}
		}
		else
		{
			if (tracksz < missingindsz)
			{
				if (i == seq.missingindices[tracksz])
				{
					tracksz++;
					Insert(seq, terms[i], true);
				}
				else
				{
					Insert(seq, terms[i], false);
				}
			}
			else
			{
				Insert(seq, terms[i], false);
			}
		}
		i++;
	}
}
void GenerateTerms(std::vector<int> &terms, bool isgeo, int constant, int curr, int extra)
{
	int currterm = terms[curr];
	int newterm;

	if (!isgeo)
	{
		if (extra != 0)
		{
			newterm = (currterm + constant) * extra;
		}
		else
		{
			newterm = currterm + constant;
		}
	}
	else
	{
		if (extra != 0)
		{
			newterm = (currterm * constant) + extra;
		}
		else
		{
			newterm = currterm * constant;
		}
	}

	terms.push_back(newterm);
}
int DigitGrouping(Sequence &seq)
{
	int numofTerms = 0;
	int counter = 0;
	int firstterm = 0;

	std::vector<int> terms;

	bool isgeo = (rand() % 2);
	int addandmul = (rand() % 8);
	int constant = 0;
	int secondval = 0;

	if (addandmul < 4)
	{
		firstterm = 1 + (rand() % 9);
		terms.push_back(firstterm);

		numofTerms = 6 + (rand() % 2);

		if (addandmul)
		{
			if (isgeo)
			{
				constant = 2 + (rand() % 9);
				secondval = 1 + (rand() % 10);

				int negval = (rand() % 2);

				if (negval && ((firstterm * constant) > 15))
				{
					secondval = secondval * -1;
				}
			}
			else
			{
				constant = 1 + (rand() % 10);
				secondval = 2 + (rand() % 9);
			}

			while (true)
			{
				GenerateTerms(terms, isgeo, constant, counter, 0);

				counter++;

				if (counter == numofTerms - 1)
				{
					break;
				}

				GenerateTerms(terms, !isgeo, secondval, counter, 0);

				counter++;

				if (counter == numofTerms - 1)
				{
					break;
				}
			}
		}
		else
		{
			secondval = 2 + (rand() % 5);

			if (isgeo)
			{
				constant = 2 + (rand() % 4);
			}
			else
			{
				constant = 1 + (rand() % 10);
			}

			while (counter < numofTerms - 1)
			{
				GenerateTerms(terms, isgeo, constant, counter, secondval);
				counter++;
			}
		}
	}
	else
	{
		int noalt = rand() % 5;

		if (isgeo)
		{
			numofTerms = 6;

			constant = 2 + (rand() % 9);

			if (constant == 10)
			{
				constant = 2 + (rand() % 9);
			}

			if (!noalt)
			{
				firstterm = 1 + (rand() % 10);
				terms.push_back(firstterm);

				if (constant < 5)
				{
					while (counter < numofTerms - 1)
					{
						GenerateTerms(terms, isgeo, constant++, counter, 0);
						counter++;
					}
				}
				else if (constant > 4)
				{
					while (counter < numofTerms - 1)
					{
						GenerateTerms(terms, isgeo, constant--, counter, 0);
						counter++;
					}
				}
			}
			else
			{
				firstterm = 1 + (rand() % 50);
				terms.push_back(firstterm);

				while (counter < numofTerms - 1)
				{
					GenerateTerms(terms, isgeo, constant, counter, 0);
					counter++;
				}
			}

		}
		else
		{
			firstterm = 1 + (rand() % 9);
			terms.push_back(firstterm);

			numofTerms = 6 + (rand() % 2);

			if (!noalt)
			{
				int nosub = rand() % 2;

				if (nosub)
				{
					constant = 1 + (rand() % 45);

					while (counter < numofTerms - 1)
					{
						GenerateTerms(terms, isgeo, constant++, counter, 0);
						counter++;
					}
				}
				else
				{
					constant = 3 + (rand() % 45);

					while (counter < numofTerms - 1)
					{
						GenerateTerms(terms, isgeo, constant--, counter, 0);
						counter++;
					}
				}
			}
			else
			{
				constant = 1 + (rand() % 45);

				while (counter < numofTerms - 1)
				{
					GenerateTerms(terms, isgeo, constant, counter, 0);
					counter++;
				}
			}
		}
	}

	std::vector<int> newlist;

	OneDigitList(terms, newlist);

	return DetermineNumofDigits(newlist, seq);
}
void OneDigitList(std::vector<int> &terms, std::vector<int> &newlist)
{
	int counter = 0;

	int numofTerms = terms.size();

	for (int i = 0; i < numofTerms; i++)
	{
		int term = terms[i];

		if (term > 9)
		{
			int numlen = intlen(term);
			std::string numstr = std::to_string(term);

			for (int j = 0; j < numlen; j++)
			{
				newlist.push_back(numstr[j] - 48);
			}

			counter++;

			if (counter == numofTerms)
			{
				break;
			}
		}
		else
		{
			newlist.push_back(term);
			counter++;

			if (counter == numofTerms)
			{
				break;
			}
		}
	}
}
void CombineDigits(std::vector<int> &terms, std::vector<int> &combineddigits, int numofTerms, int numofDigits)
{
	int counter = 0;
	int returnval = 0;
	int mul = pow(10, (numofDigits - 1));
	int initmul = 0;
	int total = 0;
	int index = 0;

	while (counter < numofTerms)
	{
		initmul = mul;

		while (initmul != 0)
		{
			total += (terms[index] * initmul);
			index++;
			initmul /= 10;
		}

		combineddigits.push_back(total);
		total = 0;
		counter++;
	}

}
int DetermineNumofDigits(std::vector<int> &newlist, Sequence &seq)
{
	int numofMissing;

	int numofTerms = newlist.size();

	int numofDigits = isPrime(numofTerms);

	if (numofDigits > 0)
	{
		std::vector<int> combineddigits;
		numofTerms = (numofTerms / numofDigits);
		CombineDigits(newlist, combineddigits, numofTerms, numofDigits);

		if (numofTerms < 7)
		{
			numofMissing = 1;
		}
		else
		{
			numofMissing = (numofTerms / 4);
		}

		RandomIndiceGen(seq.missingindices, numofTerms - 2, numofMissing, 1);
		InsertTerms(seq, combineddigits);
		return numofDigits;

	}
	else
	{
		numofMissing = (numofTerms / 4);

		if (numofMissing == 0)
		{
			numofMissing++;
		}

		RandomIndiceGen(seq.missingindices, numofTerms - 2, numofMissing, 1);
		InsertTerms(seq, newlist);
		return -1;
	}
}
void FibonacciHelper(std::vector<int> &terms)
{
	int firstterm = 1 + (rand() % 20);
	int ismul = (rand() % 2);
	int secondterm = 0;
	int numofTerms = 0;

	if (ismul)
	{
		secondterm = 1 + (rand() % 10);

		numofTerms = 6;
	}
	else
	{
		secondterm = 1 + (rand() % 50);

		numofTerms = 6 + (rand() % 3);
	}

	terms.push_back(firstterm);
	terms.push_back(secondterm);

	if (!ismul)
	{
		for (int i = 2; i < numofTerms; i++)
		{
			terms.push_back(terms[i - 1] + terms[i - 2]);
		}
	}
	else
	{
		for (int i = 2; i < numofTerms; i++)
		{
			terms.push_back(terms[i - 1] * terms[i - 2]);
		}
	}
}
int Fibonacci(Sequence &seq)
{
	std::vector<int> terms;

	FibonacciHelper(terms);

	int notdigitlist = rand() % 4;

	if (!notdigitlist)
	{
		std::vector<int> newlist;

		OneDigitList(terms, newlist);

		return DetermineNumofDigits(newlist, seq);
	}
	else
	{
		int termsz = terms.size();

		int numofMissing = (termsz / 3);
		RandomIndiceGen(seq.missingindices, termsz, numofMissing, 0);
		InsertTerms(seq, terms);

		return -1;
	}
}
void BasicSeqGen(Sequence &seq)
{
	int info[2];
	Randominit(info);
	int numofTerms = info[0];
	int firstterm = info[1];
	bool isgeo = (rand() % 2);
	int successivealterval = (rand() % 8);
	bool successivealterflag1 = (successivealterval > 3 && successivealterval < 6);
	bool successivealterflag2 = (successivealterval > 5);
	int addalter = 0;
	int tensalter = 0;
	bool ismulalteralt = false;
	int mulalter = 0;
	int constant = 0;
	std::vector<int> terms;
	terms.push_back(firstterm);

	Randomindices(numofTerms, seq.missingindices, isgeo);

	if (!isgeo)
	{
		constant = RandomAddConstant();

		if (successivealterval > 3)
		{
			addalter = 1 + (rand() % 10);
			tensalter = (rand() % 4);

			if (!tensalter)
			{
				addalter = addalter * 10;
			}

			int misssz = seq.missingindices.size();

			if (misssz > 2)
			{
				int whattoremove = (rand() % misssz);
				seq.missingindices.erase(seq.missingindices.begin() + whattoremove);
			}
		}
	}
	else
	{
		constant = RandomMultiplyConstant();
		int mulcheck = (rand() % 3);

		if (successivealterval > 3)
		{
			int misssz = seq.missingindices.size();

			if (misssz > 2)
			{
				int whattoremove = (rand() % misssz);
				seq.missingindices.erase(seq.missingindices.begin() + whattoremove);
			}
		}

		int checkcons = constant;
		if (checkcons < 0)
		{
			checkcons = checkcons * -1;
		}

		ismulalteralt = (mulcheck) && (checkcons < 5) && (numofTerms > 5);

		if (constant % 2 != 0 && ismulalteralt)
		{
			while (true)
			{
				mulalter = 2 + (rand() % 5);

				if (mulalter % 2 != 0)
				{
					continue;
				}

				break;
			}
		}
	}

	int counter = 0;
	int savedcons = constant;
	bool doaddalter = (numofTerms == 7 || (seq.missingindices.size() == 2));

	if (numofTerms > 5)
	{
		if (!isgeo)
		{
			if (doaddalter)
			{
				if (successivealterflag1)
				{
					while (counter < numofTerms - 1)
					{
						GenerateTerms(terms, isgeo, constant, counter, false);
						constant += addalter;
						counter++;
					}
				}
				else if (successivealterflag2)
				{
					while (counter < numofTerms - 1)
					{
						GenerateTerms(terms, isgeo, constant, counter, false);
						constant -= addalter;
						counter++;
					}
				}
				else
				{
					while (counter < numofTerms - 1)
					{
						GenerateTerms(terms, isgeo, constant, counter, false);
						counter++;
					}
				}
			}
			else
			{
				while (counter < numofTerms - 1)
				{
					GenerateTerms(terms, isgeo, constant, counter, false);
					counter++;
				}
			}
		}
		else
		{
			if (savedcons > 4 || ismulalteralt)
			{
				if (successivealterflag1)
				{
					if (!ismulalteralt)
					{
						while (counter < numofTerms - 1)
						{
							GenerateTerms(terms, isgeo, constant, counter, false);
							constant++;
							counter++;
						}
					}
					else
					{
						while (counter < numofTerms - 1)
						{
							GenerateTerms(terms, isgeo, constant, counter, false);
							constant += mulalter;
							counter++;
						}
					}
				}
				else if (successivealterflag2)
				{
					if (!ismulalteralt)
					{
						while (counter < numofTerms - 1)
						{
							GenerateTerms(terms, isgeo, constant, counter, false);
							constant--;
							counter++;
						}
					}
					else
					{
						while (counter < numofTerms - 1)
						{
							GenerateTerms(terms, isgeo, constant, counter, false);
							constant -= addalter;
							counter++;
						}
					}
				}
				else
				{
					while (counter < numofTerms - 1)
					{
						GenerateTerms(terms, isgeo, constant, counter, false);
						counter++;
					}
				}
			}
			else
			{
				while (counter < numofTerms - 1)
				{
					GenerateTerms(terms, isgeo, constant, counter, false);
					counter++;
				}
			}
		}
	}
	else
	{
		while (counter < numofTerms - 1)
		{
			GenerateTerms(terms, isgeo, constant, counter, false);
			counter++;
		}

	}

	InsertTerms(seq, terms);
}
