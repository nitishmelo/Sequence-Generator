#include "Sequence.h"
void Randominit(int info[2]);
int RandomAddConstant();
int RandomMultiplyConstant();
void Randomindices(int numofTerms, std::vector<int> &missingindices, bool isgeo);
void RandomIndiceGen(std::vector<int> &missingindices, int numofTerms, int numofMissing, int lowerrange);
void Insert(Sequence &seq, int val, bool isMissing);
void InsertTerms(Sequence &seq, std::vector<int> &terms);
void GenerateTerms(std::vector<int> &terms, bool isgeo, int constant, int curr, int extra);
void BasicSeqGen(Sequence &seq);

int DigitGrouping(Sequence &seq);
void OneDigitList(std::vector<int> &terms, std::vector<int> &newlist);
void CombineDigits(std::vector<int> &terms, std::vector<int> &combineddigits, int numofTerms, int numofDigits);
int DetermineNumofDigits(std::vector<int> &newlist, Sequence &seq);

void FibonacciHelper(std::vector<int> &terms);
int Fibonacci(Sequence &seq);
