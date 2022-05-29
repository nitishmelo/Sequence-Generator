#include "Sequence.h"
void Randominit(int info[2]);
int RandomAddConstant();
int RandomMultiplyConstant();
void Randomindices(int numofTerms, std::vector<int> &missingindices, int isgeo);
void Insert(Sequence &seq, int val, bool isMissing);
void InsertTerms(Sequence &seq, std::vector<int> &terms);
void UnalteredCreateTerms(std::vector<int> &terms, Sequence &seq, int numofTerms, int constant, bool mulflag);
void BasicSeqGen(Sequence &seq);
void DigitGrouping(Sequence &seq);
