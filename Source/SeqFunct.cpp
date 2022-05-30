#include "SeqFunct.h"
#include <string>
#include <algorithm>

void Randominit(int info[2])
{
	info[0] = 4 + (rand() % TERMS_RANGE);
	info[1] = 1 + (rand() % FIRST_TERM_RANGE);
	int isnegative = (rand() % 4);
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
	while (constant == 10 && i < 3)
	{
		constant = 2 + (rand() % MUL_RANGE);
		i++;
	}
	if (constant > 3)
	{
		int isnegative = (rand() % 3);
		if (isnegative == 2)
		{
			constant = constant * -1;
		}
	}
	return constant;
}
void Randomindices(int numofTerms, std::vector<int> &missingindices, int isgeo)
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
	int pos;
	for (int i = 0; i < numofmissing; i++)
	{
		pos = rand() % numofTerms;
		while ((std::find(missingindices.begin(), missingindices.end(), pos) != missingindices.end()))
		{
			pos = rand() % numofTerms;
		}
		missingindices.push_back(pos);
	}
	std::sort(missingindices.begin(), missingindices.end());
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
void DigitGrouping(Sequence &seq)
{
	// TODO
}
void BasicSeqGen(Sequence &seq)
{
	int info[2];
	Randominit(info);
	int numofTerms = info[0];
	int firstterm = info[1];
	int isgeo = (rand() % 2);
	int successivealterflag = (rand() % 8);
	int addalter = 1 + (rand() % 5);
	int constant;
	std::vector<int> terms;
	terms.push_back(firstterm);
	if (!isgeo)
	{
		constant = RandomAddConstant();
	}
	else
	{
		constant = RandomMultiplyConstant();
	}
	Randomindices(numofTerms, seq.missingindices, isgeo);
	int counter = 0;
	int currterm = firstterm;
	int newterm;
	bool isalter = false;
	bool loopbackearly = false;
	if (successivealterflag < 4) 
	{
		loopbackearly = true;
	}
	int savedcons = constant;
	while (counter < numofTerms - 1)
	{
		if (!isgeo)
		{
			newterm = currterm + constant;
		}
		else
		{
			newterm = currterm * constant;
		}
		terms.push_back(newterm);
		currterm = newterm;
		counter++;
		if (loopbackearly)
		{
			continue;
		}
		else
		{ 
			if (numofTerms > 5)
			{
				if (!isgeo)
				{
					if (successivealterflag > 3 && successivealterflag < 6)
					{
						constant += addalter;
					}
					else if (successivealterflag > 5)
					{
						constant -= addalter;
					}
					else
					{
						loopbackearly = true;
						continue;
					}
				}
				else
				{
					if (savedcons > 4)
					{
						if (successivealterflag > 3 && successivealterflag < 6)
						{
							constant++;
						}
						else if (successivealterflag > 5)
						{
							constant--;
						}
						else
						{
							loopbackearly = true;
							continue;
						}
					}
					else
					{
						loopbackearly = true;
						continue;
					}
				}
			}
			else
			{
				loopbackearly = true;
				continue;
			}
		}
	}
	InsertTerms(seq, terms);
}
