#include "SeqFunct.h"
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
void RandomIndiceGen(std::vector<int> &missingindices, int numofTerms, int numofMissing)
{
	int pos;

	for (int i = 0; i < numofMissing; i++)
	{
		pos = rand() % numofTerms;

		while ((std::find(missingindices.begin(), missingindices.end(), pos) != missingindices.end()))
		{
			pos = rand() % numofTerms;
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

	RandomIndiceGen(missingindices, numofTerms, numofmissing);

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
void GenerateTerms(std::vector<int> &terms, bool isgeo, int constant, int curr)
{
	int currterm = terms[curr];
	int newterm;

	if (!isgeo)
	{
		newterm = currterm + constant;
	}
	else
	{
		newterm = currterm * constant;
	}

	terms.push_back(newterm);
}
void DigitGrouping(Sequence &seq)
{
	int firstterm = 1 + (rand() % 20);
	bool isgeo = (rand() % 2);
	int constant = 0;
	int numofTerms;
	std::vector<int> terms;

	if (isgeo)
	{
		numofTerms = 8 + (rand() % 10);
		constant = RandomMultiplyConstant();
	}
	else
	{
		numofTerms = 8 + (rand() % 3);
		constant = RandomAddConstant();
	}
	if (constant < 0)
	{
		constant = constant * -1;
	}
	terms.push_back(firstterm);
	int counter = 0;
	std::vector<int> newlist;

	while (counter < numofTerms - 1)
	{
		GenerateTerms(terms, isgeo, constant, counter);
		counter++;
	}
	int numofdigits = 0;
	bool exit = false;
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
				numofdigits++;
				if (numofdigits == numofTerms)
				{
					exit = true;
					break;
				}
			}
		}
		else
		{
			newlist.push_back(term);
			numofdigits++;
			if (numofdigits == numofTerms)
			{
				exit = true;
			}
		}
		if (exit)
		{
			break;
		}
	}
	int numofMissing = (numofTerms / 4);
	RandomIndiceGen(seq.missingindices, numofTerms, numofMissing);
	InsertTerms(seq, newlist);
}
int intlen(int num)
{
	int length = 0;

	while (num != 0)
	{
		length++;
		num = num / 10;
	}

	return length;
}
void BasicSeqGen(Sequence& seq)
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
						GenerateTerms(terms, isgeo, constant, counter);
						constant += addalter;
						counter++;
					}
				}
				else if (successivealterflag2)
				{
					while (counter < numofTerms - 1)
					{
						GenerateTerms(terms, isgeo, constant, counter);
						constant -= addalter;
						counter++;
					}
				}
				else
				{
					while (counter < numofTerms - 1)
					{
						GenerateTerms(terms, isgeo, constant, counter);
						counter++;
					}
				}
			}
			else
			{
				while (counter < numofTerms - 1)
				{
					GenerateTerms(terms, isgeo, constant, counter);
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
							GenerateTerms(terms, isgeo, constant, counter);
							constant++;
							counter++;
						}
					}
					else
					{
						while (counter < numofTerms - 1)
						{
							GenerateTerms(terms, isgeo, constant, counter);
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
							GenerateTerms(terms, isgeo, constant, counter);
							constant--;
							counter++;
						}
					}
					else
					{
						while (counter < numofTerms - 1)
						{
							GenerateTerms(terms, isgeo, constant, counter);
							constant -= addalter;
							counter++;
						}
					}
				}
				else
				{
					while (counter < numofTerms - 1)
					{
						GenerateTerms(terms, isgeo, constant, counter);
						counter++;
					}
				}
			}
			else
			{
				while (counter < numofTerms - 1)
				{
					GenerateTerms(terms, isgeo, constant, counter);
					counter++;
				}
			}
		}
	}
	else
	{
		while (counter < numofTerms - 1)
		{
			GenerateTerms(terms, isgeo, constant, counter);
			counter++;
		}

	}

	InsertTerms(seq, terms);
}
