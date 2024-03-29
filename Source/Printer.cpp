#include "../include/SeqFunct.h"
#include "../include/Printer.h"
#include "../include/Helpers.h"
#include <iostream>
#include <fstream>

void PrintToFile(int seqs, std::ostream& terms, std::ostream& sols) {
    int x = 0;
    Sequence seq;
    int funct;
    while (x < seqs) {
        funct = (rand() % 4);
        if (funct < 2) {
            funct = rand() % 10;
            if (funct != 9)
                BasicSeqGen(seq);
            else
                SumsAndProducts(seq);
        }
        else if (funct == 2)
            DigitGrouping(seq);
        else 
            Fibonacci(seq);

        size_t termsz = seq.terms.size();
        size_t solsz = seq.solutions.size();
        size_t totalsz = termsz + solsz;
        int missind = 0;
        terms << (x + 1) << ". ";
        int counter = 0;
        int totalcounter = 0;
        bool exit = false;
        while (true) {
            while (true) {
                if (missind < solsz) {
                    while (totalcounter == seq.missingindices[missind]) {
                        missind++;
                        totalcounter++;
                        terms << "?";

                        if (totalcounter < totalsz)
                            terms << ", ";
                        else
                            exit = true;

                        if (missind == solsz)
                            break;
                    }
                }
                break;
            }
            
            if (exit)
                break;

            if (counter < termsz) {
                PrintVal(seq.terms[counter], terms);
                totalcounter++;
                counter++;
            }

            if (totalcounter >= totalsz)
                break;
            
            terms << ", ";
        }
        terms << std::endl;
        sols << (x + 1) << ". ";
        for (int i = 0; i < solsz; i++) {
            if (i != (solsz - 1)) {
                PrintVal(seq.solutions[i], sols);
                sols << ", ";
            }
            else
                PrintVal(seq.solutions[i], sols);
        }
        sols << std::endl;
        seq.terms.clear();
        seq.solutions.clear();
        seq.missingindices.clear();
        x++;
    }
}
void PrintVal(std::string val, std::ostream& stream) {
    stream << val;
}