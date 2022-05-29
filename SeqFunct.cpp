#include "Sequence.h"
#include <string>
#include <algorithm>

void Randominit(int info[2])
{
	info[0] = 4 + (rand() % TERMS_RANGE);
	info[1] = 1 + (rand() % FIRST_TERM_RANGE);
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
void Randomindices(int numofTerms, std::vector<int> &missingindices)
{
	int numofmissing;
	if (numofTerms == 4)
	{
		numofmissing = 1;
	}
	else
	{ 
		int subvalue = (rand() % NUMMISSINGSUB);
		if (numofTerms % 2 == 0)
		{
			numofmissing = (numofTerms / NUMTERMSDIV) - (subvalue);
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
}
void Insert(Sequence& seq, int val, bool isMissing)
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
void InsertTerms(Sequence& seq, std::vector<int> terms)
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

}
void BasicSeqGen(Sequence &seq)
{
	int info[2];
	Randominit(info);
	int numofTerms = info[0];
	int firstterm = info[1];
	int isgeo = (rand() % 2);
	int successivealterflag = (rand() % 8);
	int addalter = (rand() % 6);
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
	int savedcons = constant;
	Randomindices(numofTerms, seq.missingindices);
	int i = 0;
	int currterm = firstterm;
	int newterm;
	if (!isgeo)
	{
		if (numofTerms > 5)
		{ 
			if (successivealterflag > 3 && successivealterflag < 6)
			{
				while (i < numofTerms - 1)
				{
					newterm = currterm + constant;
					terms.push_back(newterm);
					i++;
					currterm = newterm;
					constant += addalter;
				}
				goto done;
			}
			else if (successivealterflag > 5)
			{
				while (i < numofTerms - 1)
				{
					newterm = currterm + constant;
					terms.push_back(newterm);
					i++;
					currterm = newterm;
					constant -= addalter;
				}
				goto done;
			}
			else
			{
				goto unalteredadd;
			}
		}
		else
		{
			goto unalteredadd;
		}
	}
	else
	{
		if (numofTerms > 5 && savedcons > 4)
		{ 
			if (successivealterflag > 3 && successivealterflag < 6)
			{
				while (i < numofTerms - 1)
				{
					newterm = currterm * constant;
					terms.push_back(newterm);
					i++;
					currterm = newterm;
					constant++;
				}
				goto done;
			}
			else if (successivealterflag > 5)
			{
				while (i < numofTerms - 1)
				{
					newterm = currterm * constant;
					terms.push_back(newterm);
					i++;
					currterm = newterm;
					constant--;
				}
				goto done;
			}
			else
			{
				goto unalteredmul;
			}
		}
		else
		{
			goto unalteredmul;
		}
	}
unalteredadd:
	while (i < numofTerms - 1)
	{
		newterm = currterm + constant;
		terms.push_back(newterm);
		i++;
		currterm = newterm;
	}
	goto done;

unalteredmul:
	while (i < numofTerms - 1)
	{
		newterm = currterm * constant;
		terms.push_back(newterm);
		i++;
		currterm = newterm;
	}
done:
	InsertTerms(seq, terms);
}