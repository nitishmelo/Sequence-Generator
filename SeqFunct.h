#include "Sequence.h"
void Randominit(int info[2]);
int RandomAddConstant();
int RandomMultiplyConstant();
void Randomindices(int numofTerms, std::vector<int> &missingindices);
void Insert(Sequence &seq, int val, bool isMissing);
void InsertTerms(Sequence& seq, std::vector<int> terms);
void BasicSeqGen(Sequence& seq);
void DigitGrouping(Sequence &seq);