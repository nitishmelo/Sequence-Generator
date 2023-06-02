#include "../include/SeqFunct.h"
#include "../include/Helpers.h"
#include <math.h>
#include <string>
#include <algorithm>

void Randominit(int info[2]) {
    info[0] = 5 + (rand() % TERMS_RANGE);
    info[1] = 1 + (rand() % FIRST_TERM_RANGE);
    int isnegative = (rand() % 5);
    if (isnegative == 3)
        info[1] = info[1] * -1;
}
int RandomAddConstant() {
    int constant = 1 + (rand() % ADD_RANGE);
    int isnegative = (rand() % 2);
    if (isnegative)
        constant = constant * -1;
    return constant;
}
int RandomMultiplyConstant() {
    int i = 0;
    int constant = 2 + (rand() % MUL_RANGE);
    if (constant == 10)
        constant = 2 + (rand() % MUL_RANGE);
    if (constant > 3) {
        int isnegative = (rand() % 4);
        if (isnegative == 2)
            constant = constant * -1;
    }
    return constant;
}
void RandomIndiceGen(std::vector<int>& missingindices, int numofTerms, int numofMissing, int lowerrange) {
    int pos;
    for (int i = 0; i < numofMissing; i++) {
        pos = lowerrange + (rand() % numofTerms);
        while ((std::find(missingindices.begin(), missingindices.end(), pos) != missingindices.end()))
            pos = lowerrange + (rand() % numofTerms);
        missingindices.push_back(pos);
    }
    std::sort(missingindices.begin(), missingindices.end());
}
void Randomindices(int numofTerms, std::vector<int>& missingindices, bool isgeo) {
    int numofmissing = 0;
    bool specialcase = false;
    if (isgeo)
        specialcase = true;
    if (numofTerms < 7) {
        numofmissing = 1;
        specialcase = false;
    }
    else
        numofmissing = 2 + (rand() % 2);
    
    RandomIndiceGen(missingindices, numofTerms - 2, numofmissing, 1);

    if (specialcase) {
        if (missingindices[0] == 1) {
            int missz = missingindices.size();
            int previndex = 1;
            for (int i = 1; i < missz; i++) {
                if (missingindices[i] - previndex != 2)
                    return;
                previndex = missingindices[i];
            }
            int whattoremove = (rand() % missz);
            missingindices.erase(missingindices.begin() + whattoremove);
        }
    }
}
void Insert(Sequence& seq, std::string val, bool isMissing) {
    if (isMissing)
        seq.solutions.push_back(val);
    else 
        seq.terms.push_back(val);
}
void InsertTerms(Sequence& seq, std::vector<std::string>& terms) {
    int i = 0;
    int numofTerms = terms.size();
    int tracksz = 0;
    int missingindsz = seq.missingindices.size();
    while (i < numofTerms) {
        if (i == 0) {
            if (seq.missingindices[tracksz] == 0) {
                Insert(seq, terms[0], true);
                tracksz++;
            }
            else
                Insert(seq, terms[0], false);
        }
        else {
            if (tracksz < missingindsz) {
                if (i == seq.missingindices[tracksz]) {
                    tracksz++;
                    Insert(seq, terms[i], true);
                }
                else
                    Insert(seq, terms[i], false);
            }
            else
                Insert(seq, terms[i], false);
        }
        i++;
    }
}
void GenerateTerms(std::vector<int>& terms, bool isgeo, int constant, int curr, int extra) {
    int currterm = terms[curr];
    int newterm;
    if (!isgeo) {
        if (extra != 0)
            newterm = (currterm + constant) * extra;
        else
            newterm = currterm + constant;
    }
    else {
        if (extra != 0)
            newterm = (currterm * constant) + extra;
        else
            newterm = currterm * constant;
    }
    terms.push_back(newterm);
}
void DigitGrouping(Sequence& seq) {
    int numofTerms = 0;
    int counter = 0;
    int firstterm = 0;

    std::vector<int> terms;

    bool isgeo = (rand() % 2);
    int addandmul = (rand() % 8);
    int constant = 0;
    int secondval = 0;

    if (addandmul < 4) {
        firstterm = 1 + (rand() % 9);
        terms.push_back(firstterm);

        numofTerms = 7 + (rand() % 2);

        if (addandmul) {
            if (isgeo) {
                constant = 2 + (rand() % 9);
                secondval = 1 + (rand() % 10);
                int negval = (rand() % 2);
                if (negval && ((firstterm * constant) > 15))
                    secondval = secondval * -1;
            }
            else {
                constant = 1 + (rand() % 10);
                secondval = 2 + (rand() % 9);
            }
            while (true) {
                GenerateTerms(terms, isgeo, constant, counter, 0);
                counter++;
                if (counter == numofTerms - 1)
                    break;
                GenerateTerms(terms, !isgeo, secondval, counter, 0);
                counter++;
                if (counter == numofTerms - 1)
                    break;
            }
        }
        else {
            secondval = 2 + (rand() % 5);
            if (isgeo)
                constant = 2 + (rand() % 4);
            else 
                constant = 1 + (rand() % 10);
            while (counter < numofTerms - 1) {
                GenerateTerms(terms, isgeo, constant, counter, secondval);
                counter++;
            }
        }
    }
    else {
        int noalt = rand() % 5;
        if (isgeo) {
            numofTerms = 6;
            constant = 2 + (rand() % 9);
            if (constant == 10)
                constant = 2 + (rand() % 9);

            if (!noalt)
                firstterm = 1 + (rand() % 10);
            else
                firstterm = 1 + (rand() % 50);

            terms.push_back(firstterm);

            while (counter < numofTerms - 1){
                if (noalt){
                    GenerateTerms(terms, isgeo, constant, counter, 0);
                    counter++;
                    continue;
                }
                if (constant < 5)
                    GenerateTerms(terms, isgeo, constant++, counter, 0);
                else
                    GenerateTerms(terms, isgeo, constant--, counter, 0);
                counter++;
            }
        }
        else {
            firstterm = 1 + (rand() % 9);
            terms.push_back(firstterm);
            numofTerms = 6 + (rand() % 2);
            int nosub = rand() % 2;

            if (noalt)
                constant = 1 + (rand() % 45);
            else if (nosub)
                constant = 1 + (rand() % 45);
            else
                constant = 3 + (rand() % 45);

            while (counter < numofTerms - 1){
                if (noalt){
                    GenerateTerms(terms, isgeo, constant, counter, 0);
                    counter++;
                    continue;  
                }
                if (nosub)
                    GenerateTerms(terms, isgeo, constant++, counter, 0);
                else
                    GenerateTerms(terms, isgeo, constant--, counter, 0);
                counter++;
            }
        }
    }
    std::vector<int> newlist;
    OneDigitList(terms, newlist);
    DetermineNumofDigits(newlist, seq);
}
void OneDigitList(std::vector<int>& terms, std::vector<int>& newlist) {
    int counter = 0;
    int numofTerms = terms.size();
    for (int i = 0; i < numofTerms; i++) {
        int term = terms[i];
        if (term > 9) {
            int numlen = intlen(term);
            std::string numstr = std::to_string(term);
            for (int j = 0; j < numlen; j++)
                newlist.push_back(numstr[j] - 48);
            counter++;
            if (counter == numofTerms)
                break;
        }
        else {
            newlist.push_back(term);
            counter++;
            if (counter == numofTerms)
                break;
        }
    }
}
void CombineDigits(std::vector<int>& terms, std::vector<int>& combineddigits, int numofTerms, int numofDigits) {
    int counter = 0;
    int returnval = 0;
    int mul = pow(10, (numofDigits - 1));
    int initmul = 0;
    int total = 0;
    int index = 0;

    while (counter < numofTerms) {
        initmul = mul;
        while (initmul != 0) {
            total += (terms[index] * initmul);
            index++;
            initmul /= 10;
        }
        combineddigits.push_back(total);
        total = 0;
        counter++;
    }
}
void DetermineNumofDigits(std::vector<int>& newlist, Sequence& seq) {
    int numofMissing;
    int numofTerms = newlist.size();
    int numofDigits = isPrime(numofTerms);
    if (numofDigits > 0) {
        std::vector<int> combineddigits;
        numofTerms = (numofTerms / numofDigits);
        CombineDigits(newlist, combineddigits, numofTerms, numofDigits);
        if (numofTerms < 7)
            numofMissing = 1;
        else
            numofMissing = (numofTerms / 5);
        RandomIndiceGen(seq.missingindices, numofTerms - 2, numofMissing, 1);
        std::vector<std::string> strlist;
        ConvertoStrings(combineddigits, strlist, numofDigits);
        InsertTerms(seq, strlist);
    }
    else {
        numofMissing = (numofTerms / 4);
        if (numofMissing == 0)
            numofMissing++;
        RandomIndiceGen(seq.missingindices, numofTerms - 2, numofMissing, 1);
        std::vector<std::string> strlist;
        ConvertoStrings(newlist, strlist, -1);
        InsertTerms(seq, strlist);
    }
}
void FH(std::vector<int>& terms) {

    // 2, 5, 7, 12, 19....

    // 2, 5, 7, 12, 9, 14, 14, 19, ?, 16
    // 2, 5, 7, 12, 12, 17, 19, ?, ?, 29
    // 2, 5, 7, 16, 12, 21, 23, ?, 28, ?, 33, 42
    // 2, 5, 7, 16, 23, 32, ?, 64
    // 2, 5, 7, 12, 19, 24, ?, 36, 43, ?
    // 3, 5, 8, 14, 13, ?, 22, 28, ?, 33

    // 2, 5, 10, 60, 20, 120, 120, ?, 40, ?
    // 2, 5, 10, 60, 50, 300, 600, 3600,

    // 9, 7, 6, 22, 28, 37, ?, 59, 65, ?, 74, ?
    // 3, 3, 7, 13, 21, 23, 31, 41, ?, 57, 65
    // 3, 3, 7, 13, 21, 27, ?, 67, 128, 134
    // 3, 3, 7, 21, 39, ?, 143
    // 2, 5, 6, 10, 40, 30, ?, 60, 240, 400, 1600
}
void FHelper2(std::vector<int>& terms, int ismul, int notaltfibo, int distinct, int constant, int mul) {
}
void FibonacciHelper(std::vector<int>& terms) {
    int firstterm = 0;
    int ismul = (rand() % 2);
    int secondterm = 0;
    int numofTerms = 0;
    int isgeo = 0;
    int distinct = 0;
    int constant = 0;

    if (ismul) {
        firstterm = 2 + (rand() % 9);
        secondterm = 2 + (rand() % 10);
        numofTerms = 6;
    }
    else {
        firstterm = 1 + (rand() % 50);
        secondterm = 1 + (rand() % 50);
        numofTerms = 7 + (rand() % 3);
    }

    terms.push_back(firstterm);
    terms.push_back(secondterm);
    int notaltfibo = rand() % 4;
    if (!notaltfibo) {
        isgeo = rand() % 2;
        distinct = rand() % 3;
        if (isgeo) 
            constant = 2 + (rand() % 4);
        else 
            constant = 1 + (rand() % 10);
    }

    if (!ismul) {
        if (notaltfibo || !distinct) {
            for (int i = 2; i < numofTerms; i++) {
                int val = terms[i - 1] + terms[i - 2];
                if (notaltfibo)
                    terms.push_back(val);
                else {
                    if (isgeo)
                        terms.push_back(val * constant);
                    else
                        terms.push_back(val + constant);
                }
            }
        }
        else {
            for (int i = 2; i < numofTerms; i += 2) {
                int val = terms[i - 1] + terms[i - 2];
                terms.push_back(val);
                if ((i + 1) == numofTerms)
                    break;
                if (isgeo)
                    terms.push_back(val * constant);                
                else 
                    terms.push_back(val + constant);
            }
        }
    }
    else {
        if (notaltfibo) {
            if (firstterm < 6 && secondterm < 6)
                numofTerms += (rand() % 2);
            for (int i = 2; i < numofTerms; i++)
                terms.push_back(terms[i - 1] * terms[i - 2]);
        }
        else {
            if (isgeo) {
                if (secondterm < 7) {
                    if (secondterm < 5)
                        numofTerms += (1 + (rand() % 2));
                    else 
                        numofTerms++;
                }
                for (int i = 2; i < numofTerms; i += 2) {
                    int val = terms[i - 1] * terms[i - 2];
                    terms.push_back(val);
                    if ((i + 1) == numofTerms)
                        break;
                    terms.push_back(val * constant);
                }
            }
            else {
                if (!distinct) {
                    for (int i = 2; i < numofTerms; i++) {
                        int val = terms[i - 1] * terms[i - 2];
                        terms.push_back(val + constant);
                    }
                }
                else {
                    for (int i = 2; i < numofTerms; i += 2) {
                        int val = terms[i - 1] * terms[i - 2];
                        terms.push_back(val);
                        if ((i + 1) == numofTerms)
                            break;
                        terms.push_back(val + constant);
                    }
                }
            }
        }
    }
}
void Fibonacci(Sequence& seq) {
    std::vector<int> terms;
    FibonacciHelper(terms);
    int notdigitlist = rand() % 4;
    if (!notdigitlist) {
        std::vector<int> newlist;
        OneDigitList(terms, newlist);
        DetermineNumofDigits(newlist, seq);
    }
    else {
        int termsz = terms.size();
        int numofMissing;
        if (termsz < 8)
            numofMissing = 1;
        else {
            if (termsz == 8)
                numofMissing = 2;
            else
                numofMissing = 3;
        }
        RandomIndiceGen(seq.missingindices, termsz - 2, numofMissing, 1);
        std::vector<std::string> strlist;
        ConvertoStrings(terms, strlist, -1);
        InsertTerms(seq, strlist);
    }
}
void DigitOperations(Sequence& seq) {
    std::vector<int> terms;
    const std::string OPS = "AMS";
    std::string opstring = "";
    int firstterm = 1001 + (rand() % 8999);
    terms.push_back(firstterm);
    int op = 1 + (rand() % 3);
    for (int i = 0; i < op; i++) {
        int opindex = rand() % 3;
        char c = OPS.at(opindex);
        opstring.push_back(c);
    }
    int opstringsz = opstring.size();
    for (int i = 0; i < opstringsz; i++) {
    }
}
void SumsAndProducts(Sequence& seq) {
    std::vector<int> terms;
    bool ismul = (rand() % 2);
    int cons1 = 2 + (rand() % 4);
    int cons2 = 2 + (rand() % 4);
    int numofTerms = 8 + (rand() % 2);
    if (ismul) {
        bool isInc1 = rand() % 2;
        bool isInc2 = rand() % 2;
        int firstterm = 2 + (rand() % 4);
        int secondterm = 2 + (rand() % 4);
        for (int i = 0; i < numofTerms; i++) {
            terms.push_back(firstterm * secondterm);
            if (isInc1)
                firstterm += cons1;
            else
                firstterm -= cons1;
            if (isInc2)
                secondterm += cons2;
            else
                secondterm -= cons2;
        }
    }
    else {
        int firstterm = 2 + (rand() % 9);
        int secondterm = 2 + (rand() % 9);
        for (int i = 0; i < numofTerms; i++) {
            terms.push_back(firstterm + secondterm);
            firstterm *= cons1;
            secondterm *= cons2;
        }
    }
    RandomIndiceGen(seq.missingindices, numofTerms - 2, 1, 1);
    std::vector<std::string> strlist;
    ConvertoStrings(terms, strlist, -1);
    InsertTerms(seq, strlist);
}
void BasicSeqGen(Sequence& seq) {
    int info[2];
    Randominit(info);
    int numofTerms = info[0];
    int firstterm = info[1];
    bool isgeo = (rand() % 2);
    int successivealterval = (rand() % 8);
    bool successivealterflag1 = (successivealterval > 3 && successivealterval < 6);
    bool successivealterflag2 = (successivealterval > 5);
    int addalter = 0;
    bool ismulalteralt = false;
    int mulalter = 0;
    int constant = 0;
    std::vector<int> terms;
    terms.push_back(firstterm);
    Randomindices(numofTerms, seq.missingindices, isgeo);
    if (!isgeo) {
        constant = RandomAddConstant();
        if (successivealterval > 3) {
            addalter = 1 + (rand() % 10);
            int misssz = seq.missingindices.size();
            if (misssz > 2) {
                int whattoremove = (rand() % misssz);
                seq.missingindices.erase(seq.missingindices.begin() + whattoremove);
            }
        }
    }
    else {
        constant = RandomMultiplyConstant();
        int mulcheck = (rand() % 3);
        if (successivealterval > 3) {
            int misssz = seq.missingindices.size();
            if (misssz > 2) {
                int whattoremove = (rand() % misssz);
                seq.missingindices.erase(seq.missingindices.begin() + whattoremove);
            }
        }
        int checkcons = constant;
        if (checkcons < 0)
            checkcons = checkcons * -1;
        ismulalteralt = (mulcheck) && (checkcons < 5) && (numofTerms > 5);
        if (constant % 2 != 0 && ismulalteralt) {
            while (true) {
                mulalter = 2 + (rand() % 5);
                if (mulalter % 2 != 0)
                    continue;
                break;
            }
        }
    }
    int counter = 0;
    int savedcons = constant;
    bool doaddalter = (numofTerms == 7 || (seq.missingindices.size() == 2));
    if (numofTerms > 5) {
        if (!isgeo) {
            while (counter < numofTerms - 1) {
                GenerateTerms(terms, isgeo, constant, counter, false);
                if (!doaddalter || (!successivealterflag1 && !successivealterflag2)){
                    counter++;
                    continue;
                }
                if (successivealterflag1)
                    constant += addalter;    
                else 
                    constant -= addalter;
                counter++;
            }
        }
        else {
            if (savedcons > 4 || ismulalteralt) {
                while (counter < numofTerms - 1){
                    GenerateTerms(terms, isgeo, constant, counter, false);
                    if (!ismulalteralt && successivealterflag1)
                        constant++;
                    else if (!ismulalteralt && successivealterflag2)
                        constant--;
                    else if (ismulalteralt && successivealterflag1)
                        constant += mulalter;
                    else if (ismulalteralt && successivealterflag2)
                        constant -= mulalter;
                    counter++;
                }
            }
            else {
                while (counter < numofTerms - 1) {
                    GenerateTerms(terms, isgeo, constant, counter, false);
                    counter++;
                }
            }
        }
    }
    else {
        while (counter < numofTerms - 1) {
            GenerateTerms(terms, isgeo, constant, counter, false);
            counter++;
        }
    }
    std::vector<std::string> strlist;
    ConvertoStrings(terms, strlist, -1);
    InsertTerms(seq, strlist);
}