#include <vector>

#define TERMS_RANGE 4
#define FIRST_TERM_RANGE 99
#define ADD_RANGE 50
#define MUL_RANGE 9
#define NUMTERMSDIV 2
#define NUMMISSINGSUB 2

struct Sequence
{
	std::vector<int> terms;
	std::vector<int> solutions;
	std::vector<int> missingindices;
};

struct Info
{
	int numofTerms;
	int firstterm;
	int constant;
};
