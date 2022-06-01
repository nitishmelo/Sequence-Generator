#include "Sequence.h"
void Randominit(int info[2]);
int RandomAddConstant();
int RandomMultiplyConstant();
void Randomindices(int numofTerms, std::vector<int> &missingindices, bool isgeo);
void RandomIndiceGen(std::vector<int>& missingindices, int numofTerms, int numofMissing);
void Insert(Sequence &seq, int val, bool isMissing);
void InsertTerms(Sequence &seq, std::vector<int> &terms);
void GenerateTerms(std::vector<int> &terms, bool isgeo, int constant, int curr);
void BasicSeqGen(Sequence &seq);

void DigitGrouping(Sequence &seq);
int intlen(int num);
