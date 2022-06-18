#include <vector>
#include <string>

#define TERMS_RANGE 4
#define FIRST_TERM_RANGE 100
#define ADD_RANGE 50
#define MUL_RANGE 9
#define NUMTERMSDIV 2
#define NUMMISSINGSUB 2

struct Sequence
{
	std::vector<std::string> terms;
	std::vector<std::string> solutions;
	std::vector<int> missingindices;
};
