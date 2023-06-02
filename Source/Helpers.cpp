#include "../include/SeqFunct.h"

int intlen(int num) {
    if (num == 0)
        return 1;

    int length = 0;
    while (num != 0) {
        length++;
        num = num / 10;
    }
    return length;
}
int isPrime(int num) {
    bool isprime = true;
    if (num == 1)
        return -1;

    std::vector<int> factors;
    int i = 2;
    while (i * i <= num) {
        if (num % i == 0) {
            if ((num / i) > 2) {
                factors.push_back(i);
                isprime = false;
            }
        }
        i++;
    }
    if (isprime)
        return 0;
    else {
        int listsz = factors.size();
        int facindex = rand() % listsz;
        return factors[facindex];
    }
}
void ConvertoStrings(std::vector<int>& terms, std::vector<std::string>& newlist, int len) {
    int termsz = terms.size();
    if (len == -1) {
        for (int i = 0; i < termsz; i++)
            newlist.push_back(std::to_string(terms[i]));
    }
    else {
        for (int i = 0; i < termsz; i++) {
            int val = terms[i];
            newlist.push_back("");
            int vallen = intlen(val);
            if (vallen != len) {
                int numofzeroes = (len - vallen);
                for (int j = 0; j < numofzeroes; j++)
                    newlist[i] += "0";
                newlist[i] += std::to_string(val);
            }
            else
                newlist[i] += std::to_string(val);
        }
    }
}